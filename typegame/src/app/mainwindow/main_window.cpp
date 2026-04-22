/* ------------------------------------------------------------------
 // 文件名     : main_window.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 主窗口实现
------------------------------------------------------------------ */

#include "main_window.h"

#include <QMessageBox>

#include "app/factory/game_factory.h"
#include "app/mainwindow/game_select_widget.h"
#include "app/mainwindow/game_window.h"
#include "common/core/igame.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setupUi();
}

MainWindow::~MainWindow() = default;

void MainWindow::setupUi()
{
    resize(960, 540);
    setMinimumSize(960, 540);
    setWindowTitle(QStringLiteral("TypeGame"));

    m_game_select_widget = new GameSelectWidget(this);
    setCentralWidget(m_game_select_widget);

    connect(m_game_select_widget, &GameSelectWidget::saveAppleSelected,
            this, &MainWindow::onSaveAppleSelected);
    connect(m_game_select_widget, &GameSelectWidget::spaceWarSelected,
            this, &MainWindow::onSpaceWarSelected);
}

void MainWindow::onSaveAppleSelected()
{
    auto game = GameFactory::createGame(GameType::SaveApple);
    if (game == nullptr)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("该游戏暂未实现。"));
        return;
    }

    GameWindow* game_window = new GameWindow(std::move(game));
    game_window->show();
    m_game_windows.append(game_window);
}

void MainWindow::onSpaceWarSelected()
{
    auto game = GameFactory::createGame(GameType::SpaceWar);
    if (game == nullptr)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("该游戏暂未实现。"));
        return;
    }

    GameWindow* game_window = new GameWindow(std::move(game));
    game_window->show();
    m_game_windows.append(game_window);
}


