# nRF52 按钮配置完整文档

## 📋 目录
1. [配置状态检查](#配置状态检查)
2. [按钮功能修改历史](#按钮功能修改历史)
3. [P1.00双击重启功能](#p100双击重启功能)
4. [硬件引脚定义](#硬件引脚定义)
5. [软件配置](#软件配置)
6. [功能映射表](#功能映射表)
7. [测试说明](#测试说明)
8. [编译和部署](#编译和部署)

---

## ✅ 配置状态检查

### 1. 硬件引脚定义 (variant.h)

#### 引脚映射
- **P1.00** → `BUTTON_PIN` (GPIO 32) - 主按钮
- **P1.01** → `BUTTON_UP_PIN` (GPIO 33) - 上按钮
- **P1.02** → `BUTTON_DOWN_PIN` (GPIO 34) - 下按钮
- **P1.06** → `BUTTON_LEFT_PIN` (GPIO 38) - 左按钮
- **P1.07** → `BUTTON_RIGHT_PIN` (GPIO 39) - 右按钮

#### 引脚分配表
```
| P1.00 | BUTTON_PIN   |     | P1.13   | CS           | CS    |
| P1.06 | BUTTON_LEFT  |     | P0.09   | RESET        | RST   |
| P1.01 | BUTTON_UP    |     | 0.15    | LED          |       |
| P1.02 | BUTTON_DOWN  |     | 0.13    | 3V3_EN       |       |
| P1.07 | BUTTON_RIGHT |     |         |              |       |
```

---

## 🔄 按钮功能修改历史

### P1.00 主按钮 (BUTTON_PIN)

#### 原始功能
- 短按: `INPUT_BROKER_USER_PRESS`
- 长按: `INPUT_BROKER_SELECT`
- 超长按: `INPUT_BROKER_SHUTDOWN`
- 双击: `INPUT_BROKER_SEND_PING`
- 三击: `INPUT_BROKER_GPS_TOGGLE`

#### 第一次修改 (简化功能)
- 短按: `INPUT_BROKER_SELECT` (确认)
- 长按: `INPUT_BROKER_SHUTDOWN` (关机)
- 长按时间: 3000ms (3秒)
- 移除了所有其他功能 (doublePress, triplePress, longLongPress)

#### 第二次修改 (添加双击重启) ✅ 最新
- 短按: `INPUT_BROKER_SELECT` (确认)
- 长按: `INPUT_BROKER_SHUTDOWN` (关机)
- 双击: `INPUT_BROKER_MSG_REBOOT` (重启设备) ✅ 新增
- 长按时间: 3000ms (3秒)

### P1.01 上按钮 (BUTTON_UP_PIN)

#### 原始功能
- 短按: `INPUT_BROKER_UP`
- 长按: `INPUT_BROKER_NONE`

#### 修改后功能
- 短按: `INPUT_BROKER_UP` (向上导航)
- 长按: `INPUT_BROKER_GPS_TOGGLE` (切换GPS模式)
- 长按时间: 3000ms (3秒)

### P1.02 下按钮 (BUTTON_DOWN_PIN)

#### 原始功能
- 短按: `INPUT_BROKER_DOWN`
- 长按: `INPUT_BROKER_NONE`

#### 修改后功能
- 短按: `INPUT_BROKER_DOWN` (向下导航)
- 长按: `INPUT_BROKER_SEND_PING` (发送adhoc ping)
- 长按时间: 3000ms (3秒)

### P1.06 左按钮 (BUTTON_LEFT_PIN) - 新增
- 短按: `INPUT_BROKER_LEFT` (向左导航)
- 长按: `INPUT_BROKER_NONE` (无功能)

### P1.07 右按钮 (BUTTON_RIGHT_PIN) - 新增
- 短按: `INPUT_BROKER_RIGHT` (向右导航)
- 长按: `INPUT_BROKER_NONE` (无功能)

---

## 🔧 P1.00双击重启功能

### 功能说明
为P1.00主按钮添加了双击重启设备的功能，提供便捷的设备重启方式。

### 重启流程
1. **用户操作**: 双击 P1.00 按钮
2. **事件触发**: 发送 `INPUT_BROKER_MSG_REBOOT` 消息
3. **系统处理**: `SystemCommandsModule` 接收消息
4. **用户提示**: 显示 "Rebooting..." 横幅（如果有屏幕）
5. **数据保存**: 保存节点数据库到磁盘
6. **重启执行**: 设置重启定时器，延迟重启

### 技术细节
```cpp
// 消息定义
#define INPUT_BROKER_MSG_REBOOT 0x90

// 配置示例
userConfig.doublePress = INPUT_BROKER_MSG_REBOOT;  // 双击：重启设备
```

### 处理逻辑
```cpp
case INPUT_BROKER_MSG_REBOOT:
    IF_SCREEN(screen->showSimpleBanner("Rebooting...", 0));
    nodeDB->saveToDisk();
    rebootAtMsec = millis() + DEFAULT_REBOOT_SECONDS * 1000;
```

---

## 🔌 硬件引脚定义

### 引脚分配表
```
| P1.00 | BUTTON_PIN   |     | P1.13   | CS           | CS    |
| P1.06 | BUTTON_LEFT  |     | P0.09   | RESET        | RST   |
| P1.01 | BUTTON_UP    |     | 0.15    | LED          |       |
| P1.02 | BUTTON_DOWN  |     | 0.13    | 3V3_EN       |       |
| P1.07 | BUTTON_RIGHT |     |         |              |       |
```

### 硬件特性
- **激活方式**: 低电平激活 (`activeLow = true`)
- **上拉电阻**: 启用 (`activePullup = true`)
- **中断支持**: 支持从睡眠状态唤醒
- **防抖处理**: 内置防抖机制

---

## 💻 软件配置

### 按钮声明
```cpp
#if defined(BUTTON_UP_PIN)
ButtonThread *UpButtonThread = nullptr;
#endif

#if defined(BUTTON_DOWN_PIN)
ButtonThread *DownButtonThread = nullptr;
#endif

#if defined(BUTTON_LEFT_PIN)
ButtonThread *LeftButtonThread = nullptr;
#endif

#if defined(BUTTON_RIGHT_PIN)
ButtonThread *RightButtonThread = nullptr;
#endif
```

### 按钮初始化配置

#### P1.00 主按钮配置
```cpp
// 有屏幕配置
userConfig.singlePress = INPUT_BROKER_SELECT;      // 短按：确认
userConfig.longPress = INPUT_BROKER_SHUTDOWN;     // 长按：关机
userConfig.longPressTime = 3000;                 // 长按时间：3秒
userConfig.longLongPress = INPUT_BROKER_NONE;    // 超长按：无
userConfig.doublePress = INPUT_BROKER_MSG_REBOOT; // 双击：重启设备

// 无屏幕配置
userConfigNoScreen.singlePress = INPUT_BROKER_SELECT;      // 短按：确认
userConfigNoScreen.longPress = INPUT_BROKER_SHUTDOWN;     // 长按：关机
userConfigNoScreen.longPressTime = 3000;                  // 长按时间：3秒
userConfigNoScreen.longLongPress = INPUT_BROKER_NONE;     // 超长按：无
userConfigNoScreen.doublePress = INPUT_BROKER_MSG_REBOOT; // 双击：重启设备
userConfigNoScreen.triplePress = INPUT_BROKER_NONE;      // 三击：无
```

#### 方向按钮配置
```cpp
// P1.01 上按钮
upConfig.singlePress = INPUT_BROKER_UP;
upConfig.longPress = INPUT_BROKER_GPS_TOGGLE;
upConfig.longPressTime = 3000;

// P1.02 下按钮
downConfig.singlePress = INPUT_BROKER_DOWN;
downConfig.longPress = INPUT_BROKER_SEND_PING;
downConfig.longPressTime = 3000;

// P1.06 左按钮
leftConfig.singlePress = INPUT_BROKER_LEFT;
leftConfig.longPress = INPUT_BROKER_NONE;

// P1.07 右按钮
rightConfig.singlePress = INPUT_BROKER_RIGHT;
rightConfig.longPress = INPUT_BROKER_NONE;
```

---

## 📊 功能映射表

| 按钮 | 短按功能 | 长按功能 | 双击功能 | 长按时间 |
|------|----------|----------|----------|----------|
| **P1.00** | 确认选择 | 关机 | 重启设备 ✅ | 3秒 |
| **P1.01** | 向上导航 | 切换GPS模式 | 无 | 3秒 |
| **P1.02** | 向下导航 | 发送adhoc ping | 无 | 3秒 |
| **P1.06** | 向左导航 | 无功能 | 无 | - |
| **P1.07** | 向右导航 | 无功能 | 无 | - |

### 事件处理
- `INPUT_BROKER_SELECT`: 确认/选择
- `INPUT_BROKER_SHUTDOWN`: 关机
- `INPUT_BROKER_MSG_REBOOT`: 重启设备 ✅ 新增
- `INPUT_BROKER_UP/DOWN/LEFT/RIGHT`: 方向导航
- `INPUT_BROKER_GPS_TOGGLE`: GPS模式切换
- `INPUT_BROKER_SEND_PING`: 发送adhoc ping

### 系统响应
- **GPS切换**: 调用`gps->toggleGpsMode()`
- **发送ping**: 调用`service->trySendPosition()`
- **关机**: 设置`shutdownAtMsec = millis()`
- **重启**: 显示提示并执行重启流程

---

## 🧪 测试说明

### 新增按钮测试

#### 1. 编译测试
```bash
cd /Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo
```

#### 2. 功能测试

##### P1.00 主按钮测试
- **短按**: 确认功能是否正常
- **长按 (3秒)**: 关机功能是否正常
- **双击**: 重启功能是否正常 ✅ 新增

##### P1.01 上按钮测试
- **短按**: 向上导航是否正常
- **长按 (3秒)**: GPS模式切换是否正常

##### P1.02 下按钮测试
- **短按**: 向下导航是否正常
- **长按 (3秒)**: 发送adhoc ping是否正常

##### P1.06 左按钮测试
- **短按**: 向左导航是否正常

##### P1.07 右按钮测试
- **短按**: 向右导航是否正常

#### 3. 硬件连接验证
确保以下引脚正确连接到按钮：
- P1.00 (GPIO 32) → 主按钮
- P1.01 (GPIO 33) → 上按钮
- P1.02 (GPIO 34) → 下按钮
- P1.06 (GPIO 38) → 左按钮
- P1.07 (GPIO 39) → 右按钮

---

## 🔨 编译和部署

### 编译命令
```bash
# 编译nRF52固件
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo

# 检查编译结果
ls -la release/
```

### 部署文件
编译完成后会生成以下文件：
- `firmware-nrf52_promicro_diy_tcxo-*.uf2` - UF2格式固件
- `firmware-nrf52_promicro_diy_tcxo-*.hex` - HEX格式固件
- `firmware-nrf52_promicro_diy_tcxo-*.zip` - OTA更新包
- `firmware-nrf52_promicro_diy_tcxo-*.elf` - ELF调试文件

### 烧录方法
1. 将设备置于DFU模式
2. 拖拽`.uf2`文件到设备或使用烧录工具烧录`.hex`文件

---

## ⚠️ 注意事项

### 1. 长按时间统一
所有长按功能都设置为3秒，避免误触发。

### 2. 功能简化
- 移除了P1.00按钮的复杂双击、三击功能
- 简化为确认、关机、重启三个核心功能

### 3. 功能重分配
- 将原主按钮的复杂功能重新分配到方向按钮
- 保持了导航功能的同时添加了实用功能

### 4. 硬件连接
- 确保按钮正确连接到对应的GPIO引脚
- 所有按钮都配置为低电平激活
- 启用了上拉电阻和中断支持

### 5. 双击重启功能
- 双击间隔在系统默认时间内
- 重启前会保存数据，确保数据不丢失
- 有屏幕的设备会显示重启提示

---

## 📋 配置验证

### ✅ 已完成的配置
- [x] 硬件引脚定义
- [x] 引脚分配表更新
- [x] 按钮声明
- [x] 按钮初始化
- [x] 功能映射
- [x] 事件处理
- [x] P1.00双击重启功能 ✅ 新增

### 🔧 需要测试的功能
- [ ] 按钮响应测试
- [ ] 长按功能测试
- [ ] GPS切换测试
- [ ] 发送ping测试
- [ ] 关机功能测试
- [ ] 双击重启测试 ✅ 新增

---

## 📝 总结

nRF52按钮配置已完成，支持5个按钮的完整功能：

### 核心功能
- **主按钮 (P1.00)**: 确认 + 关机 + 重启 ✅ 新增双击重启
- **方向按钮**: 导航 + 特殊功能
- **统一长按时间**: 3秒
- **完整事件处理**: 通过InputBroker统一管理

### 新增功能
- **P1.00双击重启**: 提供便捷的设备重启方式
- **P1.01长按GPS切换**: 快速切换GPS模式
- **P1.02长按发送ping**: 快速发送位置信息

### 技术特性
- **硬件支持**: 5个独立按钮，支持中断唤醒
- **软件支持**: 完整的事件处理和状态管理
- **用户体验**: 简化的操作逻辑，避免误触发

配置已就绪，可以进行编译和测试！