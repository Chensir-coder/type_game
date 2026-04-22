/* ------------------------------------------------------------------
 // 文件名     : asset_paths.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : UI资源路径定义
------------------------------------------------------------------ */

#ifndef __TYPEGAME_UI_ASSET_PATHS_H__
#define __TYPEGAME_UI_ASSET_PATHS_H__

#include <QString>

namespace UiAssetPaths
{
namespace Common
{
inline QString mainDialogBackground() { return QStringLiteral(":/Common/Images/MAIN_DLG_BG.png"); }
inline QString startButton() { return QStringLiteral(":/Common/Images/PUBLIC_START.png"); }
inline QString pauseButton() { return QStringLiteral(":/Common/Images/PUBLIC_PAUSE.png"); }
inline QString setupButton() { return QStringLiteral(":/Common/Images/PUBLIC_SETUP.png"); }
inline QString endButton() { return QStringLiteral(":/Common/Images/PUBLIC_END.png"); }
inline QString exitButton() { return QStringLiteral(":/Common/Images/PUBLIC_EXIT.png"); }
inline QString okButton() { return QStringLiteral(":/Common/Images/OK.png"); }
inline QString cancelButton() { return QStringLiteral(":/Common/Images/CANCEL.png"); }

inline QString btnClickSound() { return QStringLiteral(":/Common/Sound/BTN_CLICK.wav"); }
inline QString glideSound() { return QStringLiteral(":/Common/Sound/GLIDE.wav"); }
inline QString typeSound() { return QStringLiteral(":/Common/Sound/TYPE.wav"); }

}

namespace Apple
{
inline QString background() { return QStringLiteral(":/Apple/Images/APPLE_BACKGROUND.png"); }
inline QString basket() { return QStringLiteral(":/Apple/Images/APPLE_BASKET.png"); }
inline QString normalApple() { return QStringLiteral(":/Apple/Images/APPLE_NORMAL.png"); }
inline QString badApple() { return QStringLiteral(":/Apple/Images/APPLE_BAD.png"); }
inline QString smallApple() { return QStringLiteral(":/Apple/Images/APPLE_SMALL.png"); }
inline QString setupIcon() { return QStringLiteral(":/Apple/Images/APPLE_SETUP.png"); }
inline QString dialogBackground() { return QStringLiteral(":/Apple/Images/APPLE_DLG_BG.png"); }
inline QString nextButton() { return QStringLiteral(":/Apple/Images/APPLE_DLG_NEXT.png"); }
inline QString endButton() { return QStringLiteral(":/Apple/Images/APPLE_DLG_END.png"); }
inline QString retryButton() { return QStringLiteral(":/Apple/Images/APPLE_DLG_REPLAY.png"); }

inline QString backgroundSound() { return QStringLiteral(":/Apple/Sounds/APPLE_BG.wav"); }
inline QString inSound() { return QStringLiteral(":/Apple/Sounds/APPLE_IN.wav"); }
}

namespace SpaceWar
{
inline QString mainMenuBackground() { return QStringLiteral(":/Spacewar/Images/SPACE_MAINMENU_BG.png"); }
inline QString background() { return QStringLiteral(":/Spacewar/Images/SPACE_BACKGROUND.png"); }
inline QString startButton() { return QStringLiteral(":/Spacewar/Images/SPACE_START.png"); }
inline QString optionButton() { return QStringLiteral(":/Spacewar/Images/SPACE_OPTION.png"); }
inline QString exitButton() { return QStringLiteral(":/Spacewar/Images/SPACE_EXIT.png"); }
}
}

#endif // __TYPEGAME_UI_ASSET_PATHS_H__
