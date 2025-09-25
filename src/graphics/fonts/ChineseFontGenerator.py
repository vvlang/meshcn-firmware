#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
中文字体生成工具
基于常用字表生成UTF-8中文字库
"""

import os
import sys
import struct
from PIL import Image, ImageDraw, ImageFont
import platform

class ChineseFontGenerator:
    def __init__(self):
        self.font_paths = self._detect_system_fonts()
        self.char_list = []
        self.font_data = {}
        
    def _detect_system_fonts(self):
        """自动检测系统字体路径"""
        system = platform.system()
        font_paths = []
        
        if system == "Darwin":  # macOS
            font_paths = [
                "/System/Library/Fonts/STHeiti Light.ttc",
                "/System/Library/Fonts/STHeiti Medium.ttc",
                "/System/Library/Fonts/PingFang.ttc",
                "/System/Library/Fonts/Helvetica.ttc"
            ]
        elif system == "Linux":
            font_paths = [
                "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",
                "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",
                "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
                "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf"
            ]
        elif system == "Windows":
            font_paths = [
                "C:/Windows/Fonts/simsun.ttc",
                "C:/Windows/Fonts/simhei.ttf",
                "C:/Windows/Fonts/msyh.ttc",
                "C:/Windows/Fonts/arial.ttf"
            ]
        
        # 检查字体文件是否存在
        available_fonts = []
        for font_path in font_paths:
            if os.path.exists(font_path):
                available_fonts.append(font_path)
        
        return available_fonts
    
    def load_character_list(self, file_path):
        """从文件加载字符列表"""
        try:
            with open(file_path, 'r', encoding='utf-8') as f:
                lines = f.readlines()
            
            self.char_list = []
            for line in lines:
                line = line.strip()
                if line and not line.startswith('#'):
                    # 处理每个字符
                    for char in line:
                        if char and ord(char) > 127:  # 非ASCII字符
                            self.char_list.append(char)
            
            print(f"加载了 {len(self.char_list)} 个字符")
            return True
        except Exception as e:
            print(f"加载字符列表失败: {e}")
            return False
    
    def generate_font_data(self, font_size=16):
        """生成字体数据"""
        if not self.font_paths:
            print("未找到可用的系统字体")
            return False
        
        # 选择第一个可用的字体
        font_path = self.font_paths[0]
        print(f"使用字体: {font_path}")
        
        try:
            # 加载字体
            font = ImageFont.truetype(font_path, font_size)
            
            # 为每个字符生成位图数据
            for i, char in enumerate(self.char_list):
                try:
                    # 创建足够大的临时图像
                    temp_size = font_size * 3
                    img = Image.new('1', (temp_size, temp_size), 0)
                    draw = ImageDraw.Draw(img)
                    
                    # 绘制字符
                    draw.text((font_size, font_size), char, font=font, fill=1)
                    
                    # 获取字符边界
                    bbox = draw.textbbox((font_size, font_size), char, font=font)
                    if bbox:
                        char_width = bbox[2] - bbox[0]
                        char_height = bbox[3] - bbox[1]
                        
                        # 裁剪字符区域
                        char_img = img.crop((bbox[0], bbox[1], bbox[2], bbox[3]))
                        
                        # 确保尺寸合理
                        if char_width > 0 and char_height > 0 and char_width <= font_size * 2:
                            # 转换为字节数据
                            char_data = self._image_to_bytes(char_img)
                            
                            self.font_data[char] = {
                                'width': char_width,
                                'height': char_height,
                                'data': char_data
                            }
                        else:
                            # 使用默认尺寸
                            char_img = Image.new('1', (font_size, font_size), 0)
                            char_data = self._image_to_bytes(char_img)
                            
                            self.font_data[char] = {
                                'width': font_size,
                                'height': font_size,
                                'data': char_data
                            }
                    else:
                        # 使用默认尺寸
                        char_img = Image.new('1', (font_size, font_size), 0)
                        char_data = self._image_to_bytes(char_img)
                        
                        self.font_data[char] = {
                            'width': font_size,
                            'height': font_size,
                            'data': char_data
                        }
                    
                    if (i + 1) % 100 == 0:
                        print(f"已处理 {i + 1}/{len(self.char_list)} 个字符")
                        
                except Exception as char_error:
                    print(f"处理字符 '{char}' 时出错: {char_error}")
                    # 使用默认数据
                    char_img = Image.new('1', (font_size, font_size), 0)
                    char_data = self._image_to_bytes(char_img)
                    
                    self.font_data[char] = {
                        'width': font_size,
                        'height': font_size,
                        'data': char_data
                    }
            
            print(f"成功生成 {len(self.font_data)} 个字符的字体数据")
            return True
            
        except Exception as e:
            print(f"生成字体数据失败: {e}")
            return False
    
    def _image_to_bytes(self, img):
        """将图像转换为字节数据"""
        width, height = img.size
        data = []
        
        # 按列存储（OLEDDisplay格式）
        for x in range(width):
            column = 0
            for y in range(height):
                if img.getpixel((x, y)):
                    column |= (1 << y)
            # 确保字节值在0-255范围内
            data.append(column & 0xFF)
        
        return bytes(data)
    
    def generate_cpp_font_file(self, output_path, font_name, font_size):
        """生成C++字体文件"""
        try:
            with open(output_path, 'w', encoding='utf-8') as f:
                f.write(f'#ifdef OLED_CN\n\n')
                f.write(f'#include "OLEDDisplayFontsCN.h"\n\n')
                f.write(f'// 中文字体 - {font_size}pt\n')
                f.write(f'// 包含 {len(self.font_data)} 个常用汉字\n')
                f.write(f'// 生成时间: {__import__("datetime").datetime.now().strftime("%Y-%m-%d %H:%M:%S")}\n\n')
                
                # 生成字体数组
                f.write(f'const uint8_t {font_name}[] PROGMEM = {{\n')
                
                # 计算总字符数
                total_chars = len(self.font_data)
                
                # 写入字体头信息
                f.write(f'    {font_size:3d}, // Width: {font_size}\n')
                f.write(f'    {font_size:3d}, // Height: {font_size}\n')
                f.write(f'    0x20, // First char: 32\n')
                f.write(f'    0x{total_chars:02X}, // Number of chars: {total_chars}\n\n')
                
                # 生成跳转表
                f.write('    // Jump Table:\n')
                offset = 0
                
                for char in self.char_list:
                    if char in self.font_data:
                        char_info = self.font_data[char]
                        width = char_info['width']
                        height = char_info['height']
                        
                        # 跳转表条目: offset_high, offset_low, width, height
                        f.write(f'    0x{offset >> 8:02X}, 0x{offset & 0xFF:02X}, 0x{width:02X}, 0x{height:02X}, // {char} (U+{ord(char):04X})\n')
                        offset += width
                
                f.write('\n    // Font Data:\n')
                
                # 生成字体数据
                for char in self.char_list:
                    if char in self.font_data:
                        char_info = self.font_data[char]
                        data = char_info['data']
                        
                        f.write(f'    // {char} (U+{ord(char):04X})\n')
                        for i in range(0, len(data), 16):
                            line_data = data[i:i+16]
                            hex_str = ', '.join([f'0x{b:02X}' for b in line_data])
                            f.write(f'    {hex_str},\n')
                        f.write('\n')
                
                f.write('};\n\n')
                f.write('#endif // OLED_CN\n')
            
            print(f"成功生成字体文件: {output_path}")
            return True
            
        except Exception as e:
            print(f"生成C++字体文件失败: {e}")
            return False
    
    def generate_header_file(self, output_path):
        """生成头文件"""
        try:
            with open(output_path, 'w', encoding='utf-8') as f:
                f.write('#ifndef OLEDDISPLAYFONTSCN_h\n')
                f.write('#define OLEDDISPLAYFONTSCN_h\n\n')
                f.write('#ifdef ARDUINO\n')
                f.write('#include <Arduino.h>\n')
                f.write('#elif __MBED__\n')
                f.write('#define PROGMEM\n')
                f.write('#endif\n\n')
                f.write('#ifdef OLED_CN\n\n')
                f.write('// 中文字体声明\n')
                f.write('extern const uint8_t ArialMT_Plain_10_CN[] PROGMEM;\n')
                f.write('extern const uint8_t ArialMT_Plain_16_CN[] PROGMEM;\n')
                f.write('extern const uint8_t ArialMT_Plain_24_CN[] PROGMEM;\n\n')
                f.write('#endif // OLED_CN\n\n')
                f.write('#endif\n')
            
            print(f"成功生成头文件: {output_path}")
            return True
            
        except Exception as e:
            print(f"生成头文件失败: {e}")
            return False

def main():
    print("中文字体生成工具")
    print("=" * 50)
    
    # 创建生成器实例
    generator = ChineseFontGenerator()
    
    # 加载字符列表
    char_file = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/常用字表.txt"
    if not generator.load_character_list(char_file):
        return False
    
    # 生成不同尺寸的字体
    font_sizes = [10, 16, 24]
    font_names = ['ArialMT_Plain_10_CN', 'ArialMT_Plain_16_CN', 'ArialMT_Plain_24_CN']
    
    for font_size, font_name in zip(font_sizes, font_names):
        print(f"\n生成 {font_size}pt 字体...")
        
        # 生成字体数据
        if not generator.generate_font_data(font_size):
            continue
        
        # 生成C++文件
        cpp_file = f"/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/src/graphics/fonts/OLEDDisplayFontsCN_{font_size}.cpp"
        if generator.generate_cpp_font_file(cpp_file, font_name, font_size):
            print(f"✅ 成功生成 {font_size}pt 字体文件")
        else:
            print(f"❌ 生成 {font_size}pt 字体文件失败")
    
    # 生成头文件
    header_file = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/src/graphics/fonts/OLEDDisplayFontsCN.h"
    if generator.generate_header_file(header_file):
        print("✅ 成功生成头文件")
    else:
        print("❌ 生成头文件失败")
    
    print("\n字体生成完成！")
    print("请将生成的文件复制到 src/graphics/fonts/ 目录")
    print("并在 variant.h 中启用 #define OLED_CN")

if __name__ == "__main__":
    main()
