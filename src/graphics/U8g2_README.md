# U8g2 Display Support

This document describes how to use U8g2 display library support in Meshtastic firmware.

## Overview

U8g2 is a powerful graphics library for embedded systems that supports a wide variety of display controllers including SSD1306, SH1106, ST7567, and many others. This implementation provides an adapter layer that allows U8g2 displays to work with the existing Meshtastic OLEDDisplay interface.

## Supported Displays

- **SSD1306**: 128x64, 128x32 OLED displays (I2C and SPI)
- **SH1106**: 128x64, 128x32 OLED displays (I2C and SPI)
- **ST7567**: 128x64 LCD displays (I2C and SPI)
- **And many more**: U8g2 supports over 200 display controllers

## Usage

### 1. Enable U8g2 Support

Add the following build flags to your platformio.ini:

```ini
build_flags = 
    -DUSE_U8G2_SSD1306  # For SSD1306 displays
    # or
    -DUSE_U8G2_SH1106   # For SH1106 displays
```

### 2. Configure Display Pins

Set the display pin configuration:

```ini
build_flags = 
    -DUSE_U8G2_SSD1306
    -DOLED_SDA=4      # I2C SDA pin
    -DOLED_SCL=11     # I2C SCL pin
    -DOLED_RST=-1     # Reset pin (-1 if not used)
    -DOLED_ADDR=0x3C  # I2C address
```

### 3. Example Configuration

For a Pro Micro compatible nRF52840 board with SSD1306 display:

```ini
[env:nrf52_promicro_diy_tcxo_u8g2]
extends = env:nrf52_promicro_diy_tcxo
build_flags = 
    ${env:nrf52_promicro_diy_tcxo.build_flags}
    -DUSE_U8G2_SSD1306
    -DOLED_SDA=4
    -DOLED_SCL=11
    -DOLED_RST=-1
    -DOLED_ADDR=0x3C
```

## Features

### Display Adapters

- **U8g2Display**: Base class providing OLEDDisplay interface
- **U8g2SSD1306Display**: SSD1306 specific implementation
- **U8g2SH1106Display**: SH1106 specific implementation

### Key Features

- **Full OLEDDisplay Compatibility**: Works with existing Meshtastic UI code
- **Multiple Display Support**: SSD1306, SH1106, and more
- **I2C and SPI Support**: Both communication protocols supported
- **Brightness Control**: Full brightness control support
- **Font Support**: Access to U8g2's extensive font library
- **Graphics Functions**: All U8g2 drawing functions available

## Technical Details

### Architecture

```
Meshtastic UI Layer
       ↓
OLEDDisplay Interface
       ↓
U8g2Display Adapter
       ↓
U8g2 Library
       ↓
Hardware Display
```

### Buffer Management

The U8g2Display adapter manages the display buffer and converts between OLEDDisplay format and U8g2 format during the display() call.

### Performance

U8g2 provides excellent performance with:
- Hardware-accelerated drawing functions
- Efficient buffer management
- Optimized display updates

## Adding New Display Types

To add support for a new display type:

1. Create a new display class inheriting from U8g2Display
2. Implement the initDisplay() method
3. Add the display type to Screen.h and Screen.cpp
4. Create build configuration flags

Example for ST7567:

```cpp
class U8g2ST7567Display : public U8g2Display
{
  public:
    U8g2ST7567Display(uint8_t, int, int, OLEDDISPLAY_GEOMETRY, HW_I2C);
    ~U8g2ST7567Display();

  protected:
    virtual void initDisplay() override;
};
```

## Troubleshooting

### Common Issues

1. **Display not detected**: Check I2C address and pin configuration
2. **No display output**: Verify display type and geometry settings
3. **Compilation errors**: Ensure U8g2 library is properly included

### Debug Tips

- Use I2C scanner to verify display address
- Check pin assignments in variant files
- Verify display geometry matches hardware
- Test with simple U8g2 examples first

## Examples

### Basic Usage

```cpp
// Display will be automatically initialized by Screen class
// No additional code needed in application
```

### Custom Drawing

```cpp
// Access U8g2 object for custom drawing
U8g2Display* u8g2Display = static_cast<U8g2Display*>(screen->getDisplayDevice());
U8G2* u8g2 = u8g2Display->getU8g2();

// Use U8g2 drawing functions
u8g2->setFont(u8g2_font_ncenB14_tr);
u8g2->drawStr(0, 20, "Hello U8g2!");
```

## Resources

- [U8g2 Library Documentation](https://github.com/olikraus/u8g2)
- [U8g2 Reference Manual](https://github.com/olikraus/u8g2/wiki)
- [Display Controller List](https://github.com/olikraus/u8g2/wiki/u8g2setupcpp)
