# CJK字体支持指南

## 概述

本固件现在支持完整的CJK（中日韩）字体显示功能，包括中文、日文、韩文字符的显示。通过U8g2图形库和文泉驿字体，提供了高质量的CJK字符渲染支持。

## 功能特性

### 🌏 多语言支持
- **中文**: 简体中文、繁体中文支持
- **日文**: 平假名、片假名、汉字支持
- **韩文**: 韩文字符支持
- **自动检测**: 智能语言检测和字体选择

### 📏 多种字体大小
- **小字体**: 10px (适合小屏幕)
- **中字体**: 12px (默认大小)
- **大字体**: 14px (适合大屏幕)

### 🎨 字体特性
- **文泉驿字体**: 专为嵌入式设备优化
- **UTF-8编码**: 完整Unicode支持
- **高质量渲染**: 清晰的字符显示
- **内存优化**: 高效的字体存储

## 使用方法

### 基本用法

```cpp
#include "U8g2ChineseFonts.h"

// 获取U8g2对象
U8G2* u8g2 = display->getU8g2();

// 显示中文字符
drawChineseString(u8g2, 0, 20, "你好世界");

// 显示日文字符
drawJapaneseString(u8g2, 0, 35, "こんにちは");

// 显示韩文字符
drawKoreanString(u8g2, 0, 50, "안녕하세요");
```

### 自动语言检测

```cpp
// 自动检测语言并选择合适字体
drawCJKString(u8g2, 0, 20, "你好世界");        // 自动检测为中文
drawCJKString(u8g2, 0, 35, "こんにちは");      // 自动检测为日文
drawCJKString(u8g2, 0, 50, "안녕하세요");      // 自动检测为韩文
```

### 指定字体大小

```cpp
// 使用不同字体大小
drawChineseString(u8g2, 0, 20, "小字体", CJKFontSize::SMALL);
drawChineseString(u8g2, 0, 35, "中字体", CJKFontSize::MEDIUM);
drawChineseString(u8g2, 0, 50, "大字体", CJKFontSize::LARGE);
```

### 字符串宽度计算

```cpp
// 计算字符串宽度
int16_t width = getCJKStringWidth(u8g2, "你好世界");
Serial.print("字符串宽度: ");
Serial.println(width);
```

## API参考

### 字体设置函数

```cpp
// 设置中文字体
void setupChineseFont(U8G2* u8g2);

// 设置CJK字体（支持自动检测）
void setupCJKFont(U8G2* u8g2, CJKLanguage language, CJKFontSize size);

// 设置日文字体
void setupJapaneseFont(U8G2* u8g2, CJKFontSize size);

// 设置韩文字体
void setupKoreanFont(U8G2* u8g2, CJKFontSize size);
```

### 字符串绘制函数

```cpp
// 通用CJK字符串绘制
void drawCJKString(U8G2* u8g2, int16_t x, int16_t y, const char* text, 
                   CJKLanguage language, CJKFontSize size);

// 中文字符串绘制
void drawChineseString(U8G2* u8g2, int16_t x, int16_t y, const char* text, 
                      CJKFontSize size);

// 日文字符串绘制
void drawJapaneseString(U8G2* u8g2, int16_t x, int16_t y, const char* text, 
                        CJKFontSize size);

// 韩文字符串绘制
void drawKoreanString(U8G2* u8g2, int16_t x, int16_t y, const char* text, 
                      CJKFontSize size);
```

### 语言检测函数

```cpp
// 检测文本语言
CJKLanguage detectCJKLanguage(const char* text);
CJKLanguage detectCJKLanguage(String text);
```

### 字符串宽度函数

```cpp
// 计算CJK字符串宽度
int16_t getCJKStringWidth(U8G2* u8g2, const char* text, 
                          CJKLanguage language, CJKFontSize size);
```

## 枚举类型

### CJKLanguage (语言类型)
```cpp
enum class CJKLanguage {
    CHINESE,    // 中文
    JAPANESE,    // 日文
    KOREAN,      // 韩文
    AUTO         // 自动检测
};
```

### CJKFontSize (字体大小)
```cpp
enum class CJKFontSize {
    SMALL = 10,   // 小字体
    MEDIUM = 12,  // 中字体
    LARGE = 14    // 大字体
};
```

## 字体配置

### 可用字体

| 语言 | 小字体 (10px) | 中字体 (12px) | 大字体 (14px) |
|------|---------------|---------------|---------------|
| 中文 | `u8g2_font_wqy10_t_chinese1` | `u8g2_font_wqy12_t_chinese1` | `u8g2_font_wqy14_t_chinese1` |
| 日文 | `u8g2_font_wqy10_t_japanese1` | `u8g2_font_wqy12_t_japanese1` | `u8g2_font_wqy14_t_japanese1` |
| 韩文 | `u8g2_font_wqy10_t_korean1` | `u8g2_font_wqy12_t_korean1` | `u8g2_font_wqy14_t_korean1` |

### 字体特性
- **文泉驿字体**: 开源中文字体，专为屏幕显示优化
- **点阵字体**: 适合小屏幕显示
- **UTF-8支持**: 完整Unicode字符集支持
- **内存效率**: 优化的字体存储格式

## 使用示例

### 基本显示示例

```cpp
void displayCJKText() {
    U8G2* u8g2 = display->getU8g2();
    
    // 清除显示缓冲区
    u8g2->clearBuffer();
    
    // 显示标题
    drawChineseString(u8g2, 0, 15, "设备状态", CJKFontSize::LARGE);
    
    // 显示设备信息
    drawChineseString(u8g2, 0, 30, "网络: 已连接", CJKFontSize::SMALL);
    drawChineseString(u8g2, 0, 45, "信号: 强", CJKFontSize::SMALL);
    drawChineseString(u8g2, 0, 60, "电池: 85%", CJKFontSize::SMALL);
    
    // 发送到显示器
    u8g2->sendBuffer();
}
```

### 多语言显示示例

```cpp
void displayMultiLanguage() {
    U8G2* u8g2 = display->getU8g2();
    
    u8g2->clearBuffer();
    
    // 显示不同语言的相同内容
    drawChineseString(u8g2, 0, 15, "设备状态", CJKFontSize::MEDIUM);
    drawJapaneseString(u8g2, 0, 30, "デバイス状態", CJKFontSize::MEDIUM);
    drawKoreanString(u8g2, 0, 45, "디바이스 상태", CJKFontSize::MEDIUM);
    
    u8g2->sendBuffer();
}
```

### 自动语言检测示例

```cpp
void displayAutoDetected() {
    U8G2* u8g2 = display->getU8g2();
    
    u8g2->clearBuffer();
    
    // 自动检测语言
    drawCJKString(u8g2, 0, 15, "你好世界");        // 自动检测为中文
    drawCJKString(u8g2, 0, 30, "こんにちは");      // 自动检测为日文
    drawCJKString(u8g2, 0, 45, "안녕하세요");      // 自动检测为韩文
    
    u8g2->sendBuffer();
}
```

## 测试功能

### 运行测试

```cpp
#include "U8g2CJKTest.h"

void setup() {
    Serial.begin(115200);
    
    // 运行所有CJK测试
    runAllCJKTests();
}

void loop() {
    // 实际显示测试
    testCJKDisplayWithU8g2(display->getU8g2());
    delay(5000);
}
```

### 测试函数

- `testChineseDisplay()`: 中文字符显示测试
- `testJapaneseDisplay()`: 日文字符显示测试
- `testKoreanDisplay()`: 韩文字符显示测试
- `testCJKFontSizes()`: 字体大小测试
- `testCJKLanguageDetection()`: 语言检测测试
- `testCJKStringWidth()`: 字符串宽度测试

## 性能优化

### 内存使用
- CJK字体占用约8-12KB Flash内存
- 运行时内存占用最小
- 支持字体缓存优化

### 渲染性能
- 高效的UTF-8解码
- 优化的字体查找算法
- 支持字体预加载

### 显示质量
- 清晰的字符渲染
- 支持反锯齿效果
- 优化的字符间距

## 故障排除

### 常见问题

1. **中文字符显示为问号**
   - 检查字体是否正确设置
   - 确认UTF-8编码正确
   - 验证字体文件完整性

2. **字符显示不完整**
   - 检查显示区域大小
   - 确认字体大小设置
   - 验证坐标位置正确

3. **性能问题**
   - 减少字体大小
   - 优化字符串长度
   - 使用字体缓存

### 调试方法

```cpp
// 启用调试输出
#define CJK_DEBUG 1

// 检查字体设置
void debugFontSettings(U8G2* u8g2) {
    Serial.println("字体设置调试:");
    Serial.print("当前字体: ");
    Serial.println((uintptr_t)u8g2->getFont());
    Serial.print("字体模式: ");
    Serial.println(u8g2->getFontMode());
}
```

## 更新日志

### v1.0.0 (当前版本)
- ✅ 基础CJK字体支持
- ✅ 中文、日文、韩文字符显示
- ✅ 自动语言检测
- ✅ 多种字体大小支持
- ✅ 完整的API接口
- ✅ 测试套件

### 计划功能
- 🔄 更多字体选择
- 🔄 字体缓存优化
- 🔄 动态字体加载
- 🔄 字体效果支持

## 技术支持

如有问题或建议，请参考：
- [U8g2官方文档](https://github.com/olikraus/u8g2)
- [文泉驿字体项目](http://wenq.org/)
- [项目GitHub仓库](https://github.com/vvlang/meshcn-firmware)

---

**注意**: 使用CJK字体会增加固件大小，请确保设备有足够的存储空间。建议在最终发布前进行充分测试。
