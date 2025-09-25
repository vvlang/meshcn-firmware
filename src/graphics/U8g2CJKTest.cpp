#include "U8g2CJKTest.h"
#include "U8g2ChineseFonts.h"
#include <U8g2lib.h>

/**
 * U8g2 CJK字体测试程序
 * 
 * 这个文件提供了CJK（中日韩）字体显示功能的测试
 * 包括中文、日文、韩文字符的显示测试
 */

void testCJKDisplay() {
    // 测试基本CJK字符显示
    Serial.println("=== CJK字体显示测试 ===");
    
    // 这里需要实际的U8g2对象，在实际使用中会从显示器获取
    // 这个函数主要用于演示API用法
}

void testChineseDisplay() {
    Serial.println("=== 中文字符显示测试 ===");
    
    // 测试中文字符串
    const char* chineseTexts[] = {
        "你好世界",           // Hello World
        "测试中文显示",       // Test Chinese Display
        "网格网络",           // Mesh Network
        "设备状态",           // Device Status
        "信号强度",           // Signal Strength
        "电池电量",           // Battery Level
        "温度传感器",         // Temperature Sensor
        "GPS定位",            // GPS Location
        "消息传输",           // Message Transmission
        "网络配置"            // Network Configuration
    };
    
    Serial.println("中文字符串测试:");
    for (int i = 0; i < 10; i++) {
        Serial.print("  ");
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(chineseTexts[i]);
    }
}

void testJapaneseDisplay() {
    Serial.println("=== 日文字符显示测试 ===");
    
    // 测试日文字符串
    const char* japaneseTexts[] = {
        "こんにちは世界",     // Hello World
        "テスト表示",         // Test Display
        "メッシュネットワーク", // Mesh Network
        "デバイス状態",       // Device Status
        "信号強度",           // Signal Strength
        "バッテリー残量",     // Battery Level
        "温度センサー",       // Temperature Sensor
        "GPS位置",            // GPS Location
        "メッセージ送信",     // Message Transmission
        "ネットワーク設定"    // Network Configuration
    };
    
    Serial.println("日文字符串测试:");
    for (int i = 0; i < 10; i++) {
        Serial.print("  ");
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(japaneseTexts[i]);
    }
}

void testKoreanDisplay() {
    Serial.println("=== 韩文字符显示测试 ===");
    
    // 测试韩文字符串
    const char* koreanTexts[] = {
        "안녕하세요 세계",    // Hello World
        "테스트 표시",        // Test Display
        "메시 네트워크",      // Mesh Network
        "디바이스 상태",      // Device Status
        "신호 강도",          // Signal Strength
        "배터리 잔량",        // Battery Level
        "온도 센서",          // Temperature Sensor
        "GPS 위치",           // GPS Location
        "메시지 전송",        // Message Transmission
        "네트워크 설정"       // Network Configuration
    };
    
    Serial.println("韩文字符串测试:");
    for (int i = 0; i < 10; i++) {
        Serial.print("  ");
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(koreanTexts[i]);
    }
}

void testCJKFontSizes() {
    Serial.println("=== CJK字体大小测试 ===");
    
    const char* testText = "测试字体大小";
    
    Serial.println("字体大小测试:");
    Serial.println("  小字体 (10px): " + String(testText));
    Serial.println("  中字体 (12px): " + String(testText));
    Serial.println("  大字体 (14px): " + String(testText));
}

void testCJKLanguageDetection() {
    Serial.println("=== CJK语言检测测试 ===");
    
    const char* testTexts[] = {
        "你好世界",           // Chinese
        "こんにちは",         // Japanese
        "안녕하세요",         // Korean
        "Hello World",        // English
        "测试混合文本",       // Mixed
        "テスト混合",         // Mixed
        "테스트混合"          // Mixed
    };
    
    Serial.println("语言检测测试:");
    for (int i = 0; i < 7; i++) {
        CJKLanguage detected = detectCJKLanguage(testTexts[i]);
        String languageName = "";
        
        switch (detected) {
            case CJKLanguage::CHINESE:
                languageName = "中文";
                break;
            case CJKLanguage::JAPANESE:
                languageName = "日文";
                break;
            case CJKLanguage::KOREAN:
                languageName = "韩文";
                break;
            case CJKLanguage::AUTO:
                languageName = "自动";
                break;
        }
        
        Serial.print("  ");
        Serial.print(testTexts[i]);
        Serial.print(" -> ");
        Serial.println(languageName);
    }
}

void testCJKStringWidth() {
    Serial.println("=== CJK字符串宽度测试 ===");
    
    const char* testTexts[] = {
        "你好世界",
        "こんにちは世界",
        "안녕하세요 세계",
        "测试文本宽度",
        "テキスト幅テスト",
        "텍스트 너비 테스트"
    };
    
    Serial.println("字符串宽度测试:");
    for (int i = 0; i < 6; i++) {
        Serial.print("  ");
        Serial.print(testTexts[i]);
        Serial.print(" -> 宽度: ");
        // 在实际使用中，这里会调用getCJKStringWidth函数
        Serial.println("需要实际U8g2对象");
    }
}

void runAllCJKTests() {
    Serial.println("\n=== 开始CJK字体完整测试 ===");
    
    testChineseDisplay();
    Serial.println();
    
    testJapaneseDisplay();
    Serial.println();
    
    testKoreanDisplay();
    Serial.println();
    
    testCJKFontSizes();
    Serial.println();
    
    testCJKLanguageDetection();
    Serial.println();
    
    testCJKStringWidth();
    Serial.println();
    
    Serial.println("=== CJK字体测试完成 ===");
}

// 实际显示测试函数（需要U8g2对象）
void testCJKDisplayWithU8g2(U8G2* u8g2) {
    if (!u8g2) {
        Serial.println("错误: U8g2对象为空");
        return;
    }
    
    Serial.println("=== 使用U8g2对象进行CJK显示测试 ===");
    
    // 清除显示缓冲区
    u8g2->clearBuffer();
    
    // 测试中文字符
    drawChineseString(u8g2, 0, 15, "你好世界");
    drawChineseString(u8g2, 0, 30, "测试中文");
    drawChineseString(u8g2, 0, 45, "网格网络");
    
    // 测试日文字符
    drawJapaneseString(u8g2, 0, 60, "こんにちは");
    
    // 测试韩文字符
    drawKoreanString(u8g2, 0, 75, "안녕하세요");
    
    // 发送到显示器
    u8g2->sendBuffer();
    
    Serial.println("CJK显示测试完成");
}

// 混合语言显示测试
void testMixedLanguageDisplay(U8G2* u8g2) {
    if (!u8g2) {
        Serial.println("错误: U8g2对象为空");
        return;
    }
    
    Serial.println("=== 混合语言显示测试 ===");
    
    u8g2->clearBuffer();
    
    // 显示不同语言的相同内容
    drawChineseString(u8g2, 0, 15, "设备状态");
    drawJapaneseString(u8g2, 0, 30, "デバイス状態");
    drawKoreanString(u8g2, 0, 45, "디바이스 상태");
    
    // 显示网络信息
    drawChineseString(u8g2, 0, 60, "网络: 已连接");
    drawChineseString(u8g2, 0, 75, "信号: 强");
    
    u8g2->sendBuffer();
    
    Serial.println("混合语言显示测试完成");
}
