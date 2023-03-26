/*
** EPITECH PROJECT, 2023
** star-breaker
** File description:
** GameScene
*/

#include "GameScene.hpp"

GameScene::GameScene() : tileMap(4, std::vector<std::shared_ptr<Tile>>(4, nullptr))
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
    TilePos randomPos = getRandomTilePos(false);

    std::shared_ptr<Tile> tile = std::make_shared<Tile>(Rectangle{
                                                            _gridX + randomPos.x * (TILE_PADDING + _tileWidth) + TILE_PADDING,
                                                            _gridY + randomPos.y * (TILE_PADDING + _tileHeight) + TILE_PADDING,
                                                            _tileWidth,
                                                            _tileHeight},
                                                        randomPos, true);

    tileMap[randomPos.y][randomPos.x] = tile;
    addEntity(tile);

    randomPos = getRandomTilePos(true);
    tile = std::make_shared<Tile>(Rectangle{
                                      _gridX + randomPos.x * (TILE_PADDING + _tileWidth) + TILE_PADDING,
                                      _gridY + randomPos.y * (TILE_PADDING + _tileHeight) + TILE_PADDING,
                                      _tileWidth,
                                      _tileHeight},
                                  randomPos, true);
    tileMap[randomPos.y][randomPos.x] = tile;
    addEntity(tile);
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
        if (tileMap[y][i - 1] != nullptr)
            break;
        else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = tileMap[y][i];
            tileMap[y][i] = tileMap[y][i - 1];
            tileMap[y][i - 1] = temp;
        }
    }
    tileMap[y][i]->setMapPosition({i, y});
}

void GameScene::moveTileRight(int y, int x)
{
    int i = 0;
    int mapWidth = tileMap[y].size();
    for (i = x; i < mapWidth - 1; i++) {
        if (tileMap[y][i + 1] != nullptr)
            break;
        else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = tileMap[y][i];
            tileMap[y][i] = tileMap[y][i + 1];
            tileMap[y][i + 1] = temp;
        }
    }
    tileMap[y][i]->setMapPosition({i, y});
}

void GameScene::moveTileUp(int y, int x)
{
    int i = 0;
    for (i = y; i > 0; i--) {
        if (tileMap[i - 1][x] != nullptr)
            break;
        else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = tileMap[i][x];
            tileMap[i][x] = tileMap[i - 1][x];
            tileMap[i - 1][x] = temp;
        }
    }
    tileMap[i][x]->setMapPosition({x, i});
}

void GameScene::moveTileDown(int y, int x)
{
    int i = 0;
    int mapHeight = tileMap.size();
    for (i = y; i < mapHeight - 1; i++) {
        if (tileMap[i + 1][x] != nullptr)
            break;
        else {
            // Swap the tiles
            std::shared_ptr<Tile> temp = tileMap[i][x];
            tileMap[i][x] = tileMap[i + 1][x];
            tileMap[i + 1][x] = temp;
        }
    }
    tileMap[i][x]->setMapPosition({x, i});
}


void GameScene::update(float deltaTime)
{
    if (_direction == Direction::Left || _direction == Direction::Right) {
        for (int y = 0; y < tileMap.size(); y++) {
            int startX = (_direction == Direction::Left) ? 0 : tileMap[y].size() - 1;
            int endX = (_direction == Direction::Left) ? tileMap[y].size() : -1;
            int stepX = (_direction == Direction::Left) ? 1 : -1;

            for (int x = startX; x != endX; x += stepX) {
                if (tileMap[y][x]) {
                    tileMap[y][x]->setDirection(_direction);

                    if (_direction == Direction::Left) {
                        moveTileLeft(y, x);
                    } else if (_direction == Direction::Right) {
                        moveTileRight(y, x);
                    }
                }
            }
        }
    } else if (_direction == Direction::Up || _direction == Direction::Down) {
        for (int x = 0; x < tileMap[0].size(); x++) {
            int startY = (_direction == Direction::Up) ? 0 : tileMap.size() - 1;
            int endY = (_direction == Direction::Up) ? tileMap.size() : -1;
            int stepY = (_direction == Direction::Up) ? 1 : -1;

            for (int y = startY; y != endY; y += stepY) {
                if (tileMap[y][x]) {
                    tileMap[y][x]->setDirection(_direction);

                    if (_direction == Direction::Up) {
                        moveTileUp(y, x);
                    } else if (_direction == Direction::Down){
                        moveTileDown(y, x);
                    }
                }
            }
        }
    }
    for (const auto& entity : m_entities) {
        entity->update(deltaTime, m_entities);
    }
}

void GameScene::handleEvent()
{
    if (IsKeyDown(KEY_UP)) {
        _direction = Direction::Up;
    } else if (IsKeyDown(KEY_DOWN)) {
        _direction = Direction::Down;
    } else if (IsKeyDown(KEY_LEFT)) {
        _direction = Direction::Left;
    } else if (IsKeyDown(KEY_RIGHT)) {
        _direction = Direction::Right;
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
    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            if (!tileMap[y][x]) {
                nonNullPositions.push_back({ x, y });
            }
        }
    }
    int index = GetRandomValue(0, nonNullPositions.size() - 1);
    return nonNullPositions[index];
}
