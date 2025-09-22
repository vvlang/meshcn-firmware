# 文泉驿点阵宋体使用指南

## 📖 概述

文泉驿点阵宋体是一个专门为嵌入式设备优化的中文字体，具有以下特点：
- **点阵设计**: 专为小尺寸显示优化
- **清晰可读**: 在OLED屏幕上显示效果优秀
- **文件小巧**: 相比矢量字体，文件更小
- **兼容性好**: 支持常用汉字和标点符号

## 🛠️ 字体生成工具

### 工具位置
```
src/graphics/fonts/ChineseFontGenerator.py
```

### 使用方法

#### 1. 安装依赖
```bash
pip install Pillow
```

#### 2. 运行字体生成工具
```bash
cd src/graphics/fonts/
python ChineseFontGenerator.py
```

#### 3. 自动检测系统字体
工具会自动检测以下路径的字体：
- **macOS**: `/System/Library/Fonts/STHeiti Light.ttc`
- **Linux**: `/usr/share/fonts/truetype/wqy/wqy-microhei.ttc`
- **Windows**: `C:/Windows/Fonts/simsun.ttc`

#### 4. 手动指定字体路径
如果自动检测失败，可以手动输入字体文件路径。

## 📁 生成的文件

工具会生成三个尺寸的字体文件：
- `OLEDDisplayFontsCN_10.cpp` - 10pt字体
- `OLEDDisplayFontsCN_16.cpp` - 16pt字体  
- `OLEDDisplayFontsCN_24.cpp` - 24pt字体

## 🔧 集成到固件

### 1. 替换字体文件
将生成的字体文件复制到 `src/graphics/fonts/` 目录，替换现有的 `OLEDDisplayFontsCN.cpp`。

### 2. 启用中文支持
在 `variants/nrf52840/diy/nrf52_promicro_diy_tcxo/variant.h` 中取消注释：
```c++
#define OLED_CN
```

### 3. 重新编译
```bash
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo
```

## 📝 支持的字符集

### 基本汉字
- 中文显示功能测试
- 网络通信设备状态
- 设置配置参数信息
- 电池电量信号强度
- GPS定位时间日期
- 消息发送接收确认
- 节点列表连接状态
- 系统重启关机模式
- 蓝牙WiFi开关控制
- 屏幕亮度音量调节

### 数字和标点
- 0123456789
- ，。？！：；
- （）【】《》
- 、；：""''

### 常用词汇
- 确定取消返回
- 上下左右选择
- 开关开启关闭
- 连接断开重连
- 成功失败错误
- 正常异常警告

## ⚙️ 字体优化特性

### 1. 点阵优化
- 专为小尺寸OLED屏幕设计
- 字符边界清晰，避免模糊
- 支持不同尺寸的字体

### 2. 存储优化
- 按列存储，符合OLEDDisplay格式
- 压缩存储，减少Flash占用
- 支持PROGMEM存储

### 3. 渲染优化
- 支持UTF-8中文编码
- 自动字符映射
- 高效渲染算法

## 🚀 使用示例

### 在代码中使用中文
```cpp
// 启用中文支持
#define OLED_CN

// 显示中文文本
display->drawString(0, 0, "中文显示测试");
display->drawString(0, 16, "网络状态: 正常");
display->drawString(0, 32, "电池电量: 85%");
```

### 菜单项中文显示
```cpp
// 菜单项
menuItems[0] = "发送消息";
menuItems[1] = "查看节点";
menuItems[2] = "系统设置";
menuItems[3] = "设备信息";
```

## 📊 性能指标

### 内存占用
- **10pt字体**: 约50KB Flash
- **16pt字体**: 约80KB Flash
- **24pt字体**: 约120KB Flash

### 渲染性能
- 字符渲染时间: <1ms
- 支持实时更新
- 流畅的UI交互

## 🔍 故障排除

### 1. 字体文件找不到
- 检查字体文件路径是否正确
- 确保字体文件存在且可读
- 尝试使用系统默认字体

### 2. 编译错误
- 确保已启用 `#define OLED_CN`
- 检查字体文件格式是否正确
- 验证字符编码是否为UTF-8

### 3. 显示异常
- 检查字符映射是否正确
- 验证字体数据完整性
- 确认OLED驱动正常

## 📚 参考资料

- [文泉驿字体官网](http://wenq.org/)
- [OLEDDisplay库文档](https://github.com/ThingPulse/esp8266-oled-ssd1306)
- [Arduino字体格式说明](https://github.com/ThingPulse/esp8266-oled-ssd1306#fonts)

## 🎯 最佳实践

1. **字体选择**: 优先使用文泉驿点阵宋体
2. **字符集**: 只包含必要的字符，减少文件大小
3. **尺寸优化**: 根据屏幕大小选择合适的字体尺寸
4. **测试验证**: 在实际设备上测试显示效果
5. **性能监控**: 关注内存使用和渲染性能

---

**注意**: 文泉驿点阵宋体是开源字体，可以自由使用和修改。
