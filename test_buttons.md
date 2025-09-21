# 按钮功能测试说明

## 新增按钮配置

### 硬件引脚映射
- **P1.01** → `BUTTON_UP_PIN` (GPIO 33) - 上方向按钮
- **P1.02** → `BUTTON_DOWN_PIN` (GPIO 34) - 下方向按钮  
- **P1.06** → `BUTTON_LEFT_PIN` (GPIO 38) - 左方向按钮
- **P1.07** → `BUTTON_RIGHT_PIN` (GPIO 39) - 右方向按钮

### 按钮功能
- **短按**: 触发对应的方向事件
  - 上按钮 → `INPUT_BROKER_UP`
  - 下按钮 → `INPUT_BROKER_DOWN`
  - 左按钮 → `INPUT_BROKER_LEFT`
  - 右按钮 → `INPUT_BROKER_RIGHT`

### 测试方法

#### 1. 编译测试
```bash
cd /Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo
```

#### 2. 功能测试
- 在界面中测试方向按钮是否正常工作
- 检查按钮是否能够正确触发方向事件
- 验证按钮的防抖和响应时间

#### 3. 硬件连接
确保以下引脚正确连接到按钮：
- P1.01 (GPIO 33) → 上按钮
- P1.02 (GPIO 34) → 下按钮
- P1.06 (GPIO 38) → 左按钮
- P1.07 (GPIO 39) → 右按钮

### 代码更改总结

#### variant.h 更改
- 添加了4个新的按钮引脚定义
- 更新了引脚分配表

#### main.cpp 更改
- 添加了4个新的ButtonThread声明
- 添加了4个按钮的初始化代码
- 配置了对应的输入事件

### 注意事项
- 所有按钮都配置为低电平激活
- 启用了上拉电阻
- 支持中断唤醒
- 短按触发方向事件，长按无特殊功能
