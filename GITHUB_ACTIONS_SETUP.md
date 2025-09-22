# GitHub Actions 自动构建设置

本文档说明如何设置GitHub Actions来自动编译nRF52固件并发布到Releases。

## 已创建的文件

### 1. 工作流文件
- `.github/workflows/build-nrf52.yml` - 主要构建工作流
- `.github/workflows/manual-release.yml` - 手动发布工作流  
- `.github/workflows/test-build.yml` - 测试构建工作流

### 2. 文档文件
- `.github/workflows/README.md` - 工作流使用说明
- `GITHUB_ACTIONS_SETUP.md` - 本设置文档

## 工作流功能

### 自动触发条件
1. **代码推送**: 当推送到 `main` 或 `develop` 分支时，如果修改了相关文件
2. **Pull Request**: 创建PR时自动构建测试
3. **Release发布**: 创建GitHub Release时自动构建固件
4. **手动触发**: 可以手动选择目标设备进行构建

### 支持的设备
- `nrf52_promicro_diy_tcxo` - ProMicro DIY板（带TCXO）
- `nrf52_promicro_diy-inkhud` - ProMicro DIY板（带InkHUD显示）
- `rak4631` - RAK4631模块
- `nano-g2-ultra` - Nano G2 Ultra
- `wio-tracker-wm1110` - Wio Tracker WM1110
- `canaryone` - CanaryOne
- `heltec-mesh-node-t114` - Heltec Mesh Node T114
- `tracker-t1000-e` - Tracker T1000-E
- `t-echo` - T-Echo

### 构建产物
每次构建会生成以下文件：
- `.uf2` - UF2格式固件，可直接拖拽到设备
- `.hex` - HEX格式固件，用于传统烧录工具
- `.zip` - OTA更新包
- `.elf` - ELF调试文件

## 使用方法

### 1. 自动构建
```bash
# 推送代码到main分支
git add .
git commit -m "Update nRF52 firmware"
git push origin main
```

### 2. 手动构建
1. 进入GitHub仓库的Actions页面
2. 选择 "Manual nRF52 Release" 工作流
3. 点击 "Run workflow"
4. 选择目标设备和版本号
5. 点击 "Run workflow" 开始构建

### 3. 创建Release
1. 在GitHub仓库中创建新的Release
2. 工作流会自动构建固件并附加到Release中

## 环境配置

### 系统要求
- Ubuntu 20.04 LTS
- Python 3.9
- PlatformIO Core
- Git
- 构建工具链

### 权限设置
确保GitHub仓库有以下权限：
- Actions: 启用
- Releases: 启用
- Contents: 读取和写入

## 故障排除

### 常见问题

1. **构建失败**
   - 检查目标设备配置是否正确
   - 确认所有依赖库都已正确安装
   - 查看构建日志中的具体错误信息

2. **权限问题**
   - 确保GitHub仓库有足够的权限
   - 检查GITHUB_TOKEN是否正确设置

3. **文件未找到**
   - 确认构建脚本路径正确
   - 检查相关文件是否存在
   - 验证文件权限设置

### 调试步骤

1. 使用测试工作流验证环境
2. 检查构建日志
3. 验证文件路径和权限
4. 测试本地构建脚本

## 自定义配置

### 添加新设备
1. 在 `variants/nrf52840/` 目录下创建新的设备配置
2. 更新工作流文件中的设备选项列表
3. 测试构建过程

### 修改构建参数
在 `.github/workflows/build-nrf52.yml` 中修改：
```yaml
- name: Build nRF52 firmware
  run: |
    # 添加自定义构建参数
    export CUSTOM_BUILD_FLAGS="your_flags_here"
    ./bin/build-nrf52.sh $TARGET
```

## 监控和维护

### 构建状态
- 在GitHub Actions页面查看构建状态
- 设置邮件通知（在仓库设置中配置）

### 定期维护
- 更新PlatformIO版本
- 更新依赖库
- 检查构建脚本兼容性

## 联系支持

如有问题，请：
1. 查看构建日志
2. 检查GitHub Actions状态
3. 提交Issue到仓库
4. 参考 `.github/workflows/README.md` 获取详细说明

## 总结

通过以上设置，您现在可以：
- 自动构建nRF52固件
- 手动选择目标设备进行构建
- 自动发布固件到GitHub Releases
- 监控构建状态和结果

这大大简化了固件发布流程，提高了开发效率。
