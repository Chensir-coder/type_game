/* ------------------------------------------------------------------
 // 文件名     : saveapple_controller.cpp
 // 创建者     : 3263297739@qq.com
 // 创建时间   : 2026-04-13
 // 功能描述   : 拯救苹果游戏主控制器实现
------------------------------------------------------------------ */

#include "saveapple_controller.h"

#include <QRandomGenerator>
#include <QString>

#include "saveapple/model/saveapple_model.h"
#include "saveapple/model/apple_model.h"
#include "saveapple/factory/apple_factory.h"

SaveAppleController::SaveAppleController(SaveAppleModel* model, AppleFactory* apple_factory)
    : m_model(model)
    , m_apple_factory(apple_factory)
{
}

void SaveAppleController::initialize()
{
    if (m_model == nullptr)
    {
        return;
    }

    m_model->initialize();
    resetSpawnTimer();
}

void SaveAppleController::startGame()
{
    if (m_model == nullptr)
    {
        return;
    }

    m_model->startGame();
    resetSpawnTimer();
}

void SaveAppleController::pauseGame()
{
    if (m_model == nullptr)
    {
        return;
    }

    m_model->pauseGame();
}

void SaveAppleController::resumeGame()
{
    if (m_model == nullptr)
    {
        return;
    }

    m_model->resumeGame();
}

void SaveAppleController::stopGame()
{
    if (m_model == nullptr)
    {
        return;
    }

    const QList<AppleModel*> previous_apples = m_model->activeApples();

    m_model->stopGame();
    recycleInactiveApples(previous_apples);
    resetSpawnTimer();
}

void SaveAppleController::restartGame()
{
    if (m_model == nullptr)
    {
        return;
    }

    const QList<AppleModel*> previous_apples = m_model->activeApples();

    m_model->resetModel();
    recycleInactiveApples(previous_apples);

    m_model->startGame();
    resetSpawnTimer();
}

void SaveAppleController::update(int delta_ms)
{
    if (m_model == nullptr || m_apple_factory == nullptr)
    {
        return;
    }

    if (delta_ms <= 0)
    {
        return;
    }

    if (m_model->gameState() != GameState::Playing)
    {
        return;
    }

    m_elapsed_spawn_ms += delta_ms;
    if (m_elapsed_spawn_ms >= m_spawn_interval_ms)
    {
        trySpawnApple();
        m_elapsed_spawn_ms = 0;
    }

    const QList<AppleModel*> previous_apples = m_model->activeApples();

    m_model->update(delta_ms);

    recycleInactiveApples(previous_apples);
}

bool SaveAppleController::handleLetterInput(QChar input_letter)
{
    if (m_model == nullptr || m_apple_factory == nullptr)
    {
        return false;
    }

    const QList<AppleModel*> previous_apples = m_model->activeApples();

    const bool is_hit = m_model->hitAppleByLetter(input_letter);
    if (!is_hit)
    {
        return false;
    }

    recycleInactiveApples(previous_apples);
    return true;
}

void SaveAppleController::setSceneWidth(int scene_width)
{
    if (scene_width <= 0)
    {
        return;
    }

    m_scene_width = scene_width;
}

int SaveAppleController::sceneWidth() const
{
    return m_scene_width;
}

void SaveAppleController::setSpawnY(int spawn_y)
{
    m_spawn_y = spawn_y;
}

int SaveAppleController::spawnY() const
{
    return m_spawn_y;
}

void SaveAppleController::setSpawnIntervalMs(int spawn_interval_ms)
{
    if (spawn_interval_ms <= 0)
    {
        return;
    }

    m_spawn_interval_ms = spawn_interval_ms;
}

int SaveAppleController::spawnIntervalMs() const
{
    return m_spawn_interval_ms;
}

void SaveAppleController::resetSpawnTimer()
{
    m_elapsed_spawn_ms = 0;
}

void SaveAppleController::trySpawnApple()
{
    if (m_model == nullptr || m_apple_factory == nullptr)
    {
        return;
    }

    if (!m_model->canSpawnApple())
    {
        return;
    }

    const QChar spawn_letter = generateAvailableLetter();
    if (spawn_letter.isNull())
    {
        return;
    }

    AppleModel* apple = m_apple_factory->create();
    if (apple == nullptr)
    {
        return;
    }

    apple->setLetter(spawn_letter);
    apple->setPosition(generateSpawnX(), m_spawn_y);
    apple->setFallSpeed(m_model->currentAppleFallSpeed());

    if (!m_model->registerApple(apple))
    {
        m_apple_factory->recycle(apple);
    }
}

QChar SaveAppleController::generateAvailableLetter() const
{
    if (m_model == nullptr)
    {
        return QChar();
    }

    QString available_letters;
    for (QChar letter = QChar('A'); letter <= QChar('Z'); letter = QChar(letter.unicode() + 1))
    {
        if (m_model->isLetterAvailable(letter))
        {
            available_letters.append(letter);
        }
    }

    if (available_letters.isEmpty())
    {
        return QChar();
    }

    const int index = QRandomGenerator::global()->bounded(available_letters.size());
    return available_letters.at(index);
}

int SaveAppleController::generateSpawnX() const
{
    const int min_x = 20;
    const int max_x = (m_scene_width > 40) ? (m_scene_width - 20) : 20;

    if (max_x <= min_x)
    {
        return min_x;
    }

    return QRandomGenerator::global()->bounded(min_x, max_x);
}

void SaveAppleController::recycleInactiveApples(const QList<AppleModel*>& previous_apples)
{
    if (m_model == nullptr || m_apple_factory == nullptr)
    {
        return;
    }

    const QList<AppleModel*> current_apples = m_model->activeApples();

    for (AppleModel* apple : previous_apples)
    {
        if (apple == nullptr)
        {
            continue;
        }

        if (!containsApple(current_apples, apple))
        {
            m_apple_factory->recycle(apple);
        }
    }
}

bool SaveAppleController::containsApple(const QList<AppleModel*>& apples, AppleModel* target) const
{
    for (AppleModel* apple : apples)
    {
        if (apple == target)
        {
            return true;
        }
    }

    return false;
}
