/* ------------------------------------------------------------------
 // 文件名     : main.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 程序入口
------------------------------------------------------------------ */

#include <QApplication>
#include <locale>
#include "app/application/game_application.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");  // Windows/Linux 通用
    QApplication application(argc, argv);

    GameApplication game_application;
    game_application.initialize();

    const int init_result = game_application.run();
    if (init_result != 0)
    {
        return init_result;
    }

    return application.exec();
}
