#pragma once

#include "configuration.h"
#include "graphics/Screen.h"
#include "graphics/OLEDDisplay.h"

#if HAS_SCREEN

namespace graphics {
namespace ui {

/**
 * @brief 主界面UI组件
 * 
 * 参考MeshChatstic的UI设计理念，提供现代化的主界面体验
 */
class MainScreen {
public:
    enum class ScreenState {
        HOME,           // 主界面
        QUICK_SETTINGS, // 快速设置
        STATUS_OVERLAY  // 状态覆盖层
    };

    struct StatusInfo {
        uint8_t signalStrength = 0;    // 信号强度 0-100
        uint8_t batteryLevel = 0;       // 电池电量 0-100
        bool gpsConnected = false;     // GPS连接状态
        uint8_t nodeCount = 0;         // 节点数量
        bool wifiConnected = false;     // WiFi连接状态
        bool bluetoothEnabled = false; // 蓝牙状态
    };

    struct QuickAction {
        const char* label;
        const char* icon;
        std::function<void()> action;
    };

    MainScreen();
    ~MainScreen() = default;

    // 界面控制
    void showHomeScreen(OLEDDisplay* display);
    void showQuickSettings(OLEDDisplay* display);
    void showStatusOverlay(OLEDDisplay* display);
    
    // 状态更新
    void updateStatus(const StatusInfo& status);
    void setScreenState(ScreenState state);
    
    // 快速操作
    void addQuickAction(const QuickAction& action);
    void clearQuickActions();
    
    // 事件处理
    bool handleInput(const InputEvent* event);
    
    // 渲染控制
    void forceRefresh();
    void setBrightness(uint8_t level);

private:
    ScreenState currentState;
    StatusInfo currentStatus;
    std::vector<QuickAction> quickActions;
    
    // 渲染方法
    void renderStatusBar(OLEDDisplay* display, int16_t x, int16_t y);
    void renderQuickActions(OLEDDisplay* display, int16_t x, int16_t y);
    void renderMainContent(OLEDDisplay* display, int16_t x, int16_t y);
    void renderNavigation(OLEDDisplay* display, int16_t x, int16_t y);
    
    // 工具方法
    void drawSignalBars(OLEDDisplay* display, int16_t x, int16_t y, uint8_t strength);
    void drawBatteryIcon(OLEDDisplay* display, int16_t x, int16_t y, uint8_t level);
    void drawStatusIcon(OLEDDisplay* display, int16_t x, int16_t y, const char* icon, bool active);
    
    // 动画支持
    uint32_t lastUpdateTime;
    bool animationEnabled;
    uint8_t animationFrame;
};

} // namespace ui
} // namespace graphics

#endif // HAS_SCREEN
