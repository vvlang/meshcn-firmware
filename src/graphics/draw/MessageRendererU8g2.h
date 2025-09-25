#pragma once

#include "OLEDDisplay.h"
#include "../U8g2Display.h"
#include "graphics/emotes.h"
#include <string>
#include <vector>

namespace graphics
{
namespace MessageRendererU8g2
{

/**
 * 使用U8g2的UTF-8支持渲染带表情的字符串
 * 这是原有drawStringWithEmotes的U8g2优化版本
 */
void drawStringWithEmotesU8g2(OLEDDisplay *display, int x, int y, const std::string &line, const Emote *emotes, int emoteCount);

/**
 * 使用U8g2渲染消息内容
 * 这是原有renderMessageContent的U8g2优化版本
 */
void renderMessageContentU8g2(OLEDDisplay *display, const std::vector<std::string> &lines, const std::vector<int> &rowHeights, int x,
                              int yOffset, int scrollBottom, const Emote *emotes, int numEmotes, bool isInverted, bool isBold);

/**
 * 使用U8g2生成文本行
 * 这是原有generateLines的U8g2优化版本
 */
std::vector<std::string> generateLinesU8g2(OLEDDisplay *display, const char *headerStr, const char *messageBuf, int textWidth);

} // namespace MessageRendererU8g2
} // namespace graphics
