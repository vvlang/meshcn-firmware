#include "configuration.h"
#include "U8g2Display.h"
#include "U8g2ChineseFonts.h"
#include "main.h"
#include <stdint.h>

U8g2Display::U8g2Display(uint8_t type, int width, int height, OLEDDISPLAY_GEOMETRY geo, HW_I2C i2cInterface)
    : OLEDDisplay()
{
    displayType = type;
    displayWidth = width;
    displayHeight = height;
    geometry = geo;
    i2c = i2cInterface;
    
    // Set geometry and initialize display
    setGeometry(geo, width, height);
}

U8g2Display::~U8g2Display()
{
    if (u8g2) {
        // 使用静态转换避免多态删除警告
        // U8G2的具体类型在子类中确定，这里删除是安全的
        U8G2* u8g2_ptr = u8g2;
        u8g2 = nullptr;
        delete u8g2_ptr;
    }
}

void U8g2Display::display()
{
    if (!u8g2 || !isConnected) {
        return;
    }
    
    // U8g2 manages its own buffer, so we just need to send it to the display
    u8g2->sendBuffer();
}

void U8g2Display::drawString(int16_t x, int16_t y, String text)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // Ensure Chinese font is set before drawing
    setupChineseFont(u8g2);

    // Use U8g2's UTF-8 support for Chinese characters
    u8g2->drawUTF8(x, y, text.c_str());
}

void U8g2Display::drawString(int16_t x, int16_t y, const char* text)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // Ensure Chinese font is set before drawing
    setupChineseFont(u8g2);

    // Use U8g2's UTF-8 support for Chinese characters
    u8g2->drawUTF8(x, y, text);
}

void U8g2Display::flipScreenVertically()
{
    if (u8g2) {
        u8g2->setFlipMode(1);
    }
}

void U8g2Display::clear()
{
    OLEDDisplay::clear();
    if (u8g2) {
        u8g2->clearBuffer();
    }
}

void U8g2Display::setDisplayBrightness(uint8_t brightness)
{
    this->brightness = brightness;
    if (u8g2) {
        // U8g2 doesn't have direct brightness control, but we can use contrast
        u8g2->setContrast(brightness);
    }
}

void U8g2Display::setDetected(uint8_t detected)
{
    // Implementation for detected status
    isConnected = (detected != 0);
}

void U8g2Display::sendCommand(uint8_t com)
{
    if (u8g2) {
        u8g2->sendF("c", com);
    }
}

bool U8g2Display::connect()
{
    if (u8g2) {
        u8g2->begin();
        isConnected = true;
        return true;
    }
    return false;
}

void U8g2Display::initDisplay()
{
    // This is a pure virtual function that must be implemented by derived classes
    // Each specific display type will implement this differently
}

// CJK-specific drawing methods
void U8g2Display::drawCJKString(int16_t x, int16_t y, String text, CJKLanguage language, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    ::drawCJKString(u8g2, x, y, text, language, size);
}

void U8g2Display::drawCJKString(int16_t x, int16_t y, const char* text, CJKLanguage language, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    ::drawCJKString(u8g2, x, y, text, language, size);
}

void U8g2Display::drawChineseString(int16_t x, int16_t y, String text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置中文字体
    setupChineseFont(u8g2);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text.c_str());
}

void U8g2Display::drawChineseString(int16_t x, int16_t y, const char* text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置中文字体
    setupChineseFont(u8g2);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text);
}

void U8g2Display::drawJapaneseString(int16_t x, int16_t y, String text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置日文字体
    setupJapaneseFont(u8g2, size);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text.c_str());
}

void U8g2Display::drawJapaneseString(int16_t x, int16_t y, const char* text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置日文字体
    setupJapaneseFont(u8g2, size);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text);
}

void U8g2Display::drawKoreanString(int16_t x, int16_t y, String text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置韩文字体
    setupKoreanFont(u8g2, size);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text.c_str());
}

void U8g2Display::drawKoreanString(int16_t x, int16_t y, const char* text, CJKFontSize size)
{
    if (!u8g2 || !isConnected) {
        return;
    }

    // 设置韩文字体
    setupKoreanFont(u8g2, size);
    
    // 绘制文本
    u8g2->drawUTF8(x, y, text);
}

int16_t U8g2Display::getCJKStringWidth(String text, CJKLanguage language, CJKFontSize size)
{
    if (!u8g2) return 0;
    
    // 设置CJK字体
    setupCJKFont(u8g2, language, size);
    
    // 计算文本宽度
    return u8g2->getUTF8Width(text.c_str());
}

int16_t U8g2Display::getCJKStringWidth(const char* text, CJKLanguage language, CJKFontSize size)
{
    if (!u8g2) return 0;
    
    // 设置CJK字体
    setupCJKFont(u8g2, language, size);
    
    // 计算文本宽度
    return u8g2->getUTF8Width(text);
}