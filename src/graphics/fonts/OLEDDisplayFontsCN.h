#ifndef OLEDDISPLAYFONTSCN_h
#define OLEDDISPLAYFONTSCN_h

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#endif

#ifdef OLED_CN

// 中文字体声明
extern const uint8_t ArialMT_Plain_10_CN[] PROGMEM;
extern const uint8_t ArialMT_Plain_16_CN[] PROGMEM;
extern const uint8_t ArialMT_Plain_24_CN[] PROGMEM;

#endif // OLED_CN

#endif
