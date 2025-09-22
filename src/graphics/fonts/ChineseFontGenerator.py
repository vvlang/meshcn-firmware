#!/usr/bin/env python3
"""
中文字体生成工具 - 文泉驿点阵宋体专用
用于生成Arduino兼容的中文字体数据
"""

import os
import sys
from PIL import Image, ImageDraw, ImageFont
import struct

class WenQuanYiFontGenerator:
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
        
    def get_common_chinese_chars(self):
        """获取常用中文字符集"""
        return [
            # 基本汉字
            "中文显示功能测试",
            "网络通信设备状态",
            "设置配置参数信息",
            "电池电量信号强度",
            "GPS定位时间日期",
            "消息发送接收确认",
            "节点列表连接状态",
            "系统重启关机模式",
            "蓝牙WiFi开关控制",
            "屏幕亮度音量调节",
            # 数字和标点
            "0123456789",
            "，。？！：；",
            "（）【】《》",
            "、；：""''",
            # 常用词汇
            "确定取消返回",
            "上下左右选择",
            "开关开启关闭",
            "连接断开重连",
            "成功失败错误",
            "正常异常警告"
        ]
        
    def generate_font_data(self):
        """生成字体数据 - 文泉驿点阵宋体优化"""
        if not self.font_path or not os.path.exists(self.font_path):
            print("错误: 字体文件不存在")
            return None
            
        try:
            font = ImageFont.truetype(self.font_path, self.font_size)
        except:
            print("错误: 无法加载字体文件")
            return None
            
        font_data = []
        max_width = 0
        max_height = 0
        
        for char in self.chars:
            # 创建字符图像 - 文泉驿点阵宋体优化
            img = Image.new('1', (self.font_size * 3, self.font_size * 3), 0)
            draw = ImageDraw.Draw(img)
            
            # 绘制字符
            draw.text((0, 0), char, font=font, fill=1)
            
            # 获取字符边界
            bbox = draw.textbbox((0, 0), char, font=font)
            width = bbox[2] - bbox[0]
            height = bbox[3] - bbox[1]
            
            # 文泉驿点阵宋体优化：限制最大尺寸
            if width > self.font_size * 2:
                width = self.font_size * 2
            if height > self.font_size * 2:
                height = self.font_size * 2
                
            # 记录最大尺寸
            max_width = max(max_width, width)
            max_height = max(max_height, height)
                
            # 生成像素数据 - 按列存储（OLEDDisplay格式）
            char_data = []
            for x in range(width):
                byte = 0
                for y in range(height):
                    if x < img.width and y < img.height:
                        pixel = img.getpixel((x, y))
                        if pixel > 0:
                            byte |= (1 << (y % 8))
                    if (y % 8) == 7 or y == height - 1:
                        char_data.append(byte)
                        byte = 0
                
            font_data.append({
                'char': char,
                'width': width,
                'height': height,
                'data': char_data
            })
            
        print(f"最大字符尺寸: {max_width}x{max_height}")
        return font_data
        
    def save_arduino_font(self, font_data, output_file):
        """保存为Arduino字体格式 - 文泉驿点阵宋体优化"""
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write("#ifdef OLED_CN\n\n")
            f.write("#include \"OLEDDisplayFontsCN.h\"\n\n")
            f.write("// 文泉驿点阵宋体 - 中文字体数据\n")
            f.write("// 生成时间: " + str(__import__('datetime').datetime.now()) + "\n\n")
            
            # 计算最大尺寸
            max_width = max([char['width'] for char in font_data]) if font_data else 0
            max_height = max([char['height'] for char in font_data]) if font_data else 0
            
            # 生成字体数组
            f.write(f"const uint8_t ArialMT_Plain_{self.font_size}_CN[] PROGMEM = {{\n")
            f.write(f"    0x{max_width:02X}, // 最大宽度: {max_width}\n")
            f.write(f"    0x{max_height:02X}, // 最大高度: {max_height}\n")
            f.write("    0x20, // 第一个字符: 32 (空格)\n")
            f.write(f"    0x{len(font_data):02X}, // 字符数量: {len(font_data)}\n\n")
            
            # 生成跳转表
            offset = 0
            f.write("    // 跳转表 (偏移量高字节, 偏移量低字节, 宽度, 高度)\n")
            for i, char_data in enumerate(font_data):
                char_code = ord(char_data['char'])
                f.write(f"    0x{offset >> 8:02X}, 0x{offset & 0xFF:02X}, 0x{char_data['width']:02X}, 0x{char_data['height']:02X}, // {i}: {char_data['char']} (U+{char_code:04X})\n")
                offset += len(char_data['data'])
                
            f.write("\n    // 字体数据 (按列存储)\n")
            for char_data in font_data:
                f.write(f"    // {char_data['char']} ({char_data['width']}x{char_data['height']})\n")
                for i, byte in enumerate(char_data['data']):
                    if i % 16 == 0:
                        f.write("    ")
                    f.write(f"0x{byte:02X}, ")
                    if (i + 1) % 16 == 0:
                        f.write("\n")
                if len(char_data['data']) % 16 != 0:
                    f.write("\n")
                
            f.write("};\n\n")
            f.write("#endif // OLED_CN\n")

def main():
    """主函数 - 文泉驿点阵宋体专用"""
    generator = WenQuanYiFontGenerator()
    
    print("=== 文泉驿点阵宋体字体生成工具 ===")
    print("支持生成10pt、16pt、24pt三种尺寸的中文字体")
    
    # 获取常用中文字符
    common_chars = "".join(generator.get_common_chinese_chars())
    print(f"将生成 {len(common_chars)} 个字符的字体数据")
    
    # 文泉驿点阵宋体常见路径
    possible_paths = [
        "/System/Library/Fonts/STHeiti Light.ttc",  # macOS
        "/System/Library/Fonts/Hiragino Sans GB.ttc",  # macOS
        "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc",  # Linux
        "/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc",  # Linux
        "C:/Windows/Fonts/simsun.ttc",  # Windows
        "C:/Windows/Fonts/msyh.ttc",  # Windows
    ]
    
    font_path = None
    for path in possible_paths:
        if os.path.exists(path):
            font_path = path
            print(f"找到系统字体: {path}")
            break
    
    if not font_path:
        font_path = input("请输入文泉驿点阵宋体字体文件路径: ")
        if not os.path.exists(font_path):
            print("字体文件不存在，使用默认字符")
            font_path = None
    
    if font_path:
        # 生成三种尺寸的字体
        sizes = [10, 16, 24]
        for size in sizes:
            print(f"\n生成 {size}pt 字体...")
            generator.set_font(font_path, size)
            generator.add_chars(common_chars)
            
            # 生成字体数据
            font_data = generator.generate_font_data()
            if font_data:
                output_file = f"OLEDDisplayFontsCN_{size}.cpp"
                generator.save_arduino_font(font_data, output_file)
                print(f"{size}pt 字体生成完成: {output_file}")
            else:
                print(f"{size}pt 字体生成失败!")
    else:
        print("请提供有效的文泉驿点阵宋体字体文件路径")

if __name__ == "__main__":
    main()
