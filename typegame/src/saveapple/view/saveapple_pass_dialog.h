/* ------------------------------------------------------------------
 // 文件名     : saveapple_pass_dialog.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏过关弹窗
------------------------------------------------------------------ */

#ifndef __TYPEGAME_SAVEAPPLE_PASS_DIALOG_H__
#define __TYPEGAME_SAVEAPPLE_PASS_DIALOG_H__

#include <QDialog>
#include <QPixmap>
#include "common/view/sprite_button.h"

class QLabel;
class SpriteButton;
class QPaintEvent;

class SaveApplePassDialog final : public QDialog
{
    Q_OBJECT

public:
    explicit SaveApplePassDialog(QWidget* parent = nullptr);
    ~SaveApplePassDialog() override = default;

signals:
    void endClicked();
    void nextLevelClicked();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void setupUi();

private:

    QPixmap m_confrim_button_pixmap;              ///< 确认按钮图
    QPixmap m_next_level_button_pixmap;           ///< 下一关按钮图
    
    QLabel* m_message_label = nullptr;
    SpriteButton* m_confirm_button = nullptr;
    SpriteButton* m_next_level_button = nullptr;

    QPixmap m_background_pixmap;
};
#endif // __TYPEGAME_SAVEAPPLE_PASS_DIALOG_H__
