/* ------------------------------------------------------------------
 // 文件名     : letter_entity_base.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 带字母目标实体抽象基类
------------------------------------------------------------------ */

#ifndef __TYPEGAME_LETTER_ENTITY_BASE_H__
#define __TYPEGAME_LETTER_ENTITY_BASE_H__

#include <QChar>

/**
 * @brief 带字母目标实体抽象基类。
 *
 * 适用对象：
 * 1. SaveApple 中的苹果实体。
 * 2. SpaceWar 中的敌机实体。
 *
 * 职责：
 * 1. 提供通用的标识、位置、字母、激活状态管理。
 * 2. 提供字母匹配等公共逻辑。
 * 3. 约束子类实现 reset / update 等核心行为。
 *
 * 说明：
 * 1. 当前先使用 int 表示位置，便于和现有项目风格对齐。
 * 2. 后续如果需要更细粒度位置控制，可再升级为浮点坐标。
 */
class LetterEntityBase
{
public:
    explicit LetterEntityBase() = default;
    virtual ~LetterEntityBase() = default;

    LetterEntityBase(const LetterEntityBase&) = default;
    LetterEntityBase& operator=(const LetterEntityBase&) = default;

    /**
     * @brief 获取实体编号。
     */
    int id() const;

    /**
     * @brief 获取实体横坐标。
     */
    int x() const;

    /**
     * @brief 获取实体纵坐标。
     */
    int y() const;

    /**
     * @brief 获取实体字母。
     */
    QChar letter() const;

    /**
     * @brief 获取实体是否处于激活状态。
     */
    bool isActive() const;

    /**
     * @brief 设置实体编号。
     *
     * @param id 实体编号
     */
    void setId(int id);

    /**
     * @brief 设置实体位置。
     *
     * @param x 横坐标
     * @param y 纵坐标
     */
    void setPosition(int x, int y);

    /**
     * @brief 设置实体字母。
     *
     * @param letter 字母
     */
    void setLetter(QChar letter);

    /**
     * @brief 设置实体激活状态。
     *
     * @param is_active 是否激活
     */
    void setActive(bool is_active);

    /**
     * @brief 判断输入字母是否与当前实体字母匹配。
     *
     * @param input_letter 输入字母
     * @return true 表示匹配，false 表示不匹配
     */
    bool matches(QChar input_letter) const;

    /**
     * @brief 重置实体到可复用的初始状态。
     *
     * 说明：
     * 1. 该接口为后续对象池复用做准备。
     * 2. 派生类应在实现中同时重置自身扩展字段。
     */
    virtual void reset() = 0;

    /**
     * @brief 执行一次实体更新。
     *
     * @param delta_ms 距离上一次更新的毫秒数
     */
    virtual void update(int delta_ms) = 0;

protected:
    int m_id = 0;              ///< 实体编号
    int m_x = 0;               ///< 横坐标
    int m_y = 0;               ///< 纵坐标
    QChar m_letter;            ///< 实体显示字母
    bool m_is_active = false;  ///< 实体是否激活
};

inline int LetterEntityBase::id() const
{
    return m_id;
}

inline int LetterEntityBase::x() const
{
    return m_x;
}

inline int LetterEntityBase::y() const
{
    return m_y;
}

inline QChar LetterEntityBase::letter() const
{
    return m_letter;
}

inline bool LetterEntityBase::isActive() const
{
    return m_is_active;
}

inline void LetterEntityBase::setId(int id)
{
    m_id = id;
}

inline void LetterEntityBase::setPosition(int x, int y)
{
    m_x = x;
    m_y = y;
}

inline void LetterEntityBase::setLetter(QChar letter)
{
    m_letter = letter;
}

inline void LetterEntityBase::setActive(bool is_active)
{
    m_is_active = is_active;
}

inline bool LetterEntityBase::matches(QChar input_letter) const
{
    return m_letter.toUpper() == input_letter.toUpper();
}

#endif // __TYPEGAME_LETTER_ENTITY_BASE_H__
