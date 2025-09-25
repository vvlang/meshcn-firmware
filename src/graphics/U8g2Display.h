#pragma once

#include <OLEDDisplay.h>
#include <U8g2lib.h>
#include <stdint.h>

/**
 * An adapter class that allows using the U8g2 library as if it was an OLEDDisplay implementation.
 * 
 * This adapter provides a bridge between the U8g2 graphics library and the Meshtastic OLEDDisplay interface,
 * enabling support for various display controllers like SSD1306, SH1106, ST7567, etc.
 */
class U8g2Display : public OLEDDisplay
{
  public:
    /* constructor */
    U8g2Display(uint8_t, int, int, OLEDDISPLAY_GEOMETRY, HW_I2C);
    
    // Destructor to clean up allocated memory
    ~U8g2Display();

    // Write the buffer to the display memory
    virtual void display() override;
    
    // Turn the display upside down
    virtual void flipScreenVertically() override;
    
    // Clear the display
    virtual void clear() override;
    
    // Set display brightness
    void setDisplayBrightness(uint8_t brightness);
    
    // Set detected status
    void setDetected(uint8_t detected);

  protected:
    // the header size of the buffer used, e.g. for the SPI command header
    virtual int getBufferOffset(void) override { return 0; }

    // Send a command to the display (low level function)
    virtual void sendCommand(uint8_t com) override;

    // Connect to the display
    virtual bool connect() override;
    
    // Initialize the U8g2 display object
    virtual void initDisplay() = 0;
    
    // U8g2 display object
    U8G2 *u8g2 = nullptr;
    
    // Display configuration
    uint8_t displayType;
    int displayWidth;
    int displayHeight;
    OLEDDISPLAY_GEOMETRY geometry;
    HW_I2C i2c;
    
    // Display state
    bool isConnected = false;
    uint8_t brightness = 255;
};
