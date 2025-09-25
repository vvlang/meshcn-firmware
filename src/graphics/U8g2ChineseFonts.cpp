#include "U8g2ChineseFonts.h"

void setupChineseFont(U8G2* u8g2) {
    if (!u8g2) return;
    
    // 设置中文字体
    u8g2->setFont(u8g2_font_wqy12_t_chinese1);  // 文泉驿字体，支持中文
    
    // 设置字体模式
    u8g2->setFontMode(0);  // 透明模式
    u8g2->setFontDirection(0);  // 从左到右
    
    // 设置字体颜色
    u8g2->setDrawColor(1);  // 白色文字
}

// drawChineseString functions are already defined inline in the header file
