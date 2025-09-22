#pragma once

#include "../configuration.h"
#include <OLEDDisplay.h>

#if HAS_SCREEN

namespace graphics {
namespace ui {

/**
 * @brief 快速设置面板
 * 
 * 提供常用设置的快速访问，参考MeshChatstic的设置界面设计
 */
class QuickSettingsPanel {
public:
    enum class SettingType {
        TOGGLE,     // 开关类型
        SLIDER,     // 滑块类型
        SELECTION   // 选择类型
    };

    struct SettingItem {
        const char* label;
        const char* icon;
        SettingType type;
        bool* boolValue;
        uint8_t* intValue;
        uint8_t minValue;
        uint8_t maxValue;
        const char** options;  // 选择类型的选项
        uint8_t optionCount;
    };

    QuickSettingsPanel();
    ~QuickSettingsPanel() = default;

    // 界面控制
    void show(OLEDDisplay* display);
    void hide();
    bool isVisible() const { return visible; }
    
    // 设置管理
    void addSetting(const SettingItem& setting);
    void clearSettings();
    
    // 导航控制
    void selectNext();
    void selectPrevious();
    void toggleCurrent();
    void adjustCurrent(int8_t delta);
    
    // 事件处理
    bool handleInput(const InputEvent* event);
    
    // 状态更新
    void updateSettings();

private:
    bool visible;
    uint8_t selectedIndex;
    std::vector<SettingItem> settings;
    
    // 渲染方法
    void renderBackground(OLEDDisplay* display);
    void renderTitle(OLEDDisplay* display);
    void renderSettings(OLEDDisplay* display);
    void renderSelection(OLEDDisplay* display);
    
    // 工具方法
    void drawToggle(OLEDDisplay* display, int16_t x, int16_t y, bool value);
    void drawSlider(OLEDDisplay* display, int16_t x, int16_t y, uint8_t value, uint8_t min, uint8_t max);
    void drawSelection(OLEDDisplay* display, int16_t x, int16_t y, uint8_t value, const char** options, uint8_t count);
    void drawSelectionIndicator(OLEDDisplay* display, int16_t x, int16_t y);
};

} // namespace ui
} // namespace graphics

#endif // HAS_SCREEN
