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

void setupCJKFont(U8G2* u8g2, CJKLanguage language, CJKFontSize size) {
    if (!u8g2) return;
    
    // 根据语言和大小选择字体
    const uint8_t* font = nullptr;
    
    if (language == CJKLanguage::AUTO) {
        // 自动检测时使用通用CJK字体
        switch (size) {
            case CJKFontSize::SMALL:
                font = U8G2_CJK_FONT_10;
                break;
            case CJKFontSize::MEDIUM:
                font = U8G2_CJK_FONT;
                break;
            case CJKFontSize::LARGE:
                font = U8G2_CJK_FONT_14;
                break;
        }
    } else if (language == CJKLanguage::CHINESE) {
        switch (size) {
            case CJKFontSize::SMALL:
                font = U8G2_CHINESE_FONT_10;
                break;
            case CJKFontSize::MEDIUM:
                font = U8G2_CHINESE_FONT;
                break;
            case CJKFontSize::LARGE:
                font = U8G2_CHINESE_FONT_14;
                break;
        }
    } else if (language == CJKLanguage::JAPANESE) {
        switch (size) {
            case CJKFontSize::SMALL:
                font = U8G2_JAPANESE_FONT_10;
                break;
            case CJKFontSize::MEDIUM:
                font = U8G2_JAPANESE_FONT;
                break;
            case CJKFontSize::LARGE:
                font = U8G2_JAPANESE_FONT_14;
                break;
        }
    } else if (language == CJKLanguage::KOREAN) {
        switch (size) {
            case CJKFontSize::SMALL:
                font = U8G2_KOREAN_FONT_10;
                break;
            case CJKFontSize::MEDIUM:
                font = U8G2_KOREAN_FONT;
                break;
            case CJKFontSize::LARGE:
                font = U8G2_KOREAN_FONT_14;
                break;
        }
    }
    
    // 设置字体
    if (font) {
        u8g2->setFont(font);
    } else {
        // 默认使用中文字体
        u8g2->setFont(U8G2_CHINESE_FONT);
    }
    
    // 设置字体模式
    u8g2->setFontMode(0);  // 透明模式
    u8g2->setFontDirection(0);  // 从左到右
    
    // 设置字体颜色
    u8g2->setDrawColor(1);  // 白色文字
}

void setupJapaneseFont(U8G2* u8g2, CJKFontSize size) {
    setupCJKFont(u8g2, CJKLanguage::JAPANESE, size);
}

void setupKoreanFont(U8G2* u8g2, CJKFontSize size) {
    setupCJKFont(u8g2, CJKLanguage::KOREAN, size);
}

CJKLanguage detectCJKLanguage(const char* text) {
    if (!text) return CJKLanguage::AUTO;
    
    // 简单的语言检测逻辑
    // 检测日文平假名、片假名
    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char c1 = (unsigned char)text[i];
        unsigned char c2 = (unsigned char)text[i + 1];
        
        // 检测日文平假名 (U+3040-U+309F)
        if (c1 == 0xE3 && c2 >= 0x81 && c2 <= 0x9F) {
            return CJKLanguage::JAPANESE;
        }
        // 检测日文片假名 (U+30A0-U+30FF)
        if (c1 == 0xE3 && c2 >= 0x82 && c2 <= 0xBF) {
            return CJKLanguage::JAPANESE;
        }
        // 检测韩文 (U+AC00-U+D7AF)
        if (c1 == 0xEA && c2 >= 0xB0 && c2 <= 0xBF) {
            return CJKLanguage::KOREAN;
        }
        if (c1 == 0xEB && c2 >= 0x80 && c2 <= 0xAF) {
            return CJKLanguage::KOREAN;
        }
    }
    
    // 默认返回中文
    return CJKLanguage::CHINESE;
}

CJKLanguage detectCJKLanguage(String text) {
    return detectCJKLanguage(text.c_str());
}
