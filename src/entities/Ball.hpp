/*
** EPITECH PROJECT, 2023
** star-breaker
** File description:
** Ball
*/

#ifndef BALL_HPP_
#define BALL_HPP_

#include "IEntity.hpp"

class Ball : public IEntity {
    public:
        Ball(Vector2 pos, float radius, Vector2 speed = {600.f, 900.f});
        ~Ball();

        void draw() const override;
        Vector2 getPosition() const override;
        EntityType getEntityType() const override;
        void setPosition(const Vector2& position) override;
        bool collidesWithBall(const Vector2& ballPosition, float ballRadius) const override;
        void update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities) override;
    protected:
    private:
        Vector2 _position;
        Vector2 _speed;
        float _radius;
};

#endif /* !BALL_HPP_ */
