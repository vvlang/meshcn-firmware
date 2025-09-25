#pragma once

#include "U8g2Display.h"

/**
 * U8g2 adapter for SSD1306 OLED displays
 * Supports both I2C and SPI communication protocols
 */
class U8g2SSD1306Display : public U8g2Display
{
  public:
    U8g2SSD1306Display(uint8_t, int, int, OLEDDISPLAY_GEOMETRY, HW_I2C);
    ~U8g2SSD1306Display();

  protected:
    virtual void initDisplay() override;
};
