#ifndef OLEDDISPLAYFONTSCN_h
#define OLEDDISPLAYFONTSCN_h

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#include <stdint.h>
#else
#include <stdint.h>
#define PROGMEM
#endif


// 中文字体声明
extern const uint8_t ArialMT_Plain_10_CN[] PROGMEM;


#endif
