/* ------------------------------------------------------------------
 // 文件名     : audio_service.h
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-18
 // 功能描述   : 通用音频服务抽象接口
------------------------------------------------------------------ */

#ifndef __TYPEGAME_AUDIO_SERVICE_H__
#define __TYPEGAME_AUDIO_SERVICE_H__

#include <QString>

enum class AudioCue
{
    None = 0,

    EntityHit       ///< 苹果命中音效
};

class AudioService
{
public:
    virtual ~AudioService() = default;

    virtual void initialize() = 0;
    virtual void shutdown() = 0;

    // ---------- 短音效 ----------
    virtual void registerCue(AudioCue cue, const QString& source_path) = 0;
    virtual void playCue(AudioCue cue) = 0;
    virtual void stopCue(AudioCue cue) = 0;
    virtual void stopAllCues() = 0;

    // ---------- 背景音乐 ----------
    virtual void setBackgroundMusic(const QString& source_path) = 0;
    virtual void playBackgroundMusic() = 0;
    virtual void pauseBackgroundMusic() = 0;
    virtual void resumeBackgroundMusic() = 0;
    virtual void stopBackgroundMusic() = 0;
    virtual bool isBackgroundMusicPlaying() const = 0;

    // ---------- 总开关 ----------
    virtual void setEnabled(bool enabled) = 0;
    virtual bool isEnabled() const = 0;

    // ---------- 音量 ----------
    virtual void setEffectVolume(float volume) = 0;
    virtual float effectVolume() const = 0;

    virtual void setBackgroundMusicVolume(float volume) = 0;
    virtual float backgroundMusicVolume() const = 0;
};

#endif // __TYPEGAME_AUDIO_SERVICE_H__
