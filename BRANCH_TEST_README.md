# nRF52 ProMicro DIY 测试分支

## 📋 分支说明

这是专门为 **nRF52 ProMicro DIY** 设备创建的测试分支，用于开发和测试针对该硬件的特定功能。

## 🎯 测试分支特性

### ✅ 已实现功能
- **自定义图标支持**: 支持PNG到XBM格式转换
- **按钮功能优化**: P1.06左键长按进入刷机模式
- **固件大小优化**: 针对nRF52平台的特殊配置
- **编译工具链**: 完整的PlatformIO配置

### 🔧 硬件配置
- **主控**: nRF52840
- **按钮配置**: 
  - P1.00: 主按钮 (确认/关机/双击重启)
  - P1.01: 上按钮 (向上导航/长按GPS切换)
  - P1.02: 下按钮 (向下导航/长按发送ping)
  - P1.06: 左按钮 (向左导航/长按进入刷机模式)
  - P1.07: 右按钮 (向右导航)

### 📦 固件特性
- **版本**: 2.7.9.dc544184
- **环境**: nrf52_promicro_diy_tcxo
- **内存使用**: RAM 31.5%, Flash 93.1%
- **上传协议**: nrfutil DFU

## 🚀 使用方法

### 1. 编译固件
```bash
cd /Users/vvlang/Library/CloudStorage/SynologyDrive-soft/LoRa/meshcn-firmware
pio run -e nrf52_promicro_diy_tcxo
```

### 2. 刷入设备
```bash
pio run -e nrf52_promicro_diy_tcxo --target upload --upload-port /dev/cu.usbmodem*
```

### 3. 自定义图标
```bash
python3 create_custom_logo.py
```

## 🧪 测试项目

### 按钮功能测试
- [ ] P1.00 主按钮: 短按确认、长按关机、双击重启
- [ ] P1.01 上按钮: 短按向上、长按GPS切换
- [ ] P1.02 下按钮: 短按向下、长按发送ping
- [ ] P1.06 左按钮: 短按向左、长按进入刷机模式
- [ ] P1.07 右按钮: 短按向右

### 通信功能测试
- [ ] LoRa通信测试
- [ ] 蓝牙连接测试
- [ ] GPS定位测试
- [ ] 消息收发测试

### 显示功能测试
- [ ] OLED显示测试
- [ ] 自定义图标显示
- [ ] 界面导航测试

## 📊 性能指标

| 指标 | 数值 | 状态 |
|------|------|------|
| RAM使用率 | 31.5% (78,380/248,832 bytes) | ✅ 正常 |
| Flash使用率 | 93.1% (758,800/815,104 bytes) | ⚠️ 接近上限 |
| 编译时间 | ~16秒 | ✅ 正常 |
| 上传时间 | ~60秒 | ✅ 正常 |

## 🔄 分支管理

### 合并到主分支
```bash
git checkout main
git merge nrf52-promicro-diy-test
git push origin main
```

### 更新测试分支
```bash
git checkout nrf52-promicro-diy-test
git merge main
git push origin nrf52-promicro-diy-test
```

## 📝 开发日志

### 2024-01-24
- ✅ 创建测试分支
- ✅ 添加自定义图标支持
- ✅ 优化按钮配置
- ✅ 更新文档

## 🐛 已知问题

1. **Flash使用率较高**: 93.1%接近上限，可能需要进一步优化
2. **编译依赖**: 需要完整的PlatformIO环境

## 📞 支持

如有问题，请提交Issue或联系开发团队。

---
**分支创建时间**: 2024-01-24  
**最后更新**: 2024-01-24  
**维护者**: vvlang
