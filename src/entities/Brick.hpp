/*
** star-breaker
** File description:
** Brick
*/

#ifndef BRICK_HPP_
#define BRICK_HPP_

#include "IEntity.hpp"

class Brick : public IEntity {
    public:
        Brick(Rectangle rect);
        ~Brick();

        void draw() const override;
        Vector2 getPosition() const override;
        EntityType getEntityType() const override;
        void setPosition(const Vector2& position) override;
        bool collidesWithBall(const Vector2& ballPosition, float ballRadius) const override;
        void update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities) override;
        Rectangle getRect() const override;

    protected:
    private:
        Rectangle _rect;
};

#endif /* !BRICK_HPP_ */
