#!/usr/bin/env python3
"""
生成AIYeon文字logo的XBM格式数据
"""

from PIL import Image, ImageDraw, ImageFont
import sys

def generate_aiyeon_logo():
    # 创建图像
    width, height = 128, 64  # 更大的尺寸
    img = Image.new('1', (width, height), 0)  # 黑色背景
    draw = ImageDraw.Draw(img)
    
    # 尝试使用系统字体，如果没有则使用默认字体
    try:
        # 尝试使用较大的字体
        font = ImageFont.truetype("/System/Library/Fonts/Arial.ttf", 48)
    except:
        try:
            font = ImageFont.truetype("/System/Library/Fonts/Helvetica.ttc", 48)
        except:
            # 使用默认字体
            font = ImageFont.load_default()
    
    # 绘制"AIYeon"文字
    text = "AIYeon"
    
    # 获取文字尺寸
    bbox = draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    
    # 计算居中位置
    x = (width - text_width) // 2
    y = (height - text_height) // 2
    
    # 绘制白色文字
    draw.text((x, y), text, fill=1, font=font)
    
    # 保存为XBM格式
    img.save('aiyeon_logo.xbm', format='XBM')
    
    # 读取XBM文件并转换为C数组格式
    with open('aiyeon_logo.xbm', 'r') as f:
        content = f.read()
    
    # 提取数据部分
    start = content.find('{')
    end = content.rfind('}') + 1
    data = content[start:end]
    
    print("AIYeon Logo XBM Data:")
    print(f"Width: {width}")
    print(f"Height: {height}")
    print(f"Data: {data}")
    
    return width, height, data

if __name__ == "__main__":
    generate_aiyeon_logo()
