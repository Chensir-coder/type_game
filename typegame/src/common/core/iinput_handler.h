/* ------------------------------------------------------------------
 // 文件名     : iinput_handler.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 通用输入处理接口
------------------------------------------------------------------ */

#ifndef __TYPEGAME_IINPUT_HANDLER_H__
#define __TYPEGAME_IINPUT_HANDLER_H__

#include <QChar>

/**
 * @brief 通用输入处理接口。
 *
 * 职责：
 * 1. 为字母输入处理提供统一抽象。
 * 2. 便于后续将输入逻辑从 controller 中拆分出去。
 *
 * 适用场景：
 * 1. SaveApple 中的字母命中处理。
 * 2. SpaceWar 中的字母锁敌/发射逻辑处理。
 */
class IInputHandler
{
public:
    virtual ~IInputHandler() = default;

    /**
     * @brief 处理字母输入。
     *
     * @param input_letter 输入字母
     * @return true 表示成功处理，false 表示未处理
     */
    virtual bool handleLetterInput(QChar input_letter) = 0;
};

#endif // __TYPEGAME_IINPUT_HANDLER_H__
