/*
** 2048
** File description:
** Tile
*/

#include "Tile.hpp"

std::unordered_map<std::string, Color> tileColors = {
    {"2", {238, 228, 218, 255}},
    {"4", {237, 224, 200, 255}},
    {"8", {232, 180, 129, 255}},
    {"16", {232, 153, 108, 255}},
    {"32", {229, 120, 103, 255}},
    {"64", {227, 104, 71, 255}},
    {"128", {232, 208, 126, 255}},
    {"256", {231, 205, 115, 255}},
    {"512", {230, 201, 101, 255}},
    {"1024", {230, 198, 89, 255}},
    {"2048", {230, 195, 79, 255}}};

Tile::Tile(const Rectangle &rect, const TilePos &mapPosition, const bool isActive)
    : _rect(rect), _mapPosition(mapPosition), _color(Color{238, 228, 218, 255}), _value(2), _direction(Direction::None), _isActive(isActive)
{
    if (!isActive) _color = Color{202, 193, 181, 255};
    if (isActive) {
        int num = GetRandomValue(0, 1);
        _value = num ? 2 : 4;
        _color = tileColors[std::to_string(_value)];
    }
    _font = LoadFont("/Users/martonszuts/Code/C++/RayLib/2048/fonts/ClearSans-Bold.ttf");
    _fontSize = std::min(_rect.width / 2, _rect.height / 2);
    _font.baseSize = _fontSize;
    _targetPosition = Vector2{rect.x, rect.y};
}

Tile::~Tile()
{
    UnloadFont(_font);
}

void Tile::draw() const
{
    DrawRectangleRounded(
        (Rectangle){_rect.x, _rect.y, _rect.width, _rect.height},
        0.04,  // corner radius
        1,
        _color);

    if (_isActive) {
        // Draw tile value centered in the tile
        Vector2 textMeasure = MeasureTextEx(_font, std::to_string(_value).c_str(), _fontSize, 0);
        Vector2 textPos = {
            _rect.x + _rect.width / 2 - textMeasure.x / 2,
            _rect.y + _rect.height / 2 - textMeasure.y / 2 + TILE_PADDING};
        DrawTextEx(_font, std::to_string(_value).c_str(), textPos, _fontSize, 0, _value == 2 || _value == 4 ? DARKGRAY : WHITE);
    }
}

Vector2 Tile::getPosition() const
{
    return Vector2{_rect.x, _rect.y};
}

Rectangle Tile::getRect() const
{
    return _rect;
}

EntityType Tile::getEntityType() const
{
    if (_isActive) return EntityType::PlaceholderTile;
    return EntityType::Tile;
}

void Tile::setPosition(const Vector2& position)
{
    _rect.x = position.x;
    _rect.y = position.y;
}

void Tile::update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities)
{
    (void)m_entities;

    if (_direction != Direction::None) {
        if (_direction == Direction::Left || _direction == Direction::Right) {
            float distanceX = _targetPosition.x - _rect.x;
            float moveX = MOVE_SPEED * deltaTime * (_direction == Direction::Right ? 1 : -1);

            if (fabs(moveX) >= fabs(distanceX)) {
                _rect.x = _targetPosition.x;
                _direction = Direction::None;
            } else {
                _rect.x += moveX;
            }
        } else if (_direction == Direction::Up || _direction == Direction::Down) {
            float distanceY = _targetPosition.y - _rect.y;
            float moveY = MOVE_SPEED * deltaTime * (_direction == Direction::Down ? 1 : -1);

            if (fabs(moveY) >= fabs(distanceY)) {
                _rect.y = _targetPosition.y;
                _direction = Direction::None;
            } else {
                _rect.y += moveY;
            }
        }
    }
}


bool Tile::isActive() const
{
    return _isActive;
}

int Tile::getValue() const
{
    return _value;
}

Direction Tile::getDirection() const
{
    return _direction;
}

void Tile::setDirection(Direction direction)
{
    _direction = direction;
}

TilePos Tile::getMapPosition() const
{
    return _mapPosition;
}

void Tile::setValue(int value)
{
    _value = value;
    _color = tileColors[std::to_string(_value)];
}

void Tile::setMapPosition(TilePos pos)
{
    _mapPosition = pos;
    const float tileSize = _rect.width;
    const float gridSize = 4 * (_rect.width + TILE_PADDING) + TILE_PADDING;
    const float paddingHorizontal = (_direction == Direction::Left || _direction == Direction::Right) ? TILE_PADDING : 0;
    const float paddingVertical = (_direction == Direction::Up || _direction == Direction::Down) ? TILE_PADDING : 0;

    _targetPosition.x = ((SCREEN_WIDTH - gridSize) / 2) + pos.x * (TILE_PADDING + tileSize) + TILE_PADDING;
    _targetPosition.y = ((SCREEN_HEIGHT - gridSize) / 2) + pos.y * (TILE_PADDING + tileSize) + TILE_PADDING + GRID_PADDING_VERTICAL;
}


