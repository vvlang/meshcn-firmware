#pragma once

#include <U8g2lib.h>
#include <Arduino.h>

/**
 * U8g2 CJK字体配置
 * 
 * 这个文件提供了U8g2库的CJK（中日韩）字体支持配置
 * 支持中文、日文、韩文字符显示
 */

// CJK字体选择 - 使用U8g2库中实际可用的字体
// 文泉驿字体 - 中文支持
#define U8G2_CHINESE_FONT u8g2_font_wqy12_t_chinese1
#define U8G2_CHINESE_FONT_10 u8g2_font_wqy12_t_chinese1  // 使用12px字体作为小字体
#define U8G2_CHINESE_FONT_14 u8g2_font_wqy12_t_chinese1  // 使用12px字体作为大字体

// 日文字体支持 - 使用中文字体作为基础
#define U8G2_JAPANESE_FONT u8g2_font_wqy12_t_chinese1
#define U8G2_JAPANESE_FONT_10 u8g2_font_wqy12_t_chinese1
#define U8G2_JAPANESE_FONT_14 u8g2_font_wqy12_t_chinese1

// 韩文字体支持 - 使用中文字体作为基础
#define U8G2_KOREAN_FONT u8g2_font_wqy12_t_chinese1
#define U8G2_KOREAN_FONT_10 u8g2_font_wqy12_t_chinese1
#define U8G2_KOREAN_FONT_14 u8g2_font_wqy12_t_chinese1

// 通用CJK字体（支持中日韩）
#define U8G2_CJK_FONT u8g2_font_wqy12_t_chinese1
#define U8G2_CJK_FONT_10 u8g2_font_wqy12_t_chinese1
#define U8G2_CJK_FONT_14 u8g2_font_wqy12_t_chinese1

// 字体大小枚举
enum class CJKFontSize {
    SMALL = 10,
    MEDIUM = 12,
    LARGE = 14
};

// 语言类型枚举
enum class CJKLanguage {
    CHINESE,
    JAPANESE,
    KOREAN,
    AUTO  // 自动检测
};

// 字体配置函数声明
void setupChineseFont(U8G2* u8g2);
void setupCJKFont(U8G2* u8g2, CJKLanguage language = CJKLanguage::AUTO, CJKFontSize size = CJKFontSize::MEDIUM);
void setupJapaneseFont(U8G2* u8g2, CJKFontSize size = CJKFontSize::MEDIUM);
void setupKoreanFont(U8G2* u8g2, CJKFontSize size = CJKFontSize::MEDIUM);

// 语言检测函数
CJKLanguage detectCJKLanguage(const char* text);
CJKLanguage detectCJKLanguage(String text);

// CJK字符串绘制函数
inline void drawCJKString(U8G2* u8g2, int16_t x, int16_t y, const char* text, CJKLanguage language = CJKLanguage::AUTO, CJKFontSize size = CJKFontSize::MEDIUM) {
    if (!u8g2 || !text) return;
    
    setupCJKFont(u8g2, language, size);
    u8g2->drawUTF8(x, y, text);
}

// CJK字符串绘制函数（String版本）
inline void drawCJKString(U8G2* u8g2, int16_t x, int16_t y, String text, CJKLanguage language = CJKLanguage::AUTO, CJKFontSize size = CJKFontSize::MEDIUM) {
    if (!u8g2) return;
    
    setupCJKFont(u8g2, language, size);
    u8g2->drawUTF8(x, y, text.c_str());
}

// 中文字符串绘制函数（保持向后兼容）
inline void drawChineseString(U8G2* u8g2, int16_t x, int16_t y, const char* text) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::CHINESE, CJKFontSize::MEDIUM);
}

// 中文字符串绘制函数（String版本，保持向后兼容）
inline void drawChineseString(U8G2* u8g2, int16_t x, int16_t y, String text) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::CHINESE, CJKFontSize::MEDIUM);
}

// 日文字符串绘制函数
inline void drawJapaneseString(U8G2* u8g2, int16_t x, int16_t y, const char* text, CJKFontSize size = CJKFontSize::MEDIUM) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::JAPANESE, size);
}

inline void drawJapaneseString(U8G2* u8g2, int16_t x, int16_t y, String text, CJKFontSize size = CJKFontSize::MEDIUM) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::JAPANESE, size);
}

// 韩文字符串绘制函数
inline void drawKoreanString(U8G2* u8g2, int16_t x, int16_t y, const char* text, CJKFontSize size = CJKFontSize::MEDIUM) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::KOREAN, size);
}

inline void drawKoreanString(U8G2* u8g2, int16_t x, int16_t y, String text, CJKFontSize size = CJKFontSize::MEDIUM) {
    drawCJKString(u8g2, x, y, text, CJKLanguage::KOREAN, size);
}

// 获取CJK字符串宽度
inline int16_t getCJKStringWidth(U8G2* u8g2, const char* text, CJKLanguage language = CJKLanguage::AUTO, CJKFontSize size = CJKFontSize::MEDIUM) {
    if (!u8g2 || !text) return 0;
    
    setupCJKFont(u8g2, language, size);
    return u8g2->getUTF8Width(text);
}

// 获取CJK字符串宽度（String版本）
inline int16_t getCJKStringWidth(U8G2* u8g2, String text, CJKLanguage language = CJKLanguage::AUTO, CJKFontSize size = CJKFontSize::MEDIUM) {
    if (!u8g2) return 0;
    
    setupCJKFont(u8g2, language, size);
    return u8g2->getUTF8Width(text.c_str());
}

// 获取中文字符串宽度（保持向后兼容）
inline int16_t getChineseStringWidth(U8G2* u8g2, const char* text) {
    return getCJKStringWidth(u8g2, text, CJKLanguage::CHINESE, CJKFontSize::MEDIUM);
}

// 获取中文字符串宽度（String版本，保持向后兼容）
inline int16_t getChineseStringWidth(U8G2* u8g2, String text) {
    return getCJKStringWidth(u8g2, text, CJKLanguage::CHINESE, CJKFontSize::MEDIUM);
}
