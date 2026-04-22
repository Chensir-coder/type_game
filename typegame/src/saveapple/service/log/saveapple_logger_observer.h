/* ------------------------------------------------------------------
 // 文件名     : saveapple_logger_observer.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-19
 // 功能描述   : 拯救苹果游戏日志观察者接口
------------------------------------------------------------------ */

#pragma once

#include "common/core/igame_observer.h"
#include "common/service/log/ilogger.h"

class SaveAppleLoggerObserver : public IGameObserver
{
public:
    explicit SaveAppleLoggerObserver(ILogger* logger);

    void onGameEvent(const GameEvent& event) override;

private:
    ILogger* m_logger = nullptr;
};
