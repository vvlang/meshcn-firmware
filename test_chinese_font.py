#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
中文字体测试脚本
验证生成的字体文件是否正确
"""

import os
import sys

def test_font_files():
    """测试字体文件是否存在"""
    font_dir = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/src/graphics/fonts"
    
    required_files = [
        "OLEDDisplayFontsCN.h",
        "OLEDDisplayFontsCN_10.cpp",
        "OLEDDisplayFontsCN_16.cpp", 
        "OLEDDisplayFontsCN_24.cpp"
    ]
    
    print("检查字体文件...")
    all_exist = True
    
    for file in required_files:
        file_path = os.path.join(font_dir, file)
        if os.path.exists(file_path):
            size = os.path.getsize(file_path)
            print(f"✅ {file} - {size:,} bytes")
        else:
            print(f"❌ {file} - 文件不存在")
            all_exist = False
    
    return all_exist

def test_font_content():
    """测试字体文件内容"""
    font_dir = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/src/graphics/fonts"
    
    print("\n检查字体文件内容...")
    
    # 检查头文件
    header_file = os.path.join(font_dir, "OLEDDisplayFontsCN.h")
    if os.path.exists(header_file):
        with open(header_file, 'r', encoding='utf-8') as f:
            content = f.read()
            if "ArialMT_Plain_10_CN" in content and "ArialMT_Plain_16_CN" in content:
                print("✅ 头文件包含正确的字体声明")
            else:
                print("❌ 头文件内容不正确")
    
    # 检查16pt字体文件
    font_16_file = os.path.join(font_dir, "OLEDDisplayFontsCN_16.cpp")
    if os.path.exists(font_16_file):
        with open(font_16_file, 'r', encoding='utf-8') as f:
            content = f.read()
            if "ArialMT_Plain_16_CN" in content and "PROGMEM" in content:
                print("✅ 16pt字体文件格式正确")
                
                # 统计字符数量
                char_count = content.count("// 一 (U+")
                print(f"   包含 {char_count} 个字符")
            else:
                print("❌ 16pt字体文件格式不正确")

def test_character_coverage():
    """测试字符覆盖范围"""
    print("\n检查字符覆盖范围...")
    
    # 读取常用字表
    char_file = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/常用字表.txt"
    if os.path.exists(char_file):
        with open(char_file, 'r', encoding='utf-8') as f:
            lines = f.readlines()
        
        chars = []
        for line in lines:
            line = line.strip()
            if line and not line.startswith('#'):
                for char in line:
                    if char and ord(char) > 127:
                        chars.append(char)
        
        print(f"常用字表包含 {len(chars)} 个字符")
        
        # 检查字体文件中的字符
        font_16_file = "/Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware/src/graphics/fonts/OLEDDisplayFontsCN_16.cpp"
        if os.path.exists(font_16_file):
            with open(font_16_file, 'r', encoding='utf-8') as f:
                content = f.read()
            
            found_chars = 0
            for char in chars[:10]:  # 检查前10个字符
                if char in content:
                    found_chars += 1
                    print(f"✅ 找到字符: {char}")
                else:
                    print(f"❌ 未找到字符: {char}")
            
            print(f"前10个字符中找到 {found_chars} 个")

def main():
    print("中文字体测试")
    print("=" * 50)
    
    # 测试文件存在性
    if not test_font_files():
        print("\n❌ 字体文件不完整")
        return False
    
    # 测试文件内容
    test_font_content()
    
    # 测试字符覆盖
    test_character_coverage()
    
    print("\n✅ 中文字体测试完成")
    print("\n下一步:")
    print("1. 编译固件: ./bin/build-nrf52.sh nrf52_promicro_diy_tcxo")
    print("2. 烧录到设备进行实际测试")
    print("3. 在代码中使用: display->drawString(0, 0, \"中文测试\");")
    
    return True

if __name__ == "__main__":
    main()
