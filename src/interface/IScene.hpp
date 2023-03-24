// IScene.hpp

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include "IEntity.hpp"

class IScene {
public:
    /**
     * @brief Default destructor.
     */
    virtual ~IScene() = default;

    /**
     * @brief Adds an entity to the scene.
     * @param entity The entity to add to the scene.
     */
    virtual void addEntity(std::shared_ptr<IEntity> entity) = 0;

    /**
     * @brief Removes an entity from the scene.
     * @param entity The entity to remove from the scene.
     */
    virtual void removeEntity(std::shared_ptr<IEntity> entity) = 0;

    /**
     * @brief Updates all entities in the scene.
     * @param deltaTime The time passed since the last update.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Draws all entities in the scene.
     */
    virtual void draw() const = 0;
};

#endif /* !ISCENE_HPP_ */
