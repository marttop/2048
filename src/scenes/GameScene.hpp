// GameScene.hpp

#include "IScene.hpp"
#include "Brick.hpp"
#include "Ball.hpp"
#include "Player.hpp"

class GameScene : public IScene {
public:
    // Constructors, destructors and other member functions can be added here

    GameScene();
    ~GameScene() = default;
    /**
     * @brief Adds an entity to the scene.
     * @param entity The entity to add to the scene.
     */
    void addEntity(std::shared_ptr<IEntity> entity) override;

    /**
     * @brief Removes an entity from the scene.
     * @param entity The entity to remove from the scene.
     */
    void removeEntity(std::shared_ptr<IEntity> entity) override;

    /**
     * @brief Updates all entities in the scene.
     * @param deltaTime The time passed since the last update.
     */
    void update(float deltaTime) override;

    /**
     * @brief Draws all entities in the scene.
     */
    void draw() const override;

private:
    std::vector<std::shared_ptr<IEntity>> m_entities;
};
