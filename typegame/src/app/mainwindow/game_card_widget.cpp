/* ------------------------------------------------------------------
 // 文件名     : game_card_widget.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 游戏卡片控件实现
------------------------------------------------------------------ */

#include "game_card_widget.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>


GameCardWidget::GameCardWidget(const QString& imagePath,
                               const QString& title,
                               QWidget* parent)
    : QWidget(parent)
    , m_image_path(imagePath)
    , m_title_text(title)
{
    setFixedSize(200, 160);  // 卡片整体大小
    setAttribute(Qt::WA_Hover, true);
    setCursor(Qt::PointingHandCursor);

    setupUi();
    updateVisualState();
}

void GameCardWidget::setSelected(bool selected)
{
    m_selected = selected;
    updateVisualState();
    update();
}

void GameCardWidget::setupUi()
{
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);  // ✅ 四周边距完全一致 = 0
    layout->setSpacing(0);

    // 图片 Label 充满整个卡片
    m_image_label = new QLabel(this);
    m_image_label->setScaledContents(true);        // ✅ 核心：让图片自动拉伸填满控件
    m_image_label->setAlignment(Qt::AlignCenter);

    QPixmap pix(m_image_path);
    if (!pix.isNull())
    {
        m_image_label->setPixmap(pix);
    }

    // 把图片添加到布局，让它自动拉伸填满整个卡片
    layout->addWidget(m_image_label);

    // 阴影效果
    m_shadow = new QGraphicsDropShadowEffect(this);
    m_shadow->setBlurRadius(18);
    m_shadow->setOffset(0, 4);
    m_shadow->setColor(QColor(0, 0, 0, 60));
    setGraphicsEffect(m_shadow);
}

void GameCardWidget::updateVisualState()
{
    if (m_shadow == nullptr)
        return;

    if (m_hovered || m_selected)
    {
        m_shadow->setBlurRadius(28);
        m_shadow->setOffset(0, 6);
        m_shadow->setColor(QColor(80, 170, 255, 180));
    }
    else
    {
        m_shadow->setBlurRadius(18);
        m_shadow->setOffset(0, 4);
        m_shadow->setColor(QColor(0, 0, 0, 60));
    }
}

void GameCardWidget::enterEvent(QEvent* event)
{
    QWidget::enterEvent(event);
    m_hovered = true;
    updateVisualState();
    update();
}

void GameCardWidget::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
    m_hovered = false;
    updateVisualState();
    update();
}

void GameCardWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        emit clicked();

    QWidget::mousePressEvent(event);
}

void GameCardWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF cardRect = rect().adjusted(0, 0, 0, 0);  // ✅ 无边距，整个卡片都是图片

    QColor fillColor = QColor(250, 250, 250, 235);
    QColor borderColor = m_hovered || m_selected
        ? QColor(90, 170, 255, 220)
        : QColor(190, 198, 208, 200);

    painter.setPen(QPen(borderColor, m_hovered || m_selected ? 2.0 : 1.0));
    painter.setBrush(fillColor);
    painter.drawRect(cardRect);  // ✅ 直角矩形
}