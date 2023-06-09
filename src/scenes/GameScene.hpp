// GameScene.hpp

#include "IScene.hpp"
#include "Tile.hpp"

class GameScene : public IScene {
public:
    // Constructors, destructors and other member functions can be added here

    GameScene();
    ~GameScene() = default;

    void addEntity(std::shared_ptr<IEntity> entity) override;
    void removeEntity(std::shared_ptr<IEntity> entity) override;
    void update(float deltaTime) override;
    void handleEvent() override;
    void draw() const override;

private:
    TilePos getRandomTilePos(bool isMapped) const;
    void moveTileLeft(int y, int x);
    void moveTileRight(int y, int x);
    void moveTileUp(int y, int x);
    void moveTileDown(int y, int x);

    void checkFusion(std::shared_ptr<Tile> moving, std::shared_ptr<Tile> obstacle);
    void putRandomTile();
    void putTile(TilePos pos);
    bool areTilesSetteled();
    void resetKeyevents();

    // CORE
    std::vector<std::shared_ptr<IEntity>> m_entities;
    std::vector<std::vector<std::shared_ptr<Tile>>> _tileMap;
    bool _isEvent;
    int _tilesMoved;
    Direction _direction;
    float _gridWidth;
    float _gridHeight;
    float _tileWidth;
    float _tileHeight;
    float _gridX;
    float _gridY;

    // GAMEPLAY
    int _score;
};
