# 按钮功能修改总结

## 修改内容

### P1.00 主按钮 (BUTTON_PIN)
**原功能**:
- 短按: `INPUT_BROKER_USER_PRESS`
- 长按: `INPUT_BROKER_SELECT`
- 超长按: `INPUT_BROKER_SHUTDOWN`

**新功能**:
- 短按: `INPUT_BROKER_SELECT` (确认)
- 长按: `INPUT_BROKER_SHUTDOWN` (关机)
- 长按时间: 3000ms (3秒)
- 移除了所有其他功能 (doublePress, triplePress, longLongPress)

### P1.01 上按钮 (BUTTON_UP_PIN)
**原功能**:
- 短按: `INPUT_BROKER_UP`
- 长按: `INPUT_BROKER_NONE`

**新功能**:
- 短按: `INPUT_BROKER_UP` (保持不变)
- 长按: `INPUT_BROKER_GPS_TOGGLE` (切换GPS模式)
- 长按时间: 3000ms (3秒)

### P1.02 下按钮 (BUTTON_DOWN_PIN)
**原功能**:
- 短按: `INPUT_BROKER_DOWN`
- 长按: `INPUT_BROKER_NONE`

**新功能**:
- 短按: `INPUT_BROKER_DOWN` (保持不变)
- 长按: `INPUT_BROKER_SEND_PING` (发送adhoc ping)
- 长按时间: 3000ms (3秒)

## 功能说明

### 1. P1.00 主按钮
- **短按**: 确认选择，进入菜单
- **长按 (3秒)**: 关机，进入深度睡眠

### 2. P1.01 上按钮
- **短按**: 向上导航
- **长按 (3秒)**: 切换GPS模式 (开启/关闭GPS)

### 3. P1.02 下按钮
- **短按**: 向下导航
- **长按 (3秒)**: 发送adhoc ping (发送位置信息或节点信息)

## 技术细节

### 长按时间统一
所有长按功能都设置为3000ms (3秒)，避免误触发。

### 功能映射
- `INPUT_BROKER_SELECT`: 确认/选择
- `INPUT_BROKER_SHUTDOWN`: 关机
- `INPUT_BROKER_GPS_TOGGLE`: GPS模式切换
- `INPUT_BROKER_SEND_PING`: 发送adhoc ping

### 移除的功能
- P1.00按钮的双击、三击功能
- P1.00按钮的超长按功能
- 所有按钮的默认长按功能

## 测试建议

1. **P1.00按钮测试**:
   - 短按确认功能是否正常
   - 长按3秒是否触发关机

2. **P1.01按钮测试**:
   - 短按向上导航是否正常
   - 长按3秒是否切换GPS模式

3. **P1.02按钮测试**:
   - 短按向下导航是否正常
   - 长按3秒是否发送adhoc ping

## 编译测试
```bash
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo
```

## 注意事项
- 所有长按时间都设置为3秒，避免误触发
- 移除了P1.00按钮的复杂功能，简化为确认和关机
- 保持了P1.01和P1.02的导航功能，同时添加了实用的长按功能
