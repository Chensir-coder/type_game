/* ------------------------------------------------------------------
 // 文件名     : game_card_widget.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 游戏卡片控件
------------------------------------------------------------------ */

#ifndef __TYPEGAME_GAME_CARD_WIDGET_H__
#define __TYPEGAME_GAME_CARD_WIDGET_H__

#include <QWidget>

class QLabel;
class QGraphicsDropShadowEffect;

class GameCardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameCardWidget(const QString& imagePath,
                            const QString& title,
                            QWidget* parent = nullptr);

    void setSelected(bool selected);

signals:
    void clicked();

protected:
    void enterEvent(QEvent* event) override;

    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void setupUi();
    void updateVisualState();

private:
    QString m_image_path;
    QString m_title_text;

    QLabel* m_image_label = nullptr;
    QLabel* m_title_label = nullptr;

    QGraphicsDropShadowEffect* m_shadow = nullptr;

    bool m_hovered = false;
    bool m_selected = false;
};

#endif // __TYPEGAME_GAME_CARD_WIDGET_H__
