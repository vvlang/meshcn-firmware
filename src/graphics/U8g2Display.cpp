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
        delete u8g2;
        u8g2 = nullptr;
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