/*
** 2048
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene() : _tileMap(4, std::vector<std::shared_ptr<Tile>>(4, nullptr)), _isEvent(true), _score(0)
{
    _gridWidth = GRID_RATIO * SCREEN_WIDTH;
    _gridHeight = GRID_RATIO * SCREEN_HEIGHT;
    _gridX = (SCREEN_WIDTH - _gridWidth) / 2;
    _gridY = (SCREEN_HEIGHT - _gridHeight) / 2 + GRID_PADDING_VERTICAL;
    _tileWidth = (_gridWidth - 5 * TILE_PADDING) / 4;
    _tileHeight = (_gridHeight - 5 * TILE_PADDING) / 4;
    TilePos gridPos;
    Vector2 pos = Vector2{_gridX + TILE_PADDING, _gridY + TILE_PADDING};
    gridPos.x = _gridX;
    gridPos.y = _gridY;

    // Populate placeholders
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            addEntity(std::make_shared<Tile>(Rectangle{pos.x, pos.y, _tileWidth, _tileHeight}, gridPos));
            gridPos.x += 1;
            pos.x += _tileWidth + TILE_PADDING;
        }
        pos.y += _tileHeight + TILE_PADDING;
        pos.x = _gridX + TILE_PADDING;
        gridPos.y += 1;
    }

    // Insert first two tiles
    putRandomTile();
    putRandomTile();
}

void GameScene::addEntity(std::shared_ptr<IEntity> entity)
{
    m_entities.push_back(entity);
}

void GameScene::removeEntity(std::shared_ptr<IEntity> entity)
{
    m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
}

void GameScene::moveTileLeft(int y, int x)
{
    int i = 0;
    for (i = x; i > 0; i--) {
        if (_tileMap[y][i - 1] != nullptr) {
            checkFusion(_tileMap[y][i], _tileMap[y][i - 1]);
            break;
        } else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = _tileMap[y][i];
            _tileMap[y][i] = _tileMap[y][i - 1];
            _tileMap[y][i - 1] = temp;
            temp->setMapPosition({i - 1, y});
            _tilesMoved += 1;
        }
    }
}

void GameScene::moveTileRight(int y, int x)
{
    int i = 0;
    int mapWidth = _tileMap[y].size();
    for (i = x; i < mapWidth - 1; i++) {
        if (_tileMap[y][i + 1] != nullptr) {
            checkFusion(_tileMap[y][i], _tileMap[y][i + 1]);
            break;
        } else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = _tileMap[y][i];
            _tileMap[y][i] = _tileMap[y][i + 1];
            _tileMap[y][i + 1] = temp;
            temp->setMapPosition({i + 1, y});
            _tilesMoved += 1;
        }
    }
}

void GameScene::moveTileUp(int y, int x)
{
    int i = 0;
    for (i = y; i > 0; i--) {
        if (_tileMap[i - 1][x] != nullptr) {
            checkFusion(_tileMap[i][x], _tileMap[i - 1][x]);
            break;
        } else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = _tileMap[i][x];
            _tileMap[i][x] = _tileMap[i - 1][x];
            _tileMap[i - 1][x] = temp;
            temp->setMapPosition({x, i - 1});
            _tilesMoved += 1;
        }
    }
}

void GameScene::moveTileDown(int y, int x)
{
    int i = 0;
    int mapHeight = _tileMap.size();
    for (i = y; i < mapHeight - 1; i++) {
        if (_tileMap[i + 1][x] != nullptr) {
            checkFusion(_tileMap[i][x], _tileMap[i + 1][x]);
            break;
        } else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = _tileMap[i][x];
            _tileMap[i][x] = _tileMap[i + 1][x];
            _tileMap[i + 1][x] = temp;
            temp->setMapPosition({x, i + 1});
            _tilesMoved += 1;
        }
    }
}

void GameScene::checkFusion(std::shared_ptr<Tile> moving, std::shared_ptr<Tile> obstacle)
{
    int movingValue = moving->getValue();
    int obstacleValue = obstacle->getValue();
    if (movingValue == obstacleValue) {
        int total = obstacleValue + movingValue;
        _score += total;
        _tilesMoved += 1;
        obstacle->setValue(total);
        removeEntity(moving);
        int x = moving->getMapPosition().x;
        int y = moving->getMapPosition().y;
        if (y >= 0 && y < _tileMap.size() && x >= 0 && x < _tileMap[y].size() && _tileMap[y][x] != nullptr) {
            _tileMap[y][x] = nullptr;
        }

        DEBUG("Fusion of : (y:{0},x:{1}) into -> (y:{2},x:{3})", moving->getMapPosition().y,
              moving->getMapPosition().x, obstacle->getMapPosition().y, obstacle->getMapPosition().x);
        DEBUG("Result of fusion : {0} + {1} = {2}", movingValue, obstacleValue, total);
        DEBUG("Current total score : {0}", _score);

        moving = nullptr;
    }
}

void GameScene::putRandomTile()
{
    TilePos randomPos = getRandomTilePos(true);
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(Rectangle{
                                                            _gridX + randomPos.x * (TILE_PADDING + _tileWidth) + TILE_PADDING,
                                                            _gridY + randomPos.y * (TILE_PADDING + _tileHeight) + TILE_PADDING,
                                                            _tileWidth,
                                                            _tileHeight},
                                                        randomPos, true);
    _tileMap[randomPos.y][randomPos.x] = tile;
    addEntity(tile);
}

void GameScene::putTile(TilePos pos)
{
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(Rectangle{
                                                            _gridX + pos.x * (TILE_PADDING + _tileWidth) + TILE_PADDING,
                                                            _gridY + pos.y * (TILE_PADDING + _tileHeight) + TILE_PADDING,
                                                            _tileWidth,
                                                            _tileHeight},
                                                        pos, true);
    _tileMap[pos.y][pos.x] = tile;
    addEntity(tile);
}

bool GameScene::areTilesSetteled()
{
    for (auto line : _tileMap) {
        for (auto e : line) {
            if (e && e->getDirection() != Direction::None) return false;
        }
    }
    return true;
}

void GameScene::resetKeyevents()
{
    float currentTime = 0.0f;
    static float previousTime = 0.0f;
    const float timeInterval = 0.2f;  // Reset the timer every 0.x seconds

    currentTime = GetTime();
    if (currentTime - previousTime >= timeInterval) {
        previousTime = currentTime;
        _isEvent = true;
    }
}

void GameScene::update(float deltaTime)
{
    if (_direction == Direction::Left || _direction == Direction::Right) {
        for (int y = 0; y < _tileMap.size(); y++) {
            int startX = (_direction == Direction::Left) ? 0 : _tileMap[y].size() - 1;
            int endX = (_direction == Direction::Left) ? _tileMap[y].size() : -1;
            int stepX = (_direction == Direction::Left) ? 1 : -1;

            for (int x = startX; x != endX; x += stepX) {
                if (_tileMap[y][x]) {
                    _tileMap[y][x]->setDirection(_direction);

                    if (_direction == Direction::Left) {
                        moveTileLeft(y, x);
                    } else if (_direction == Direction::Right) {
                        moveTileRight(y, x);
                    }
                }
            }
        }
    } else if (_direction == Direction::Up || _direction == Direction::Down) {
        for (int x = 0; x < _tileMap[0].size(); x++) {
            int startY = (_direction == Direction::Up) ? 0 : _tileMap.size() - 1;
            int endY = (_direction == Direction::Up) ? _tileMap.size() : -1;
            int stepY = (_direction == Direction::Up) ? 1 : -1;

            for (int y = startY; y != endY; y += stepY) {
                if (_tileMap[y][x]) {
                    _tileMap[y][x]->setDirection(_direction);

                    if (_direction == Direction::Up) {
                        moveTileUp(y, x);
                    } else if (_direction == Direction::Down) {
                        moveTileDown(y, x);
                    }
                }
            }
        }
    }
    for (const auto& entity : m_entities) {
        entity->update(deltaTime, m_entities);
    }
    _direction = Direction::None;
    bool areSettle = areTilesSetteled();
    if (_tilesMoved && areSettle) {
        _isEvent = true;
        putRandomTile();
        _tilesMoved = 0;
    } else if (!_tilesMoved && areSettle) {
        _isEvent = true;
    }
}

void GameScene::handleEvent()
{
    if (_isEvent) {
        if (IsKeyDown(KEY_UP)) {
            _direction = Direction::Up;
            _isEvent = false;
        } else if (IsKeyDown(KEY_DOWN)) {
            _direction = Direction::Down;
            _isEvent = false;
        } else if (IsKeyDown(KEY_LEFT)) {
            _direction = Direction::Left;
            _isEvent = false;
        } else if (IsKeyDown(KEY_RIGHT)) {
            _direction = Direction::Right;
            _isEvent = false;
        }
    }
}

void GameScene::draw() const
{
    ClearBackground(Color{250, 248, 240, 255});
    DrawRectangleRounded(
        (Rectangle){_gridX, _gridY, _gridWidth, _gridHeight},
        0.02,  // corner radius
        1,
        Color{185, 173, 161, 255});
    for (auto entity : m_entities) {
        entity->draw();
    }
}

TilePos GameScene::getRandomTilePos(bool isMapped) const
{
    TilePos pos;
    pos.x = GetRandomValue(0, 3);
    pos.y = GetRandomValue(0, 3);
    if (!isMapped) return pos;

    // Create a vector of all null elements in the tile map
    std::vector<TilePos> nonNullPositions;
    for (int y = 0; y < _tileMap.size(); ++y) {
        for (int x = 0; x < _tileMap[y].size(); ++x) {
            if (!_tileMap[y][x]) {
                nonNullPositions.push_back({x, y});
            }
        }
    }
    int index = GetRandomValue(0, nonNullPositions.size() - 1);
    return nonNullPositions[index];
}
