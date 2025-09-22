#ifndef OLEDDISPLAYFONTSCN_h
#define OLEDDISPLAYFONTSCN_h

#include <stdint.h>

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#endif

/**
 * 中文字体支持 - 简体中文
 * 包含常用汉字和标点符号
 */
extern const uint8_t ArialMT_Plain_10_CN[] PROGMEM;
extern const uint8_t ArialMT_Plain_16_CN[] PROGMEM;
extern const uint8_t ArialMT_Plain_24_CN[] PROGMEM;

#endif
