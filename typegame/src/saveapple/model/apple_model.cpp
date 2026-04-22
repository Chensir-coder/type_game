/* ------------------------------------------------------------------
 // 文件名     : apple_model.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏中的苹果实体模型实现
------------------------------------------------------------------ */

#include "apple_model.h"

AppleModel::AppleModel()
{
    reset();
}

int AppleModel::fallSpeed() const
{
    return m_fall_speed;
}

bool AppleModel::isHit() const
{
    return m_is_hit;
}

void AppleModel::setFallSpeed(int fall_speed)
{
    if (fall_speed <= 0)
    {
        return;
    }

    m_fall_speed = fall_speed;
}

void AppleModel::setHit(bool is_hit)
{
    m_is_hit = is_hit;
}

void AppleModel::reset()
{
    m_id = 0;
    m_x = 0;
    m_y = 0;
    m_letter = QChar();
    m_is_active = false;

    m_fall_speed = 120;
    m_is_hit = false;
}

void AppleModel::update(int delta_ms)
{
    if (!m_is_active)
    {
        return;
    }

    if (delta_ms <= 0)
    {
        return;
    }

    const int delta_y = (m_fall_speed * delta_ms) / 1000;
    m_y += delta_y;
}
