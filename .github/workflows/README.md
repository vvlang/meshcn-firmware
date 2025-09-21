# GitHub Actions 工作流说明

本目录包含了用于自动构建和发布nRF52固件的GitHub Actions工作流。

## 工作流文件

### 1. build-nrf52.yml
自动构建工作流，在以下情况下触发：
- 推送到 `main` 或 `develop` 分支时（仅当相关文件发生变化）
- 创建Pull Request时
- 发布Release时
- 手动触发（workflow_dispatch）

**触发条件**：
- 修改了 `src/` 目录下的源代码
- 修改了 `variants/nrf52840/` 目录下的变体配置
- 修改了 `arch/nrf52/` 目录下的架构配置
- 修改了构建脚本或平台配置

### 2. manual-release.yml
手动发布工作流，专门用于手动触发构建和发布。

**功能**：
- 可选择构建目标设备
- 可指定版本号
- 可选择是否创建GitHub Release
- 支持多种nRF52设备变体

## 支持的设备

工作流支持以下nRF52设备：

- `nrf52_promicro_diy_tcxo` - ProMicro DIY板（带TCXO）
- `nrf52_promicro_diy-inkhud` - ProMicro DIY板（带InkHUD显示）
- `rak4631` - RAK4631模块
- `nano-g2-ultra` - Nano G2 Ultra
- `wio-tracker-wm1110` - Wio Tracker WM1110
- `canaryone` - CanaryOne
- `heltec-mesh-node-t114` - Heltec Mesh Node T114
- `tracker-t1000-e` - Tracker T1000-E
- `t-echo` - T-Echo

## 使用方法

### 自动构建
1. 推送代码到 `main` 或 `develop` 分支
2. 工作流会自动检测相关文件变化并触发构建
3. 构建完成后，固件文件会作为构建产物保存

### 手动发布
1. 进入GitHub仓库的Actions页面
2. 选择 "Manual nRF52 Release" 工作流
3. 点击 "Run workflow"
4. 选择目标设备和版本号
5. 选择是否创建GitHub Release
6. 点击 "Run workflow" 开始构建

### 创建Release
1. 在GitHub仓库中创建新的Release
2. 工作流会自动构建固件并附加到Release中
3. 或者使用手动发布工作流创建Release

## 构建产物

每次构建会生成以下文件：

- `firmware-{target}-{version}.uf2` - UF2格式固件，可直接拖拽到设备
- `firmware-{target}-{version}.hex` - HEX格式固件，用于传统烧录工具
- `firmware-{target}-{version}-ota.zip` - OTA更新包
- `firmware-{target}-{version}.elf` - ELF调试文件

## 环境要求

- Ubuntu 20.04 LTS
- Python 3.9
- PlatformIO Core
- Git
- 构建工具链

## 故障排除

### 构建失败
1. 检查目标设备配置是否正确
2. 确认所有依赖库都已正确安装
3. 查看构建日志中的具体错误信息

### 权限问题
1. 确保GitHub仓库有足够的权限
2. 检查GITHUB_TOKEN是否正确设置

### 文件未找到
1. 确认构建脚本路径正确
2. 检查相关文件是否存在
3. 验证文件权限设置

## 自定义配置

如需添加新的设备支持：

1. 在 `variants/nrf52840/` 目录下创建新的设备配置
2. 更新工作流文件中的设备选项列表
3. 测试构建过程

## 联系支持

如有问题，请：
1. 查看构建日志
2. 检查GitHub Actions状态
3. 提交Issue到仓库
