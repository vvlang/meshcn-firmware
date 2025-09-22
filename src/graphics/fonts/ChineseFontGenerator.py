#!/usr/bin/env python3
"""
中文字体生成工具
用于生成Arduino兼容的中文字体数据
"""

import os
import sys
from PIL import Image, ImageDraw, ImageFont
import struct

class ChineseFontGenerator:
    def __init__(self):
        self.font_size = 10
        self.font_path = None
        self.chars = []
        
    def set_font(self, font_path, size=10):
        """设置字体路径和大小"""
        self.font_path = font_path
        self.font_size = size
        
    def add_chars(self, chars):
        """添加要生成的字符"""
        self.chars.extend(chars)
        
    def generate_font_data(self):
        """生成字体数据"""
        if not self.font_path or not os.path.exists(self.font_path):
            print("错误: 字体文件不存在")
            return None
            
        try:
            font = ImageFont.truetype(self.font_path, self.font_size)
        except:
            print("错误: 无法加载字体文件")
            return None
            
        font_data = []
        
        for char in self.chars:
            # 创建字符图像
            img = Image.new('1', (self.font_size * 2, self.font_size * 2), 0)
            draw = ImageDraw.Draw(img)
            
            # 绘制字符
            draw.text((0, 0), char, font=font, fill=1)
            
            # 获取字符边界
            bbox = draw.textbbox((0, 0), char, font=font)
            width = bbox[2] - bbox[0]
            height = bbox[3] - bbox[1]
            
            # 调整到合适大小
            if width > self.font_size:
                width = self.font_size
            if height > self.font_size:
                height = self.font_size
                
            # 生成像素数据
            char_data = []
            for y in range(height):
                byte = 0
                for x in range(width):
                    if x < img.width and y < img.height:
                        pixel = img.getpixel((x, y))
                        if pixel > 0:
                            byte |= (1 << (7 - (x % 8)))
                char_data.append(byte)
                
            font_data.append({
                'char': char,
                'width': width,
                'height': height,
                'data': char_data
            })
            
        return font_data
        
    def save_arduino_font(self, font_data, output_file):
        """保存为Arduino字体格式"""
        with open(output_file, 'w') as f:
            f.write("#ifdef OLED_CN\n\n")
            f.write("#include \"OLEDDisplayFontsCN.h\"\n\n")
            
            # 生成字体数组
            f.write(f"const uint8_t ArialMT_Plain_{self.font_size}_CN[] PROGMEM = {{\n")
            f.write(f"    0x{self.font_size:02X}, // Width: {self.font_size}\n")
            f.write(f"    0x{self.font_size + 3:02X}, // Height: {self.font_size + 3}\n")
            f.write("    0x20, // First char: 32\n")
            f.write(f"    0x{len(font_data):02X}, // Number of chars: {len(font_data)}\n\n")
            
            # 生成跳转表
            offset = 0
            for i, char_data in enumerate(font_data):
                f.write(f"    // {ord(char_data['char']):04X}: {char_data['char']}\n")
                f.write(f"    0x{offset >> 8:02X}, 0x{offset & 0xFF:02X}, 0x{char_data['width']:02X}, 0x{char_data['height']:02X}, // {i}\n")
                offset += len(char_data['data'])
                
            f.write("\n    // 字体数据\n")
            for char_data in font_data:
                f.write(f"    // {char_data['char']}\n")
                for byte in char_data['data']:
                    f.write(f"    0x{byte:02X}, ")
                f.write("\n")
                
            f.write("};\n\n")
            f.write("#endif // OLED_CN\n")

def main():
    """主函数"""
    generator = ChineseFontGenerator()
    
    # 常用汉字
    common_chars = "中文显示功能测试"
    
    # 设置字体路径 (需要用户提供)
    font_path = input("请输入中文字体文件路径: ")
    if not os.path.exists(font_path):
        print("字体文件不存在，使用默认字符")
        font_path = None
        
    if font_path:
        generator.set_font(font_path, 10)
        generator.add_chars(common_chars)
        
        # 生成字体数据
        font_data = generator.generate_font_data()
        if font_data:
            generator.save_arduino_font(font_data, "OLEDDisplayFontsCN_generated.h")
            print("字体生成完成!")
        else:
            print("字体生成失败!")
    else:
        print("请提供有效的中文字体文件路径")

if __name__ == "__main__":
    main()
