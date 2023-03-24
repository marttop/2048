/*
** star-breaker
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(Rectangle rect) : _rect(rect)
{
}

Player::~Player()
{
}

void Player::draw() const
{
    DrawRectangleRec(_rect, GREEN);
}

Vector2 Player::getPosition() const
{
    return (Vector2){_rect.x, _rect.y};
}

EntityType Player::getEntityType() const
{
    return EntityType::Player;
}

void Player::setPosition(const Vector2& position)
{
    _rect.x = position.x;
    _rect.y = position.y;
}

bool Player::collidesWithBall(const Vector2& ballPosition, float ballRadius) const
{
    return CheckCollisionCircleRec(ballPosition, ballRadius, _rect);
}

void Player::update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities) {
    float speed = 1100.0f; // Adjust the paddle's speed as needed

    // Move paddle left
    if (IsKeyDown(KEY_LEFT)) {
        _rect.x -= speed * deltaTime;
    }
    // Move paddle right
    if (IsKeyDown(KEY_RIGHT)) {
        _rect.x += speed * deltaTime;
    }

    // Keep paddle inside the screen bounds
    if (_rect.x < 0) {
        _rect.x = 0;
    } else if (_rect.x + _rect.width > GetScreenWidth()) {
        _rect.x = GetScreenWidth() - _rect.width;
    }
}

Rectangle Player::getRect() const
{
    return _rect;
}
