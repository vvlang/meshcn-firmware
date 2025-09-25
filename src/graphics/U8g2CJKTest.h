#pragma once

#include <U8g2lib.h>
#include "U8g2ChineseFonts.h"

/**
 * U8g2 CJK字体测试头文件
 * 
 * 这个文件提供了CJK（中日韩）字体显示功能的测试函数声明
 */

// 基本测试函数
void testCJKDisplay();
void testChineseDisplay();
void testJapaneseDisplay();
void testKoreanDisplay();
void testCJKFontSizes();
void testCJKLanguageDetection();
void testCJKStringWidth();

// 完整测试套件
void runAllCJKTests();

// 实际显示测试函数（需要U8g2对象）
void testCJKDisplayWithU8g2(U8G2* u8g2);
void testMixedLanguageDisplay(U8G2* u8g2);

// 性能测试函数
void testCJKPerformance(U8G2* u8g2);
void testCJKMemoryUsage();

// 字体渲染质量测试
void testCJKFontQuality(U8G2* u8g2);
void testCJKFontRendering(U8G2* u8g2);

// 多语言混合显示测试
void testMultiLanguageDisplay(U8G2* u8g2);
void testCJKTextAlignment(U8G2* u8g2);

// 错误处理测试
void testCJKErrorHandling(U8G2* u8g2);
void testCJKInvalidInput(U8G2* u8g2);
