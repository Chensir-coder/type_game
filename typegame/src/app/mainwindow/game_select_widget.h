/* ------------------------------------------------------------------
 // 文件名     : game_select_widget.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 游戏选择控件
------------------------------------------------------------------ */

#ifndef __TYPEGAME_GAME_SELECT_WIDGET_H__
#define __TYPEGAME_GAME_SELECT_WIDGET_H__

#include <QWidget>

class GameCardWidget;

class GameSelectWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameSelectWidget(QWidget* parent = nullptr);

signals:
    void saveAppleSelected();
    void spaceWarSelected();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void setupUi();
    void updateCardPositions();
    int dividerY() const;

private:
    QWidget* m_cards_container = nullptr;
    GameCardWidget* m_save_apple_card = nullptr;
    GameCardWidget* m_space_war_card = nullptr;
};

#endif // __TYPEGAME_GAME_SELECT_WIDGET_H__
