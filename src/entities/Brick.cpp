/*
** star-breaker
** File description:
** Brick
*/

#include "Brick.hpp"

Brick::Brick(Rectangle rect) : _rect(rect)
{
}

Brick::~Brick()
{
}

void Brick::draw() const
{
    DrawRectangleRec(_rect, GREEN);
}

Vector2 Brick::getPosition() const
{
    return (Vector2){_rect.x, _rect.y};
}

EntityType Brick::getEntityType() const
{
    return EntityType::Brick;
}

void Brick::setPosition(const Vector2& position)
{
    _rect.x = position.x;
    _rect.y = position.y;
}

bool Brick::collidesWithBall(const Vector2& ballPosition, float ballRadius) const
{
    return CheckCollisionCircleRec(ballPosition, ballRadius, _rect);
}

void Brick::update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities)
{
    // Not used
    (void)deltaTime;
    (void)m_entities;
}

Rectangle Brick::getRect() const
{
    return _rect;
}
