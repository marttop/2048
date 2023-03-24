/*
** star-breaker
** File description:
** Ball
*/

#include "Ball.hpp"

Ball::Ball(Vector2 pos, float radius, Vector2 speed) : _position(pos), _radius(radius), _speed(speed)
{
}

Ball::~Ball()
{
}

void Ball::draw() const
{
    DrawCircleV(_position, _radius, BLACK);
}

Vector2 Ball::getPosition() const
{
    return _position;
}

EntityType Ball::getEntityType() const
{
    return EntityType::Ball;
}

void Ball::setPosition(const Vector2& position)
{
    _position = position;
}

bool Ball::collidesWithBall(const Vector2& ballPosition, float ballRadius) const
{
    return false;
}

void Ball::update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities)
{
    // Bounce from window borders
    if (_position.x <= _radius || _position.x >= SCREEN_WIDTH - _radius) {
        _speed.x *= -1;
    }
    if (_position.y <= _radius || _position.y >= SCREEN_HEIGHT - _radius) {
        _speed.y *= -1;
    }

    // Check for collisions with other entities in the game
    for (const auto& entity : m_entities) {
        EntityType entityType = entity->getEntityType();

        if (entityType == EntityType::Brick || entityType == EntityType::Player) {
            if (entity->collidesWithBall(_position, _radius)) {
                // Determine which side of the rectangle the ball hit
                float prevX = _position.x - _speed.x * deltaTime;
                float prevY = _position.y - _speed.y * deltaTime;

                // Assuming the entity has a getRect() function only for the ones that have a rect (e.g., Brick and Player)
                Rectangle rect = entity->getRect();

                Vector2 normal;
                if (entityType == EntityType::Player) {
                    // For the paddle, calculate the normal based on the relative horizontal position of the ball to the center of the paddle
                    float relativeIntersectX = (rect.x + rect.width / 2) - _position.x;
                    float maxBounceAngle = 75.0f; // Adjust this value to control the maximum bounce angle
                    float bounceAngle = (relativeIntersectX / (rect.width / 2)) * maxBounceAngle;
                    normal.x = -sinf(bounceAngle * DEG2RAD);
                    normal.y = -cosf(bounceAngle * DEG2RAD);
                } else {
                    // For the bricks, determine the normal based on the side the ball hit
                    if (prevX - _radius < rect.x + rect.width && prevX + _radius > rect.x) {
                        normal = {0, _speed.y < 0 ? 1.f : -1.f};
                    } else {
                        normal = {_speed.x < 0 ? 1.f : -1.f, 0};
                    }
                }

                normal = Vector2Normalize(normal);

                // Reflect the ball's velocity based on the collision normal
                float dot = 2 * (Vector2DotProduct(_speed, normal));
                _speed.x -= dot * normal.x;
                _speed.y -= dot * normal.y;
            }
        }
    }

    _position.x += _speed.x * deltaTime;
    _position.y += _speed.y * deltaTime;
}



