/* ------------------------------------------------------------------
 // 文件名     : game_select_widget.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 游戏选择控件实现
------------------------------------------------------------------ */

#include "game_select_widget.h"

#include <QPainter>
#include <QPixmap>
#include <QResizeEvent>
#include <QtGlobal>

#include "app/mainwindow/game_card_widget.h"
#include "app/resources/asset_paths.h"

namespace
{
constexpr int kWindowMinWidth = 960;
constexpr int kWindowMinHeight = 540;
constexpr int kCardSpacing = 48;
constexpr int kCardsTopPadding = 18;
constexpr int kCardsBottomPadding = 24;

// 按老师给的背景图比例计算横线位置：176 高图中，横线大约在 113 像素处
constexpr qreal kDividerRatio = 113.0 / 176.0;
}

GameSelectWidget::GameSelectWidget(QWidget* parent)
    : QWidget(parent)
{
    setObjectName(QStringLiteral("game_select_widget"));
    setMinimumSize(kWindowMinWidth, kWindowMinHeight);

    setupUi();
}

void GameSelectWidget::setupUi()
{
    setAttribute(Qt::WA_StyledBackground, true);

    m_cards_container = new QWidget(this);
    m_cards_container->setAttribute(Qt::WA_TranslucentBackground);

    m_save_apple_card = new GameCardWidget(
        UiAssetPaths::Apple::background(),
        QStringLiteral("拯救苹果"),
        m_cards_container);

    m_space_war_card = new GameCardWidget(
        UiAssetPaths::SpaceWar::mainMenuBackground(),
        QStringLiteral("太空大战"),
        m_cards_container);

    connect(m_save_apple_card, &GameCardWidget::clicked, this, [this]() {
        m_save_apple_card->setSelected(true);
        m_space_war_card->setSelected(false);
        emit saveAppleSelected();
    });

    connect(m_space_war_card, &GameCardWidget::clicked, this, [this]() {
        m_space_war_card->setSelected(true);
        m_save_apple_card->setSelected(false);
        emit spaceWarSelected();
    });

    updateCardPositions();
}

int GameSelectWidget::dividerY() const
{
    return qRound(static_cast<qreal>(height()) * kDividerRatio);
}

void GameSelectWidget::updateCardPositions()
{
    if (m_cards_container == nullptr || m_save_apple_card == nullptr || m_space_war_card == nullptr)
    {
        return;
    }

    const int line_y = dividerY();
    const int top = line_y + kCardsTopPadding;
    const int available_height = qMax(0, height() - top - kCardsBottomPadding);

    const int card_width = m_save_apple_card->width();
    const int card_height = m_save_apple_card->height();
    const int total_width = (card_width * 2) + kCardSpacing;

    const int left = qMax(0, (width() - total_width) / 2);
    const int card_top = top + qMax(0, (available_height - card_height) / 2);

    m_cards_container->setGeometry(0, top, width(), qMax(0, height() - top));
    m_save_apple_card->move(left, card_top - top);
    m_space_war_card->move(left + card_width + kCardSpacing, card_top - top);
}

void GameSelectWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPixmap bg(UiAssetPaths::Common::mainDialogBackground());
    if (!bg.isNull())
    {
        painter.drawPixmap(rect(), bg);
    }
    else
    {
        painter.fillRect(rect(), QColor(214, 222, 232));
    }
}

void GameSelectWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    updateCardPositions();
}
