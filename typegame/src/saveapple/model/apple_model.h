/* ------------------------------------------------------------------
 // 文件名     : apple_model.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏中的苹果实体模型
------------------------------------------------------------------ */

#ifndef __TYPEGAME_APPLE_MODEL_H__
#define __TYPEGAME_APPLE_MODEL_H__

#include "common/core/letter_entity_base.h"
#include "common/pool/ipoolable.h"

/**
 * @brief 拯救苹果游戏中的苹果实体模型。
 *
 * 职责：
 * 1. 表示单个苹果实体的状态。
 * 2. 维护苹果自身的扩展属性，如下落速度、命中状态。
 * 3. 在 update() 中推进单个苹果的下落逻辑。
 * 4. 支持对象池复用。
 *
 * 说明：
 * 1. AppleModel 继承自 LetterEntityBase，复用通用字母实体基础能力。
 * 2. AppleModel 实现 IPoolable，便于后续由对象池统一复用。
 * 3. AppleModel 不负责整局游戏规则，仅负责单个苹果自身行为。
 */
class AppleModel final : public LetterEntityBase, public IPoolable
{
public:
    explicit AppleModel();
    ~AppleModel() override = default;

    AppleModel(const AppleModel&) = default;
    AppleModel& operator=(const AppleModel&) = default;

    /**
     * @brief 获取苹果下落速度。
     *
     * @return 下落速度（像素/秒）
     */
    int fallSpeed() const;

    /**
     * @brief 获取苹果是否已命中。
     *
     * @return true 表示已命中，false 表示未命中
     */
    bool isHit() const;

    /**
     * @brief 设置苹果下落速度。
     *
     * @param fall_speed 下落速度（像素/秒）
     */
    void setFallSpeed(int fall_speed);

    /**
     * @brief 设置苹果命中状态。
     *
     * @param is_hit 是否命中
     */
    void setHit(bool is_hit);

    /**
     * @brief 重置苹果到可复用的初始状态。
     *
     * 说明：
     * 1. 该方法用于对象池回收后复用。
     * 2. 会同时重置通用实体属性和苹果扩展属性。
     */
    void reset() override;

    /**
     * @brief 推进苹果更新。
     *
     * @param delta_ms 距离上一次更新的毫秒数
     *
     * 说明：
     * 1. 当前实现为竖直匀速下落。
     * 2. 若苹果未激活，则不进行更新。
     */
    void update(int delta_ms) override;

private:
    int m_fall_speed = 120; ///< 苹果下落速度（像素/秒）
    bool m_is_hit = false;  ///< 苹果是否已命中
};

#endif // __TYPEGAME_APPLE_MODEL_H__
