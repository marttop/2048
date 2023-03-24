/*
** EPITECH PROJECT, 2023
** star-breaker
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene()
{
    // Paddle dimensions
    float paddleWidth = 200.0f;
    float paddleHeight = 20.0f;

    // Calculate initial paddle position
    Vector2 paddlePosition = {
        (SCREEN_WIDTH - paddleWidth) / 2.0f,  // Center the paddle horizontally
        SCREEN_HEIGHT - paddleHeight - 40.0f  // Place the paddle near the bottom, 10 pixels from the edge
    };

    Rectangle paddleRect = {paddlePosition.x, paddlePosition.y, paddleWidth, paddleHeight};
    std::shared_ptr<IEntity> paddle = std::make_shared<Player>(paddleRect);
    addEntity(paddle);

    addEntity(std::make_shared<Brick>(Rectangle{50, 50, 100, 30}));
    addEntity(std::make_shared<Brick>(Rectangle{200, 50, 150, 30}));
    addEntity(std::make_shared<Brick>(Rectangle{400, 50, 80, 40}));
    addEntity(std::make_shared<Brick>(Rectangle{50, 150, 100, 50}));
    addEntity(std::make_shared<Brick>(Rectangle{200, 150, 150, 20}));
    addEntity(std::make_shared<Brick>(Rectangle{400, 150, 80, 30}));

    addEntity(std::make_shared<Ball>(Vector2{400, 300}, 10.0f, Vector2{400.0f, 500.0f}));
}

void GameScene::addEntity(std::shared_ptr<IEntity> entity)
{
    m_entities.push_back(entity);
}

void GameScene::removeEntity(std::shared_ptr<IEntity> entity)
{
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

void GameScene::update(float deltaTime)
{
    for (auto entity : m_entities) {
        entity->update(deltaTime, m_entities);
    }
}

void GameScene::draw() const
{
    ClearBackground(DARKGRAY);
    for (auto entity : m_entities) {
        entity->draw();
    }
}
