#include "MainScreen.h"
#include <OLEDDisplay.h>
#include <OLEDDisplayUi.h>
#include "../../input/InputBroker.h"
#include "../configuration.h"
#include "../../mesh/NodeDB.h"
#include "../../PowerFSM.h"

#if HAS_SCREEN

namespace graphics {
namespace ui {

MainScreen::MainScreen() 
    : currentState(ScreenState::HOME)
    , lastUpdateTime(0)
    , animationEnabled(true)
    , animationFrame(0)
{
    // 初始化默认快速操作
    quickActions = {
        {"发送消息", "📨", []() { /* 发送消息逻辑 */ }},
        {"查看节点", "📡", []() { /* 节点列表逻辑 */ }},
        {"设置", "⚙️", []() { /* 设置菜单逻辑 */ }},
        {"系统信息", "ℹ️", []() { /* 系统信息逻辑 */ }}
    };
}

void MainScreen::showHomeScreen(OLEDDisplay* display) {
    if (!display) return;
    
    currentState = ScreenState::HOME;
    display->clear();
    
    int16_t y = 0;
    
    // 渲染状态栏
    renderStatusBar(display, 0, y);
    y += 16;
    
    // 渲染主内容
    renderMainContent(display, 0, y);
    y += 48;
    
    // 渲染快速操作
    renderQuickActions(display, 0, y);
    y += 32;
    
    // 渲染导航
    renderNavigation(display, 0, y);
    
    display->display();
}

void MainScreen::showQuickSettings(OLEDDisplay* display) {
    if (!display) return;
    
    currentState = ScreenState::QUICK_SETTINGS;
    display->clear();
    
    int16_t y = 0;
    
    // 标题
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_16);
    display->drawString(64, y, "快速设置");
    y += 20;
    
    // 设置选项
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    
    // 静音模式
    display->drawString(10, y, "🔇 静音模式");
    display->drawString(100, y, currentStatus.nodeCount > 0 ? "开启" : "关闭");
    y += 15;
    
    // WiFi状态
    display->drawString(10, y, "📶 WiFi");
    display->drawString(100, y, currentStatus.wifiConnected ? "已连接" : "未连接");
    y += 15;
    
    // 蓝牙状态
    display->drawString(10, y, "🔵 蓝牙");
    display->drawString(100, y, currentStatus.bluetoothEnabled ? "已开启" : "已关闭");
    y += 15;
    
    // 屏幕亮度
    display->drawString(10, y, "💡 亮度");
    display->drawString(100, y, "80%");
    y += 15;
    
    // 屏幕超时
    display->drawString(10, y, "⏰ 超时");
    display->drawString(100, y, "30秒");
    
    display->display();
}

void MainScreen::showStatusOverlay(OLEDDisplay* display) {
    if (!display) return;
    
    currentState = ScreenState::STATUS_OVERLAY;
    display->clear();
    
    // 半透明背景
    display->setColor(BLACK);
    display->fillRect(0, 0, 128, 64);
    display->setColor(WHITE);
    
    // 状态信息
    int16_t y = 10;
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    
    // 信号强度
    char signalStr[32];
    snprintf(signalStr, sizeof(signalStr), "📡 信号: %d%%", currentStatus.signalStrength);
    display->drawString(64, y, signalStr);
    y += 12;
    
    // 电池电量
    char batteryStr[32];
    snprintf(batteryStr, sizeof(batteryStr), "🔋 电量: %d%%", currentStatus.batteryLevel);
    display->drawString(64, y, batteryStr);
    y += 12;
    
    // GPS状态
    display->drawString(64, y, currentStatus.gpsConnected ? "📍 GPS: 已连接" : "📍 GPS: 未连接");
    y += 12;
    
    // 节点数量
    char nodeStr[32];
    snprintf(nodeStr, sizeof(nodeStr), "📡 节点: %d个", currentStatus.nodeCount);
    display->drawString(64, y, nodeStr);
    
    display->display();
}

void MainScreen::updateStatus(const StatusInfo& status) {
    currentStatus = status;
    lastUpdateTime = millis();
}

void MainScreen::setScreenState(ScreenState state) {
    currentState = state;
}

void MainScreen::addQuickAction(const QuickAction& action) {
    quickActions.push_back(action);
}

void MainScreen::clearQuickActions() {
    quickActions.clear();
}

bool MainScreen::handleInput(const InputEvent* event) {
    if (!event) return false;
    
    switch (event->inputEvent) {
        case INPUT_BROKER_UP:
            // 向上导航
            return true;
        case INPUT_BROKER_DOWN:
            // 向下导航
            return true;
        case INPUT_BROKER_LEFT:
            // 向左导航
            return true;
        case INPUT_BROKER_RIGHT:
            // 向右导航
            return true;
        case INPUT_BROKER_SELECT:
            // 选择操作
            return true;
        default:
            return false;
    }
}

void MainScreen::forceRefresh() {
    lastUpdateTime = millis();
    animationFrame = 0;
}

void MainScreen::setBrightness(uint8_t level) {
    // 设置屏幕亮度
    if (level > 100) level = 100;
    // 这里需要根据具体的显示驱动来实现
}

void MainScreen::renderStatusBar(OLEDDisplay* display, int16_t x, int16_t y) {
    if (!display) return;
    
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    
    // 信号强度
    drawSignalBars(display, x, y, currentStatus.signalStrength);
    x += 20;
    
    // 电池电量
    drawBatteryIcon(display, x, y, currentStatus.batteryLevel);
    x += 20;
    
    // GPS状态
    drawStatusIcon(display, x, y, "📍", currentStatus.gpsConnected);
    x += 15;
    
    // 节点数量
    if (currentStatus.nodeCount > 0) {
        char nodeStr[8];
        snprintf(nodeStr, sizeof(nodeStr), "%d", currentStatus.nodeCount);
        display->drawString(x, y, nodeStr);
        x += 15;
    }
    
    // 时间
    display->setTextAlignment(TEXT_ALIGN_RIGHT);
    display->drawString(128, y, "10:30");
}

void MainScreen::renderQuickActions(OLEDDisplay* display, int16_t x, int16_t y) {
    if (!display || quickActions.empty()) return;
    
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    
    int16_t buttonWidth = 60;
    int16_t buttonHeight = 30;
    int16_t spacing = 4;
    
    for (size_t i = 0; i < quickActions.size() && i < 4; ++i) {
        int16_t buttonX = x + (i % 2) * (buttonWidth + spacing);
        int16_t buttonY = y + (i / 2) * (buttonHeight + spacing);
        
        // 绘制按钮背景
        display->setColor(WHITE);
        display->drawRect(buttonX, buttonY, buttonWidth, buttonHeight);
        
        // 绘制图标和文字
        display->drawString(buttonX + buttonWidth/2, buttonY + 5, quickActions[i].icon);
        display->drawString(buttonX + buttonWidth/2, buttonY + 18, quickActions[i].label);
    }
}

void MainScreen::renderMainContent(OLEDDisplay* display, int16_t x, int16_t y) {
    if (!display) return;
    
    display->setFont(ArialMT_Plain_16);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64, y, "MESHCN");
    
    y += 20;
    display->setFont(ArialMT_Plain_10);
    display->drawString(64, y, "连接世界，无需网络");
}

void MainScreen::renderNavigation(OLEDDisplay* display, int16_t x, int16_t y) {
    if (!display) return;
    
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64, y, "← 返回  ↑↓ 导航  ✓ 确认");
}

void MainScreen::drawSignalBars(OLEDDisplay* display, int16_t x, int16_t y, uint8_t strength) {
    if (!display) return;
    
    int16_t barWidth = 2;
    int16_t barHeight = 8;
    int16_t spacing = 1;
    
    for (int i = 0; i < 5; ++i) {
        int16_t barX = x + i * (barWidth + spacing);
        int16_t barY = y + (8 - (i + 1) * 2);
        int16_t currentHeight = (i + 1) * 2;
        
        if (strength > (i * 20)) {
            display->setColor(WHITE);
            display->fillRect(barX, barY, barWidth, currentHeight);
        } else {
            display->setColor(BLACK);
            display->drawRect(barX, barY, barWidth, currentHeight);
        }
    }
}

void MainScreen::drawBatteryIcon(OLEDDisplay* display, int16_t x, int16_t y, uint8_t level) {
    if (!display) return;
    
    // 电池外框
    display->setColor(WHITE);
    display->drawRect(x, y, 12, 6);
    display->drawRect(x + 12, y + 2, 2, 2);
    
    // 电池电量
    if (level > 0) {
        int16_t fillWidth = (level * 10) / 100;
        display->fillRect(x + 1, y + 1, fillWidth, 4);
    }
}

void MainScreen::drawStatusIcon(OLEDDisplay* display, int16_t x, int16_t y, const char* icon, bool active) {
    if (!display) return;
    
    display->setColor(active ? WHITE : BLACK);
    display->drawString(x, y, icon);
}

} // namespace ui
} // namespace graphics

#endif // HAS_SCREEN
