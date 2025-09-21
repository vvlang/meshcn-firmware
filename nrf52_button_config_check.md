# nRF52 按钮配置检查报告

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

### 2. 软件配置 (main.cpp)

#### 按钮声明
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

#### 按钮功能配置

##### P1.00 主按钮 (BUTTON_PIN)
- **短按**: `INPUT_BROKER_SELECT` (确认)
- **长按**: `INPUT_BROKER_SHUTDOWN` (关机)
- **长按时间**: 3000ms (3秒)
- **其他功能**: 已移除 (双击、三击、超长按)

##### P1.01 上按钮 (BUTTON_UP_PIN)
- **短按**: `INPUT_BROKER_UP` (向上导航)
- **长按**: `INPUT_BROKER_GPS_TOGGLE` (切换GPS模式)
- **长按时间**: 3000ms (3秒)

##### P1.02 下按钮 (BUTTON_DOWN_PIN)
- **短按**: `INPUT_BROKER_DOWN` (向下导航)
- **长按**: `INPUT_BROKER_SEND_PING` (发送adhoc ping)
- **长按时间**: 3000ms (3秒)

##### P1.06 左按钮 (BUTTON_LEFT_PIN)
- **短按**: `INPUT_BROKER_LEFT` (向左导航)
- **长按**: `INPUT_BROKER_NONE` (无功能)

##### P1.07 右按钮 (BUTTON_RIGHT_PIN)
- **短按**: `INPUT_BROKER_RIGHT` (向右导航)
- **长按**: `INPUT_BROKER_NONE` (无功能)

### 3. 技术特性

#### 硬件特性
- **激活方式**: 低电平激活 (`activeLow = true`)
- **上拉电阻**: 启用 (`activePullup = true`)
- **中断支持**: 支持从睡眠状态唤醒
- **防抖处理**: 内置防抖机制

#### 软件特性
- **事件处理**: 通过InputBroker统一处理
- **音频反馈**: 支持按钮音效
- **状态管理**: 完整的状态机管理
- **组合按键**: 支持短按+长按组合

### 4. 功能映射表

| 按钮 | 短按功能 | 长按功能 | 长按时间 |
|------|----------|----------|----------|
| **P1.00** | 确认选择 | 关机 | 3秒 |
| **P1.01** | 向上导航 | 切换GPS模式 | 3秒 |
| **P1.02** | 向下导航 | 发送adhoc ping | 3秒 |
| **P1.06** | 向左导航 | 无功能 | - |
| **P1.07** | 向右导航 | 无功能 | - |

### 5. 事件处理

#### 输入事件
- `INPUT_BROKER_SELECT`: 确认/选择
- `INPUT_BROKER_SHUTDOWN`: 关机
- `INPUT_BROKER_UP/DOWN/LEFT/RIGHT`: 方向导航
- `INPUT_BROKER_GPS_TOGGLE`: GPS模式切换
- `INPUT_BROKER_SEND_PING`: 发送adhoc ping

#### 系统响应
- **GPS切换**: 调用`gps->toggleGpsMode()`
- **发送ping**: 调用`service->trySendPosition()`
- **关机**: 设置`shutdownAtMsec = millis()`

### 6. 配置验证

#### ✅ 已完成的配置
- [x] 硬件引脚定义
- [x] 引脚分配表更新
- [x] 按钮声明
- [x] 按钮初始化
- [x] 功能映射
- [x] 事件处理

#### 🔧 需要测试的功能
- [ ] 按钮响应测试
- [ ] 长按功能测试
- [ ] GPS切换测试
- [ ] 发送ping测试
- [ ] 关机功能测试

### 7. 编译测试

```bash
# 编译nRF52固件
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo

# 检查编译结果
ls -la release/
```

### 8. 注意事项

1. **长按时间统一**: 所有长按功能都设置为3秒，避免误触发
2. **功能简化**: 移除了复杂的双击、三击功能，简化用户体验
3. **功能重分配**: 将原主按钮的复杂功能重新分配到方向按钮
4. **硬件连接**: 确保按钮正确连接到对应的GPIO引脚

## 📋 总结

nRF52按钮配置已完成，支持5个按钮的完整功能：
- **主按钮**: 确认 + 关机
- **方向按钮**: 导航 + 特殊功能
- **统一长按时间**: 3秒
- **完整事件处理**: 通过InputBroker统一管理

配置已就绪，可以进行编译和测试！
