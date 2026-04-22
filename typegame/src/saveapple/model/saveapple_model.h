/* ------------------------------------------------------------------
 // 文件名     : saveapple_model.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-14
 // 功能描述   : 拯救苹果游戏核心业务模型
------------------------------------------------------------------ */

#ifndef __TYPEGAME_SAVEAPPLE_MODEL_H__
#define __TYPEGAME_SAVEAPPLE_MODEL_H__

#include <QChar>
#include <QList>
#include <QSet>

#include "common/core/game_event.h"
#include "common/core/game_state.h"
#include "common/core/game_event_subject_base.h"

class AppleModel;

/**
 * @brief 拯救苹果游戏核心业务模型。
 *
 * 职责：
 * 1. 管理游戏运行状态、分数和统计信息。
 * 2. 管理当前活动苹果集合。
 * 3. 处理命中、漏失、过关、结束等业务规则。
 * 4. 对外提供统一的苹果速度规则读取接口。
 *
 * 边界：
 * 1. 不负责界面绘制。
 * 2. 不负责按钮交互流程。
 * 3. 不负责苹果对象创建与对象池回收。
 * 4. 不反向依赖 controller / app / view。
 */
class SaveAppleModel final : public GameEventSubjectBase
{
public:
    explicit SaveAppleModel();
    ~SaveAppleModel() override = default;

    SaveAppleModel(const SaveAppleModel&) = delete;
    SaveAppleModel& operator=(const SaveAppleModel&) = delete;

public:
    /**
     * @brief 初始化模型到默认初始状态。
     *
     * 说明：
     * 1. 恢复默认配置。
     * 2. 清空运行时统计与活动苹果。
     * 3. 设置游戏状态为 Initial。
     */
    void initialize();

    /**
     * @brief 重置当前对局，但保留当前设置项。
     *
     * 说明：
     * 1. 保留 speed/max count/target/max miss/sound/fail line 等配置。
     * 2. 清空分数、统计和活动苹果。
     * 3. 状态回到 Initial。
     */
    void resetModel();

    void startGame();
    void pauseGame();
    void resumeGame();
    void stopGame();

    /**
     * @brief 推进模型更新。
     *
     * @param delta_ms 距离上次更新的毫秒数
     */
    void update(int delta_ms);

public:
    bool registerApple(AppleModel* apple);
    bool unregisterApple(AppleModel* apple);

    bool hitAppleByLetter(QChar input_letter);
    AppleModel* findAppleByLetter(QChar letter) const;

    bool canSpawnApple() const;
    bool isLetterAvailable(QChar letter) const;
    void clearActiveApples();

public:
    void setSpeedLevel(int speed_level);
    void setMaxAppleCount(int max_apple_count);
    void setTargetSuccessCount(int target_success_count);
    void setMaxMissCount(int max_miss_count);
    void setSoundEnabled(bool sound_enabled);
    void setFailLineY(int fail_line_y);

public:
    GameState gameState() const;
    int speedLevel() const;
    int maxAppleCount() const;
    int targetSuccessCount() const;
    int maxMissCount() const;
    bool soundEnabled() const;
    int failLineY() const;

    int score() const;
    int successCount() const;
    int missCount() const;
    int accuracy() const;

    bool isLevelCompleted() const;
    const QList<AppleModel*>& activeApples() const;

    /**
     * @brief 获取当前统一苹果下落速度。
     *
     * 说明：
     * 1. 新生成苹果设置速度走这里。
     * 2. 设置变更后同步当前已有苹果速度也走这里。
     *
     * @return 当前苹果下落速度（像素/秒）
     */
    int currentAppleFallSpeed() const;

private:
    // 验证设置项合法性
    bool isValidSpeedLevel(int speed_level) const;
    bool isValidMaxAppleCount(int max_apple_count) const;
    bool isValidTargetSuccessCount(int target_success_count) const;
    bool isValidMaxMissCount(int max_miss_count) const;

    
    // 内部业务逻辑处理
    // 1. 苹果更新与状态检查
    void updateActiveApples(int delta_ms);
    void processMissedApples();
    // 2. 命中与漏失处理
    void handleAppleHit(AppleModel* apple);
    void handleAppleMiss(AppleModel* apple);
    // 3. 苹果管理与字母占用
    void removeAppleInternal(AppleModel* apple);
    void occupyLetter(QChar letter);
    void releaseLetter(QChar letter);
    // 4. 关卡与对局管理
    void finishCurrentRound();
    void syncActiveAppleFallSpeed();
    // 5. 分数与统计计算
    int hitScoreValue() const;
    int missPenaltyValue() const;

    
    // 事件通知
    void notifyStateEvent(GameEventType event_type);
    void notifyScoreChanged();
    void notifyAppleSpawned(QChar letter);
    void notifyAppleRemoved(QChar letter);
    void notifyAppleHit(QChar letter);
    void notifyAppleMiss(QChar letter);
    void notifyLevelCompleted();
    void notifyGameOver();
    void notifySettingsChanged(SettingKey key, int value, int extra_value = 0);
    void notifyInputRejected(QChar letter);

private:
    GameState m_game_state = GameState::Initial;

    int m_speed_level = 1;
    int m_max_apple_count = 3;
    int m_target_success_count = 10;
    int m_max_miss_count = 5;
    bool m_sound_enabled = true;
    int m_fail_line_y = 700;

    int m_score = 0;
    int m_success_count = 0;
    int m_miss_count = 0;

    QList<AppleModel*> m_active_apples;
    QSet<QChar> m_used_letters;
};

#endif // __TYPEGAME_SAVEAPPLE_MODEL_H__
