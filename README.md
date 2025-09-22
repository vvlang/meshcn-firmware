<div align="center" markdown="1">

<h1>MESHCN 固件</h1>

</div>

</div>

<div align="center">
	<a href="https://meshcn.net">官方网站</a>
	-
	<a href="https://meshcn.net/docs/">文档</a>
</div>

## 项目概述

本仓库包含 MESHCN 的官方设备固件，这是一个开源 LoRa 网格网络项目，专为长距离、低功耗通信而设计，无需依赖互联网或蜂窝基础设施。固件支持多种硬件平台，包括 ESP32、nRF52、RP2040/RP2350 和基于 Linux 的设备。

MESHCN 通过去中心化网格网络实现文本消息、位置共享和遥测功能，非常适合户外探险、应急准备和远程操作。

## 主要特性

### 🌐 网格网络通信
- **去中心化网络**: 无需基站或互联网连接
- **长距离通信**: 基于 LoRa 技术，覆盖范围可达数公里
- **自愈网络**: 自动路由和网络恢复能力
- **低功耗设计**: 延长设备电池寿命

### 📱 设备支持
- **ESP32 系列**: 功能丰富的物联网开发板
- **nRF52 系列**: 低功耗蓝牙和 LoRa 设备
- **RP2040/RP2350**: 高性能微控制器
- **Linux 设备**: 支持树莓派等单板计算机

### 💬 通信功能
- **文本消息**: 点对点和广播消息
- **位置共享**: GPS 位置追踪和分享
- **遥测数据**: 环境传感器数据收集
- **紧急信标**: 紧急情况下的位置广播

### 🔧 开发特性
- **开源固件**: 完全开源，可自定义和扩展
- **模块化设计**: 支持插件和自定义模块
- **多平台支持**: 统一的代码库支持多种硬件
- **自动构建**: GitHub Actions 自动编译和发布

## 硬件平台

### nRF52 系列
- **nRF52 ProMicro DIY**: 自定义开发板，支持五向按钮
- **RAK4631**: 工业级 LoRa 模块
- **nano-g2-ultra**: 紧凑型设备
- **wio-tracker-wm1110**: 追踪器设备

### ESP32 系列
- **T-Watch S3**: 智能手表
- **T-Deck**: 全键盘设备
- **T-Echo**: 对讲机设备
- **Heltec 系列**: 开发板和模块

## 快速开始

### 1. 克隆仓库
```bash
git clone https://github.com/vvlang/meshcn-firmware.git
cd meshcn-firmware
```

### 2. 安装依赖
```bash
# 安装 PlatformIO
pip install platformio

# 或者使用包管理器
# Ubuntu/Debian
sudo apt-get install python3-pip
pip3 install platformio

# macOS
brew install platformio
```

### 3. 编译固件
```bash
# 编译 nRF52 固件
./bin/build-nrf52.sh nrf52_promicro_diy_tcxo

# 编译 ESP32 固件
./bin/build-esp32.sh t-watch-s3

# 编译 RP2040 固件
./bin/build-rp2xx0.sh t-deck
```

### 4. 烧录固件
```bash
# 查看编译结果
ls -la release/

# 使用 UF2 文件（推荐）
# 将设备置于 DFU 模式，拖拽 .uf2 文件到设备

# 使用 HEX 文件
# 使用 J-Link 或其他烧录工具烧录 .hex 文件
```

## 按钮配置

### nRF52 ProMicro DIY 按钮功能
| 按钮 | 短按功能 | 长按功能 | 双击功能 |
|------|----------|----------|----------|
| **P1.00** | 确认选择 | 关机 (3秒) | 重启设备 |
| **P1.01** | 向上导航 | 切换GPS模式 (3秒) | 无 |
| **P1.02** | 向下导航 | 发送adhoc ping (3秒) | 无 |
| **P1.06** | 向左导航 | 无功能 | 无 |
| **P1.07** | 向右导航 | 无功能 | 无 |

### 按钮操作说明
- **短按**: 快速按下并释放
- **长按**: 按住3秒后释放
- **双击**: 快速连续按下两次

## 贡献指南

### 开发环境设置
1. 安装 PlatformIO IDE 或 VS Code + PlatformIO 扩展
2. 克隆仓库并安装依赖
3. 选择目标硬件平台进行开发

### 代码规范
- 遵循现有的代码风格
- 添加适当的注释和文档
- 测试新功能确保兼容性

### 提交规范
- 使用清晰的提交信息
- 一个提交只包含一个功能或修复
- 添加必要的测试和文档

## 许可证

本项目采用开源许可证，详见 [LICENSE](LICENSE) 文件。

## 支持与社区

- **官方网站**: [https://meshcn.net](https://meshcn.net)
- **文档**: [https://meshcn.net/docs/](https://meshcn.net/docs/)
- **问题反馈**: [GitHub Issues](https://github.com/vvlang/meshcn-firmware/issues)
- **讨论区**: [GitHub Discussions](https://github.com/vvlang/meshcn-firmware/discussions)

## 更新日志

### 最新版本
- ✅ 添加 nRF52 五向按钮支持
- ✅ 实现 P1.00 双击重启功能
- ✅ 配置 GitHub Actions 自动构建
- ✅ 优化按钮功能和用户体验
- ✅ 完善文档和说明

---

<div align="center">
	<strong>MESHCN - 连接世界，无需网络</strong>
</div>