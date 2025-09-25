/**
 * U8g2中文字符显示测试程序
 * 
 * 这个文件演示如何使用U8g2显示中文文本
 * 用于验证中文字符显示功能是否正常工作
 */

#include "U8g2ChineseFonts.h"
#include <U8g2lib.h>

/**
 * 测试基本中文字符显示
 * 这个函数演示了如何使用U8g2显示中文文本
 */
void testBasicChineseDisplay() {
    // 创建U8g2对象进行测试
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
    
    // 初始化显示
    u8g2.begin();
    u8g2.setContrast(255);
    
    // 设置中文字体
    setupChineseFont(&u8g2);
    
    // 清空屏幕
    u8g2.clearBuffer();
    
    // 显示中文文本
    u8g2.drawUTF8(0, 15, "你好世界");  // Hello World in Chinese
    u8g2.drawUTF8(0, 30, "测试中文");  // Test Chinese
    u8g2.drawUTF8(0, 45, "显示正常");  // Display Normal
    u8g2.drawUTF8(0, 60, "U8g2支持");  // U8g2 Support
    
    // 发送到显示器
    u8g2.sendBuffer();
}

/**
 * 测试使用drawChineseString函数
 * 这个函数演示了如何使用封装的中文字符串绘制函数
 */
void testChineseStringFunctions() {
    // 创建U8g2对象进行测试
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
    
    // 初始化显示
    u8g2.begin();
    u8g2.setContrast(255);
    
    // 清空屏幕
    u8g2.clearBuffer();
    
    // 使用封装的中文字符串绘制函数
    drawChineseString(&u8g2, 0, 15, "你好世界");
    drawChineseString(&u8g2, 0, 30, "测试中文");
    drawChineseString(&u8g2, 0, 45, "显示正常");
    drawChineseString(&u8g2, 0, 60, "U8g2支持");
    
    // 发送到显示器
    u8g2.sendBuffer();
}

/**
 * 测试中文字符串宽度计算
 * 这个函数演示了如何计算中文字符串的显示宽度
 */
void testChineseStringWidth() {
    // 创建U8g2对象进行测试
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
    
    // 初始化显示
    u8g2.begin();
    u8g2.setContrast(255);
    
    // 设置中文字体
    setupChineseFont(&u8g2);
    
    // 测试中文字符串宽度
    String testText = "你好世界";
    int16_t width = getChineseStringWidth(&u8g2, testText);
    
    // 在屏幕上显示宽度信息
    u8g2.clearBuffer();
    u8g2.drawUTF8(0, 15, "宽度测试:");
    u8g2.drawUTF8(0, 30, testText.c_str());
    
    // 显示宽度数值
    char widthStr[20];
    snprintf(widthStr, sizeof(widthStr), "宽度: %d", width);
    u8g2.drawUTF8(0, 45, widthStr);
    
    // 发送到显示器
    u8g2.sendBuffer();
}

/**
 * 测试混合中英文显示
 * 这个函数演示了如何同时显示中文和英文字符
 */
void testMixedLanguageDisplay() {
    // 创建U8g2对象进行测试
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
    
    // 初始化显示
    u8g2.begin();
    u8g2.setContrast(255);
    
    // 设置中文字体
    setupChineseFont(&u8g2);
    
    // 清空屏幕
    u8g2.clearBuffer();
    
    // 显示混合语言文本
    u8g2.drawUTF8(0, 15, "Hello 世界");  // Hello World mixed
    u8g2.drawUTF8(0, 30, "Test 测试");   // Test mixed
    u8g2.drawUTF8(0, 45, "Display 显示"); // Display mixed
    u8g2.drawUTF8(0, 60, "U8g2 支持");   // U8g2 Support mixed
    
    // 发送到显示器
    u8g2.sendBuffer();
}