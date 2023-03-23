/**
 * @file IEntity.hpp
 * @brief This file declares the IEntity interface.
 */

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include "raylib.h"

/**
 * @interface IEntity
 * @brief An interface for game entities.
 */
class IEntity {
public:
    /**
     * @brief Default destructor.
     */
    virtual ~IEntity() = default;

    /**
     * @brief Draws the entity on the screen.
     */
    virtual void draw() const = 0;

    /**
     * @brief Gets the entity's position as a Vector2.
     * @return The entity's position as a Vector2.
     */
    virtual Vector2 getPosition() const = 0;

    /**
     * @brief Sets the entity's position with a Vector2.
     * @param position The position to set the entity to.
     */
    virtual void setPosition(const Vector2& position) = 0;

    /**
     * @brief Updates the entity.
     * @param deltaTime The time passed since the last update.
     */
    virtual void update(float deltaTime) = 0;
};

#endif /* !IENTITY_HPP_ */
