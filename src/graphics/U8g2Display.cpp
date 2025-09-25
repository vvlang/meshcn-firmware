#include "configuration.h"
#include "U8g2Display.h"
#include "main.h"
#include <stdint.h>

U8g2Display::U8g2Display(uint8_t type, int width, int height, OLEDDISPLAY_GEOMETRY geo, HW_I2C i2cInterface)
    : OLEDDisplay(width, height)
{
    displayType = type;
    displayWidth = width;
    displayHeight = height;
    geometry = geo;
    i2c = i2cInterface;
    
    // Initialize the display buffer
    setBuffer(nullptr, width, height);
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
    
    // Convert OLEDDisplay buffer to U8g2 format and display
    u8g2->firstPage();
    do {
        // Draw each pixel from the buffer
        for (int y = 0; y < displayHeight; y++) {
            for (int x = 0; x < displayWidth; x++) {
                if (getPixel(x, y) == WHITE) {
                    u8g2->drawPixel(x, y);
                }
            }
        }
    } while (u8g2->nextPage());
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
