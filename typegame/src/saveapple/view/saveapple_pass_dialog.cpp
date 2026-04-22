/* ------------------------------------------------------------------
 // 文件名     : saveapple_pass_dialog.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏过关弹窗实现
------------------------------------------------------------------ */

#include "saveapple_pass_dialog.h"

#include "app/resources/asset_paths.h"
#include "common/view/sprite_button.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QVBoxLayout>
#include <QWidget>

namespace
{
constexpr int kDialogWidth = 640;
constexpr int kDialogHeight = 360;

constexpr int kButtonWidth = 132;
constexpr int kButtonHeight = 60;
}

SaveApplePassDialog::SaveApplePassDialog(QWidget* parent)
    : QDialog(parent)
    , m_background_pixmap(UiAssetPaths::Apple::dialogBackground())
    , m_confrim_button_pixmap(UiAssetPaths::Apple::endButton())
    , m_next_level_button_pixmap(UiAssetPaths::Apple::nextButton())
{
    setupUi();
}

void SaveApplePassDialog::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    if (!m_background_pixmap.isNull())
    {
        painter.drawPixmap(rect(), m_background_pixmap);
    }
    else
    {
        painter.fillRect(rect(), QColor(255, 242, 220));
    }

    QDialog::paintEvent(event);
}

void SaveApplePassDialog::setupUi()
{
    setObjectName(QStringLiteral("saveapple_pass_dialog"));
    setModal(true);
    resize(kDialogWidth, kDialogHeight);

    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(28, 24, 28, 24);
    main_layout->setSpacing(0);

    main_layout->addStretch();

    QWidget* message_container = new QWidget(this);
    message_container->setStyleSheet(QStringLiteral(
        "QWidget {"
        "  background: transparent;"
        "}"
    ));

    QHBoxLayout* message_layout = new QHBoxLayout(message_container);
    message_layout->setContentsMargins(0, 0, 0, 0);
    message_layout->setSpacing(0);

    message_layout->addStretch(3);

    m_message_label = new QLabel(QStringLiteral("恭喜您，过关了！"), message_container);
    m_message_label->setAlignment(Qt::AlignCenter);
    m_message_label->setStyleSheet(QStringLiteral(
        "QLabel {"
        "  color: #FFF7E8;"
        "  font-size: 30px;"
        "  font-weight: 800;"
        "  background: rgba(60, 30, 10, 110);"
        "  border: 1px solid rgba(255, 235, 200, 120);"
        "  border-radius: 18px;"
        "  padding: 16px 28px;"
        "}"
    ));

    message_layout->addWidget(m_message_label, 0, Qt::AlignVCenter);
    message_layout->addStretch(1);

    main_layout->addWidget(message_container);
    main_layout->addStretch();

    QWidget* button_container = new QWidget(this);
    button_container->setStyleSheet(QStringLiteral("background: transparent;"));

    QHBoxLayout* button_layout = new QHBoxLayout(button_container);
    button_layout->setContentsMargins(0, 0, 0, 0);
    button_layout->setSpacing(28);

    button_layout->addStretch();

    m_confirm_button = new SpriteButton(button_container);
    m_next_level_button = new SpriteButton(button_container);

    m_confirm_button->setFixedSize(kButtonWidth, kButtonHeight);
    m_next_level_button->setFixedSize(kButtonWidth, kButtonHeight);

    m_confirm_button->setSprite(m_confrim_button_pixmap);
    m_next_level_button->setSprite(m_next_level_button_pixmap);

    button_layout->addWidget(m_confirm_button);
    button_layout->addWidget(m_next_level_button);
    button_layout->addStretch();

    main_layout->addWidget(button_container);

    connect(m_confirm_button, &QPushButton::clicked, this, [this]() {
        emit endClicked();
        accept();
    });
    connect(m_next_level_button, &QPushButton::clicked, this, [this]() {
        emit nextLevelClicked();
        accept();
    });
}
