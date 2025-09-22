# P1.00 双击重启功能添加

## 📋 修改概述

为 nRF52 ProMicro DIY 板的 P1.00 主按钮添加了双击重启设备的功能。

## 🔧 修改内容

### 修改的文件
- `src/main.cpp` - 主按钮配置

### 具体修改

#### 1. 有屏幕配置 (userConfig)
```cpp
userConfig.singlePress = INPUT_BROKER_SELECT;      // 短按：确认
userConfig.longPress = INPUT_BROKER_SHUTDOWN;       // 长按：关机
userConfig.longPressTime = 3000;                   // 长按时间：3秒
userConfig.longLongPress = INPUT_BROKER_NONE;      // 超长按：无
userConfig.doublePress = INPUT_BROKER_MSG_REBOOT;  // 双击：重启设备 ✅ 新增
```

#### 2. 无屏幕配置 (userConfigNoScreen)
```cpp
userConfigNoScreen.singlePress = INPUT_BROKER_SELECT;      // 短按：确认
userConfigNoScreen.longPress = INPUT_BROKER_SHUTDOWN;     // 长按：关机
userConfigNoScreen.longPressTime = 3000;                  // 长按时间：3秒
userConfigNoScreen.longLongPress = INPUT_BROKER_NONE;     // 超长按：无
userConfigNoScreen.doublePress = INPUT_BROKER_MSG_REBOOT; // 双击：重启设备 ✅ 新增
userConfigNoScreen.triplePress = INPUT_BROKER_NONE;      // 三击：无
```

## 🎯 功能说明

### P1.00 按钮功能总结
| 操作 | 功能 | 说明 |
|------|------|------|
| **短按** | 确认 (SELECT) | 选择菜单项、确认操作 |
| **长按 (3秒)** | 关机 (SHUTDOWN) | 安全关闭设备 |
| **双击** | 重启 (REBOOT) | 重启设备 ✅ 新增 |
| **三击** | 无 | 保留为无功能 |

### 重启功能特性
- **触发方式**: 双击 P1.00 按钮
- **响应时间**: 双击间隔在系统默认时间内
- **执行动作**: 发送 `INPUT_BROKER_MSG_REBOOT` 消息
- **系统处理**: 由 `SystemCommandsModule` 处理重启逻辑
- **用户反馈**: 显示 "Rebooting..." 提示（如果有屏幕）

## 🔄 重启流程

1. **用户操作**: 双击 P1.00 按钮
2. **事件触发**: 发送 `INPUT_BROKER_MSG_REBOOT` 消息
3. **系统处理**: `SystemCommandsModule` 接收消息
4. **用户提示**: 显示 "Rebooting..." 横幅（如果有屏幕）
5. **数据保存**: 保存节点数据库到磁盘
6. **重启执行**: 设置重启定时器，延迟重启

## ⚙️ 技术细节

### 消息定义
```cpp
#define INPUT_BROKER_MSG_REBOOT 0x90
```

### 重启延迟
```cpp
#define DEFAULT_REBOOT_SECONDS * 1000  // 默认重启延迟
```

### 处理逻辑
```cpp
case INPUT_BROKER_MSG_REBOOT:
    IF_SCREEN(screen->showSimpleBanner("Rebooting...", 0));
    nodeDB->saveToDisk();
    rebootAtMsec = millis() + DEFAULT_REBOOT_SECONDS * 1000;
```

## 🧪 测试方法

### 1. 编译固件
```bash
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo
```

### 2. 烧录测试
1. 将编译好的固件烧录到设备
2. 测试按钮功能：
   - **短按**: 确认功能
   - **长按 (3秒)**: 关机功能
   - **双击**: 重启功能 ✅ 新增

### 3. 验证重启
- 双击 P1.00 按钮
- 观察设备重启过程
- 确认重启后设备正常运行

## 📝 注意事项

1. **双击时间**: 系统使用默认的双击检测时间间隔
2. **重启延迟**: 重启前会保存数据，确保数据不丢失
3. **用户反馈**: 有屏幕的设备会显示重启提示
4. **安全重启**: 重启前会执行必要的清理和保存操作

## 🔗 相关文件

- `src/main.cpp` - 按钮配置
- `src/modules/SystemCommandsModule.cpp` - 重启处理逻辑
- `src/input/InputBroker.h` - 消息定义
- `variants/nrf52840/diy/nrf52_promicro_diy_tcxo/variant.h` - 硬件定义

## ✅ 修改完成

P1.00 按钮现在支持双击重启功能，为用户提供了便捷的设备重启方式。
