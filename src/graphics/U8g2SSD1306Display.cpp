#include "configuration.h"
#include "U8g2SSD1306Display.h"
#include "U8g2ChineseFonts.h"

U8g2SSD1306Display::U8g2SSD1306Display(uint8_t type, int width, int height, OLEDDISPLAY_GEOMETRY geo, HW_I2C i2cInterface)
    : U8g2Display(type, width, height, geo, i2cInterface)
{
    initDisplay();
}

U8g2SSD1306Display::~U8g2SSD1306Display()
{
    // Cleanup handled by base class
}

void U8g2SSD1306Display::initDisplay()
{
    // Initialize U8g2 SSD1306 display based on geometry and interface
    if (geometry == GEOMETRY_128_64) {
        if (i2c == I2C_ONE) {
            u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
        } else {
            // SPI interface
            u8g2 = new U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI(U8G2_R0, /* cs=*/ U8X8_PIN_NONE, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
        }
    } else if (geometry == GEOMETRY_128_32) {
        if (i2c == I2C_ONE) {
            u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
        } else {
            // SPI interface
            u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_4W_HW_SPI(U8G2_R0, /* cs=*/ U8X8_PIN_NONE, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
        }
    } else {
        // Default to 128x64
        if (i2c == I2C_ONE) {
            u8g2 = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
        } else {
            u8g2 = new U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI(U8G2_R0, /* cs=*/ U8X8_PIN_NONE, /* dc=*/ U8X8_PIN_NONE, /* reset=*/ U8X8_PIN_NONE);
        }
    }
    
           if (u8g2) {
               u8g2->begin();
               u8g2->setContrast(255);
               u8g2->setFlipMode(0);

               // 设置中文字体支持
               setupChineseFont(u8g2);
           }
}