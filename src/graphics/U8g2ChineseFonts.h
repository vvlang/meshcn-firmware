#pragma once

#include <U8g2lib.h>

/**
 * U8g2中文字体配置
 * 
 * 这个文件提供了U8g2库的中文字体支持配置
 * 使用文泉驿点阵字体，专门为嵌入式设备优化
 */

// 中文字体选择
// 使用文泉驿字体支持中文显示
#define U8G2_CHINESE_FONT u8g2_font_wqy12_t_chinese1

// 字体配置函数声明
void setupChineseFont(U8G2* u8g2);

// 中文字符串绘制函数
inline void drawChineseString(U8G2* u8g2, int16_t x, int16_t y, const char* text) {
    if (!u8g2 || !text) return;
    
    setupChineseFont(u8g2);
    u8g2->drawUTF8(x, y, text);
}

// 中文字符串绘制函数（String版本）
inline void drawChineseString(U8G2* u8g2, int16_t x, int16_t y, String text) {
    if (!u8g2) return;
    
    setupChineseFont(u8g2);
    u8g2->drawUTF8(x, y, text.c_str());
}

// 获取中文字符串宽度
inline int16_t getChineseStringWidth(U8G2* u8g2, const char* text) {
    if (!u8g2 || !text) return 0;
    
    setupChineseFont(u8g2);
    return u8g2->getUTF8Width(text);
}

// 获取中文字符串宽度（String版本）
inline int16_t getChineseStringWidth(U8G2* u8g2, String text) {
    if (!u8g2) return 0;
    
    setupChineseFont(u8g2);
    return u8g2->getUTF8Width(text.c_str());
}
