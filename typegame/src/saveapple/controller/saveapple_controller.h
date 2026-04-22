/* ------------------------------------------------------------------
 // 文件名     : saveapple_controller.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏主控制器
------------------------------------------------------------------ */

#ifndef __TYPEGAME_SAVEAPPLE_CONTROLLER_H__
#define __TYPEGAME_SAVEAPPLE_CONTROLLER_H__

#include <QList>

#include "common/core/igame_controller.h"

class SaveAppleModel;
class AppleFactory;
class AppleModel;

/**
 * @brief 拯救苹果游戏主控制器。
 *
 * 职责：
 * 1. 驱动苹果游戏生命周期。
 * 2. 串联 SaveAppleModel 与 AppleFactory。
 * 3. 处理字母输入，并驱动苹果命中与回收。
 * 4. 在 update() 中调度苹果生成、模型更新以及漏掉苹果回收。
 *
 * 边界：
 * 1. 不负责 UI 绘制与页面布局。
 * 2. 不负责核心业务数据保存，业务数据由 SaveAppleModel 管理。
 * 3. 不直接操作对象池，仅通过 AppleFactory 创建与回收苹果。
 */
class SaveAppleController final : public IGameController
{
public:
    /**
     * @brief 构造控制器。
     *
     * @param model 苹果游戏核心业务模型
     * @param apple_factory 苹果实体工厂
     */
    explicit SaveAppleController(SaveAppleModel* model, AppleFactory* apple_factory);

    ~SaveAppleController() override = default;

    SaveAppleController(const SaveAppleController&) = delete;
    SaveAppleController& operator=(const SaveAppleController&) = delete;

    void initialize() override;
    void startGame() override;
    void pauseGame() override;
    void resumeGame() override;
    void stopGame() override;
    void restartGame() override;
    void update(int delta_ms) override;
    bool handleLetterInput(QChar input_letter) override;

    /**
     * @brief 设置生成区域宽度。
     *
     * @param scene_width 场景宽度
     */
    void setSceneWidth(int scene_width);

    /**
     * @brief 获取生成区域宽度。
     *
     * @return 场景宽度
     */
    int sceneWidth() const;

    /**
     * @brief 设置苹果初始生成的 Y 坐标。
     *
     * @param spawn_y 生成纵坐标
     */
    void setSpawnY(int spawn_y);

    /**
     * @brief 获取苹果初始生成 Y 坐标。
     *
     * @return 生成纵坐标
     */
    int spawnY() const;

    /**
     * @brief 设置生成间隔（毫秒）。
     *
     * @param spawn_interval_ms 生成间隔
     */
    void setSpawnIntervalMs(int spawn_interval_ms);

    /**
     * @brief 获取生成间隔（毫秒）。
     *
     * @return 生成间隔
     */
    int spawnIntervalMs() const;

private:
    void resetSpawnTimer();
    void trySpawnApple();
    QChar generateAvailableLetter() const;
    int generateSpawnX() const;

    void recycleInactiveApples(const QList<AppleModel*>& previous_apples);
    bool containsApple(const QList<AppleModel*>& apples, AppleModel* target) const;

private:
    SaveAppleModel* m_model = nullptr;        ///< 苹果游戏业务模型（非拥有型指针）
    AppleFactory* m_apple_factory = nullptr;  ///< 苹果工厂（非拥有型指针）

    int m_scene_width = 800;       ///< 生成区域宽度
    int m_spawn_y = -40;           ///< 苹果初始生成 Y 坐标
    int m_spawn_interval_ms = 900; ///< 苹果生成间隔（毫秒）
    int m_elapsed_spawn_ms = 0;    ///< 当前已累计生成时间（毫秒）
};

#endif // __TYPEGAME_SAVEAPPLE_CONTROLLER_H__
