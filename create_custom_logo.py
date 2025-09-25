#!/usr/bin/env python3
"""
创建自定义logo的XBM格式文件
"""

from PIL import Image, ImageDraw, ImageFont
import sys

def create_custom_logo():
    # 创建图像
    width, height = 50, 28  # 标准尺寸
    img = Image.new('1', (width, height), 0)  # 黑色背景
    draw = ImageDraw.Draw(img)
    
    # 方法1: 绘制简单图形
    # 绘制一个简单的"AIYeon"文字logo
    try:
        font = ImageFont.truetype("/System/Library/Fonts/Arial.ttf", 16)
    except:
        font = ImageFont.load_default()
    
    # 绘制文字
    text = "AIYeon"
    bbox = draw.textbbox((0, 0), text, font=font)
    text_width = bbox[2] - bbox[0]
    text_height = bbox[3] - bbox[1]
    
    # 计算居中位置
    x = (width - text_width) // 2
    y = (height - text_height) // 2
    
    # 绘制白色文字
    draw.text((x, y), text, fill=1, font=font)
    
    # 方法2: 绘制几何图形
    # 绘制一个简单的logo图案
    # draw.rectangle([10, 5, 40, 23], outline=1, fill=0)
    # draw.ellipse([15, 8, 35, 20], outline=1, fill=0)
    
    # 保存为XBM格式
    img.save('custom_icon.xbm', format='XBM')
    
    # 读取XBM文件并转换为C数组格式
    with open('custom_icon.xbm', 'r') as f:
        content = f.read()
    
    # 提取数据部分
    start = content.find('{')
    end = content.rfind('}') + 1
    data = content[start:end]
    
    print("自定义Logo XBM数据:")
    print(f"Width: {width}")
    print(f"Height: {height}")
    print(f"Data: {data}")
    
    return width, height, data

if __name__ == "__main__":
    create_custom_logo()


