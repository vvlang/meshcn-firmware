/**
 * U8g2消息渲染器
 * 
 * 这个文件提供了专门为U8g2显示器优化的消息渲染功能
 * 支持中文字符的正确显示，避免字符映射问题
 */

#include "MessageRendererU8g2.h"
#include "../U8g2Display.h"
#include "../U8g2ChineseFonts.h"
#include "../emotes.h"
#include <string>

namespace graphics
{
namespace MessageRendererU8g2
{

/**
 * 使用U8g2的UTF-8支持渲染带表情的字符串
 * 这是原有drawStringWithEmotes的U8g2优化版本
 */
void drawStringWithEmotesU8g2(OLEDDisplay *display, int x, int y, const std::string &line, const Emote *emotes, int emoteCount)
{
    // 检查是否是U8g2显示器（使用编译时检查）
    #if !defined(USE_U8G2_SSD1306) && !defined(USE_U8G2_SH1106)
    // 如果不是U8g2显示器，回退到原有逻辑
    MessageRenderer::drawStringWithEmotes(display, x, y, line, emotes, emoteCount);
    return;
    #endif

    U8g2Display *u8g2Display = static_cast<U8g2Display *>(display);

    U8G2 *u8g2 = u8g2Display->getU8g2();
    if (!u8g2) {
        return;
    }

    // 设置中文字体
    setupChineseFont(u8g2);

    int cursorX = x;
    int fontY = y;
    bool inBold = false;

    size_t i = 0;
    while (i < line.length()) {
        // 检查粗体标记
        if (line.compare(i, 2, "**") == 0) {
            inBold = !inBold;
            i += 2;
            continue;
        }

        // 查找下一个表情符号
        size_t nextEmotePos = std::string::npos;
        const Emote *matchedEmote = nullptr;
        size_t emojiLen = 0;

        for (int e = 0; e < emoteCount; ++e) {
            size_t pos = line.find(emotes[e].label, i);
            if (pos != std::string::npos && (nextEmotePos == std::string::npos || pos < nextEmotePos)) {
                nextEmotePos = pos;
                matchedEmote = &emotes[e];
                emojiLen = strlen(emotes[e].label);
            }
        }

        // 渲染到表情符号或粗体标记的文本段
        size_t nextControl = std::min(nextEmotePos, line.find("**", i));
        if (nextControl == std::string::npos)
            nextControl = line.length();

        if (nextControl > i) {
            std::string textChunk = line.substr(i, nextControl - i);
            
            // 使用U8g2的UTF-8支持直接渲染中文字符
            if (inBold) {
                // 粗体：绘制两次，偏移1像素
                u8g2->drawUTF8(cursorX + 1, fontY, textChunk.c_str());
            }
            u8g2->drawUTF8(cursorX, fontY, textChunk.c_str());
            
            // 计算文本宽度
            cursorX += u8g2->getUTF8Width(textChunk.c_str());
            i = nextControl;
            continue;
        }

        // 渲染表情符号（如果找到）
        if (matchedEmote && i == nextEmotePos) {
            int iconY = y - matchedEmote->height / 2 - 1;
            u8g2->drawXBM(cursorX, iconY, matchedEmote->width, matchedEmote->height, matchedEmote->bitmap);
            cursorX += matchedEmote->width + 1;
            i += emojiLen;
        } else {
            // 没有更多表情符号 - 渲染剩余文本
            std::string remaining = line.substr(i);
            if (inBold) {
                u8g2->drawUTF8(cursorX + 1, fontY, remaining.c_str());
            }
            u8g2->drawUTF8(cursorX, fontY, remaining.c_str());
            break;
        }
    }
}

/**
 * 使用U8g2渲染消息内容
 * 这是原有renderMessageContent的U8g2优化版本
 */
void renderMessageContentU8g2(OLEDDisplay *display, const std::vector<std::string> &lines, const std::vector<int> &rowHeights, int x,
                              int yOffset, int scrollBottom, const Emote *emotes, int numEmotes, bool isInverted, bool isBold)
{
    // 检查是否是U8g2显示器（使用编译时检查）
    #if !defined(USE_U8G2_SSD1306) && !defined(USE_U8G2_SH1106)
    // 如果不是U8g2显示器，回退到原有逻辑
    MessageRenderer::renderMessageContent(display, lines, rowHeights, x, yOffset, scrollBottom, emotes, numEmotes, isInverted, isBold);
    return;
    #endif

    U8g2Display *u8g2Display = static_cast<U8g2Display *>(display);

    U8G2 *u8g2 = u8g2Display->getU8g2();
    if (!u8g2) {
        return;
    }

    // 设置中文字体
    setupChineseFont(u8g2);

    for (size_t i = 0; i < lines.size(); ++i) {
        int lineY = yOffset;
        for (size_t j = 0; j < i; ++j)
            lineY += rowHeights[j];
        if (lineY > -rowHeights[i] && lineY < scrollBottom) {
            if (i == 0 && isInverted) {
                // 使用U8g2的UTF-8支持渲染
                u8g2->drawUTF8(x, lineY, lines[i].c_str());
                if (isBold)
                    u8g2->drawUTF8(x, lineY, lines[i].c_str());
            } else {
                drawStringWithEmotesU8g2(display, x, lineY, lines[i], emotes, numEmotes);
            }
        }
    }
}

/**
 * 使用U8g2生成文本行
 * 这是原有generateLines的U8g2优化版本
 */
std::vector<std::string> generateLinesU8g2(OLEDDisplay *display, const char *headerStr, const char *messageBuf, int textWidth)
{
    // 检查是否是U8g2显示器（使用编译时检查）
    #if !defined(USE_U8G2_SSD1306) && !defined(USE_U8G2_SH1106)
    // 如果不是U8g2显示器，回退到原有逻辑
    return MessageRenderer::generateLines(display, headerStr, messageBuf, textWidth);
    #endif

    U8g2Display *u8g2Display = static_cast<U8g2Display *>(display);

    U8G2 *u8g2 = u8g2Display->getU8g2();
    if (!u8g2) {
        return std::vector<std::string>();
    }

    // 设置中文字体
    setupChineseFont(u8g2);

    std::vector<std::string> lines;
    lines.push_back(std::string(headerStr)); // 标题行始终在第一行

    std::string line, word;
    for (int i = 0; messageBuf[i]; ++i) {
        char ch = messageBuf[i];
        
        // 处理特殊UTF-8字符
        if ((unsigned char)messageBuf[i] == 0xE2 && (unsigned char)messageBuf[i + 1] == 0x80 &&
            (unsigned char)messageBuf[i + 2] == 0x99) {
            ch = '\''; // 普通撇号
            i += 2;    // 跳过额外的UTF-8字节
        }
        
        if (ch == '\n') {
            if (!word.empty())
                line += word;
            if (!line.empty())
                lines.push_back(line);
            line.clear();
            word.clear();
        } else if (ch == ' ') {
            line += word + ' ';
            word.clear();
        } else {
            word += ch;
            std::string test = line + word;
            
            // 使用U8g2的UTF-8宽度计算
            uint16_t strWidth = u8g2->getUTF8Width(test.c_str());
            if (strWidth > textWidth) {
                if (!line.empty())
                    lines.push_back(line);
                line = word;
                word.clear();
            }
        }
    }

    if (!word.empty())
        line += word;
    if (!line.empty())
        lines.push_back(line);

    return lines;
}

} // namespace MessageRendererU8g2
} // namespace graphics
