/* ------------------------------------------------------------------
 // 文件名     : saveapple_model.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-14
 // 功能描述   : 拯救苹果游戏核心业务模型实现
------------------------------------------------------------------ */

#include "saveapple_model.h"

#include <algorithm>

#include "common/core/game_event.h"
#include "saveapple/model/apple_model.h"


SaveAppleModel::SaveAppleModel()
{
    initialize();
}

void SaveAppleModel::initialize()
{
    m_game_state = GameState::Initial;

    m_speed_level = 5;
    m_max_apple_count = 3;
    m_target_success_count = 5;
    m_max_miss_count = 3;
    m_sound_enabled = true;
    m_fail_line_y = 700;

    m_score = 0;
    m_success_count = 0;
    m_miss_count = 0;

    clearActiveApples();

    notifyStateEvent(GameEventType::GameInitialized);
    notifyStateEvent(GameEventType::GameStateChanged);
    notifyScoreChanged();
}

void SaveAppleModel::resetModel()
{
    m_score = 0;
    m_success_count = 0;
    m_miss_count = 0;

    clearActiveApples();
    m_game_state = GameState::Initial;

    notifyStateEvent(GameEventType::GameRestarted);
    notifyStateEvent(GameEventType::GameStateChanged);
    notifyScoreChanged();
}

void SaveAppleModel::startGame()
{
    if (m_game_state == GameState::Playing)
    {
        return;
    }

    if (m_game_state == GameState::End)
    {
        resetModel();
    }

    m_game_state = GameState::Playing;
    notifyStateEvent(GameEventType::GameStarted);
    notifyStateEvent(GameEventType::GameStateChanged);
}

void SaveAppleModel::pauseGame()
{
    if (m_game_state != GameState::Playing)
    {
        return;
    }

    m_game_state = GameState::Paused;
    notifyStateEvent(GameEventType::GamePaused);
    notifyStateEvent(GameEventType::GameStateChanged);
}

void SaveAppleModel::resumeGame()
{
    if (m_game_state != GameState::Paused)
    {
        return;
    }

    m_game_state = GameState::Playing;
    notifyStateEvent(GameEventType::GameResumed);
    notifyStateEvent(GameEventType::GameStateChanged);
}

void SaveAppleModel::stopGame()
{
    // if (m_game_state == GameState::End)
    // {
    //     return;
    // }

    
    m_game_state = GameState::End;
    resetModel();

    notifyStateEvent(GameEventType::GameStopped);
    notifyStateEvent(GameEventType::GameStateChanged);

    
}

void SaveAppleModel::update(int delta_ms)
{
    // std::cout<<"更新模型, delta_ms="<<delta_ms<<std::endl;
    if (m_game_state != GameState::Playing)
    {
        return;
    }

    if (delta_ms <= 0)
    {
        return;
    }

    updateActiveApples(delta_ms);
    processMissedApples();

    if (isLevelCompleted())
    {
        finishCurrentRound();
    }
}

bool SaveAppleModel::registerApple(AppleModel* apple)
{
    if (apple == nullptr)
    {
        return false;
    }

    if (!canSpawnApple())
    {
        return false;
    }

    if (!isLetterAvailable(apple->letter()))
    {
        return false;
    }

    if (m_active_apples.contains(apple))
    {
        return false;
    }

    m_active_apples.append(apple);
    occupyLetter(apple->letter());
    apple->setActive(true);

    notifyAppleSpawned(apple->letter());

    return true;
}

bool SaveAppleModel::unregisterApple(AppleModel* apple)
{

    if (apple == nullptr)
    {
        return false;
    }

    if (!m_active_apples.contains(apple))
    {
        return false;
    }

    const QChar apple_letter = apple->letter();
    removeAppleInternal(apple);
    notifyAppleRemoved(apple_letter);
    return true;
}

bool SaveAppleModel::hitAppleByLetter(QChar input_letter)
{

    if (m_game_state != GameState::Playing)
    {
        return false;
    }

    AppleModel* apple = findAppleByLetter(input_letter);
    if (apple == nullptr)
    {
        notifyInputRejected(input_letter);
        return false;
    }

    handleAppleHit(apple);
    return true;
}

AppleModel* SaveAppleModel::findAppleByLetter(QChar letter) const
{
    const QChar normalized_letter = letter.toUpper();

    for (AppleModel* apple : m_active_apples)
    {
        if (apple == nullptr)
        {
            continue;
        }

        if (apple->matches(normalized_letter))
        {
            return apple;
        }
    }

    return nullptr;
}

bool SaveAppleModel::canSpawnApple() const
{
    return m_game_state != GameState::End
        && m_active_apples.size() < m_max_apple_count;
}

bool SaveAppleModel::isLetterAvailable(QChar letter) const
{
    return !m_used_letters.contains(letter.toUpper());
}

void SaveAppleModel::clearActiveApples()
{
    for (AppleModel* apple : m_active_apples)
    {
        if (apple != nullptr)
        {
            apple->setActive(false);
        }
    }

    m_active_apples.clear();
    m_used_letters.clear();
}

void SaveAppleModel::setSpeedLevel(int speed_level)
{
    if (!isValidSpeedLevel(speed_level))
    {
        return;
    }

    if (m_speed_level == speed_level)
    {
        return;
    }

    m_speed_level = speed_level;
    syncActiveAppleFallSpeed();
    notifySettingsChanged(SettingKey::SpeedLevel, m_speed_level);
}

void SaveAppleModel::setMaxAppleCount(int max_apple_count)
{
    if (!isValidMaxAppleCount(max_apple_count))
    {
        return;
    }

    m_max_apple_count = max_apple_count;
    notifySettingsChanged(SettingKey::MaxAppleCount, m_max_apple_count);
}

void SaveAppleModel::setTargetSuccessCount(int target_success_count)
{
    if (!isValidTargetSuccessCount(target_success_count))
    {
        return;
    }

    m_target_success_count = target_success_count;
    notifySettingsChanged(SettingKey::TargetSuccessCount, m_target_success_count);
}

void SaveAppleModel::setMaxMissCount(int max_miss_count)
{
    if (!isValidMaxMissCount(max_miss_count))
    {
        return;
    }

    m_max_miss_count = max_miss_count;
    notifySettingsChanged(SettingKey::MaxMissCount, m_max_miss_count);
}

void SaveAppleModel::setSoundEnabled(bool sound_enabled)
{
    m_sound_enabled = sound_enabled;
    notifySettingsChanged(SettingKey::SoundEnabled, m_sound_enabled ? 1 : 0);
}

void SaveAppleModel::setFailLineY(int fail_line_y)
{
    if (fail_line_y <= 0)
    {
        return;
    }

    m_fail_line_y = fail_line_y;
    notifySettingsChanged(SettingKey::FailLineY, m_fail_line_y);
}

GameState SaveAppleModel::gameState() const
{
    return m_game_state;
}

int SaveAppleModel::speedLevel() const
{
    return m_speed_level;
}

int SaveAppleModel::maxAppleCount() const
{
    return m_max_apple_count;
}

int SaveAppleModel::targetSuccessCount() const
{
    return m_target_success_count;
}

int SaveAppleModel::maxMissCount() const
{
    return m_max_miss_count;
}

bool SaveAppleModel::soundEnabled() const
{
    return m_sound_enabled;
}

int SaveAppleModel::failLineY() const
{
    return m_fail_line_y;
}

int SaveAppleModel::score() const
{
    return m_score;
}

int SaveAppleModel::successCount() const
{
    return m_success_count;
}

int SaveAppleModel::missCount() const
{
    return m_miss_count;
}

int SaveAppleModel::accuracy() const
{
    const int total_count = m_success_count + m_miss_count;
    if (total_count <= 0)
    {
        return 0;
    }

    return (m_success_count * 100) / total_count;
}

bool SaveAppleModel::isLevelCompleted() const
{
    return m_success_count >= m_target_success_count;
}

const QList<AppleModel*>& SaveAppleModel::activeApples() const
{
    return m_active_apples;
}

int SaveAppleModel::currentAppleFallSpeed() const
{
    return 80 + (m_speed_level - 1) * 20;
}

bool SaveAppleModel::isValidSpeedLevel(int speed_level) const
{
    return speed_level >= 1 && speed_level <= 10;
}

bool SaveAppleModel::isValidMaxAppleCount(int max_apple_count) const
{
    return max_apple_count >= 1 && max_apple_count <= 5;
}

bool SaveAppleModel::isValidTargetSuccessCount(int target_success_count) const
{
    return target_success_count > 0;
}

bool SaveAppleModel::isValidMaxMissCount(int max_miss_count) const
{
    return max_miss_count > 0;
}

void SaveAppleModel::updateActiveApples(int delta_ms)
{
    for (AppleModel* apple : m_active_apples)
    {
        if (apple == nullptr)
        {
            continue;
        }

        if (!apple->isActive())
        {
            continue;
        }

        apple->update(delta_ms);
    }
}

void SaveAppleModel::processMissedApples()
{
    QList<AppleModel*> missed_apples;

    for (AppleModel* apple : m_active_apples)
    {
        if (apple == nullptr)
        {
            continue;
        }

        if (!apple->isActive())
        {
            continue;
        }

        if (apple->y() >= m_fail_line_y)
        {
            missed_apples.append(apple);
        }
    }

    for (AppleModel* apple : missed_apples)
    {
        handleAppleMiss(apple);
    }
}

void SaveAppleModel::handleAppleHit(AppleModel* apple)
{
    if (apple == nullptr)
    {
        return;
    }

    const QChar apple_letter = apple->letter();

    m_success_count += 1;
    m_score += hitScoreValue();

    removeAppleInternal(apple);

    notifyAppleHit(apple_letter);
    notifyAppleRemoved(apple_letter);
    notifyScoreChanged();
}

void SaveAppleModel::handleAppleMiss(AppleModel* apple)
{
    if (apple == nullptr)
    {
        return;
    }

    const QChar apple_letter = apple->letter();

    m_miss_count += 1;
    m_score = std::max(0, m_score - missPenaltyValue());

    removeAppleInternal(apple);

    notifyAppleMiss(apple_letter);
    notifyAppleRemoved(apple_letter);
    notifyScoreChanged();

    if (m_miss_count >= m_max_miss_count)
    {
        notifyGameOver();
        m_game_state = GameState::End;
        notifyStateEvent(GameEventType::GameStateChanged);
    }
}

void SaveAppleModel::removeAppleInternal(AppleModel* apple)
{
    if (apple == nullptr)
    {
        return;
    }

    const int remove_index = m_active_apples.indexOf(apple);
    if (remove_index < 0)
    {
        return;
    }

    releaseLetter(apple->letter());
    m_active_apples.removeAt(remove_index);
    apple->setActive(false);
}

void SaveAppleModel::occupyLetter(QChar letter)
{
    m_used_letters.insert(letter.toUpper());
}

void SaveAppleModel::releaseLetter(QChar letter)
{
    m_used_letters.remove(letter.toUpper());
}

void SaveAppleModel::finishCurrentRound()
{
    m_game_state = GameState::End;
    notifyStateEvent(GameEventType::GameStateChanged);
    notifyGameOver();
    notifyLevelCompleted();
}

void SaveAppleModel::syncActiveAppleFallSpeed()
{
    const int fall_speed = currentAppleFallSpeed();

    for (AppleModel* apple : m_active_apples)
    {
        if (apple == nullptr)
        {
            continue;
        }

        apple->setFallSpeed(fall_speed);
    }
}

int SaveAppleModel::hitScoreValue() const
{
    return 10 + (m_speed_level - 1) * 2;
}

int SaveAppleModel::missPenaltyValue() const
{
    return 5;
}

void SaveAppleModel::notifyStateEvent(GameEventType event_type)
{
    GameEvent event;
    event.type = event_type;
    event.state = m_game_state;
    event.score = m_score;
    event.level = m_speed_level;
    event.value = 0;
    event.extra_value = 0;
    notifyObservers(event);
}

void SaveAppleModel::notifyScoreChanged()
{
    GameEvent event;
    event.type = GameEventType::ScoreChanged;
    event.state = m_game_state;
    event.value = m_score;
    event.extra_value = 0;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyAppleSpawned(QChar letter)
{
    GameEvent event;
    event.type = GameEventType::EntitySpawned;
    event.state = m_game_state;
    event.letter = letter;
    event.value = m_active_apples.size();   // 当前活动苹果数
    event.extra_value = 0;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyAppleRemoved(QChar letter)
{
    GameEvent event;
    event.type = GameEventType::EntityRemoved;
    event.state = m_game_state;
    event.letter = letter;
    event.value = m_active_apples.size();   // 移除后剩余活动苹果数
    event.extra_value = 0;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyAppleHit(QChar letter)
{
    GameEvent event;
    event.type = GameEventType::EntityHit;
    event.state = m_game_state;
    event.letter = letter;
    event.value = m_success_count;          // 当前成功数
    event.extra_value = m_miss_count;       // 当前漏失数
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyAppleMiss(QChar letter)
{
    GameEvent event;
    event.type = GameEventType::EntityMissed;
    event.state = m_game_state;
    event.letter = letter;
    event.value = m_miss_count;             // 当前漏失数
    event.extra_value = m_success_count;    // 当前成功数
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyLevelCompleted()
{
    GameEvent event;
    event.type = GameEventType::LevelCompleted;
    event.state = m_game_state;
    event.value = m_success_count;
    event.extra_value = m_target_success_count;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifyGameOver()
{
    GameEvent event;
    event.type = GameEventType::GameOver;
    event.state = m_game_state;
    event.value = m_miss_count;
    event.extra_value = m_max_miss_count;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}

void SaveAppleModel::notifySettingsChanged(SettingKey key, int value, int extra_value)
{
    GameEvent event;
    event.type = GameEventType::SettingsChanged;
    event.state = m_game_state;
    event.setting_key = key;
    event.value = value;
    event.extra_value = extra_value;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}


void SaveAppleModel::notifyInputRejected(QChar letter)
{
    GameEvent event;
    event.type = GameEventType::InputRejected;
    event.state = m_game_state;
    event.letter = letter;
    event.value = 0;
    event.extra_value = 0;
    event.score = m_score;
    event.level = m_speed_level;
    notifyObservers(event);
}
