/*
** star-breaker
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "IEntity.hpp"

class Player : public IEntity {
    public:
        Player(Rectangle rect);
        ~Player();

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

#endif /* !PLAYER_HPP_ */
