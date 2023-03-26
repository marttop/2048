/*
** star-breaker
** File description:
** Tile
*/

#include "Tile.hpp"

std::unordered_map<std::string, Color> tileColors = {
    {"2", {238, 228, 218, 255}},
    {"4", {237, 224, 200, 255}},
    {"8", {242, 177, 121, 255}},
    {"16", {245, 149, 99, 255}},
    {"32", {246, 124, 95, 255}},
    {"64", {246, 94, 59, 255}},
    {"128", {237, 207, 114, 255}},
    {"256", {237, 204, 97, 255}},
    {"512", {237, 200, 80, 255}},
    {"1024", {237, 197, 63, 255}},
    {"2048", {237, 194, 46, 255}}
};

Tile::Tile(Rectangle rect, TilePos mapPosition, bool isActive) : _rect(rect),
                                                                 _mapPosition(mapPosition),
                                                                 _color(Color{238, 228, 218, 255}),
                                                                 _value(2),
                                                                 _direction(Direction::None),
                                                                 _isActive(isActive)
{
    if (!isActive) _color = Color{202, 193, 181, 255};
    if (isActive) {
        int num = GetRandomValue(0, 1);
        _value = num ? 2 : 4;
        _color = tileColors[std::to_string(_value)];
    }
    _font = LoadFont("/Users/martonszuts/Code/C++/RayLib/star-breaker/fonts/ClearSans-Bold.ttf");
    _fontSize = std::min(_rect.width / 2, _rect.height / 2);
    _font.baseSize = _fontSize;
}

Tile::~Tile()
{
    UnloadFont(_font);
}

void Tile::draw() const
{
    DrawRectangleRounded(
        (Rectangle){_rect.x, _rect.y, _rect.width, _rect.height},
        0.02,  // corner radius
        1,
        _color
    );

    if (_isActive) {

        // Draw tile value centered in the tile
        Vector2 textMeasure = MeasureTextEx(_font, std::to_string(_value).c_str(), _fontSize, 0);
        Vector2 textPos = {
            _rect.x + _rect.width / 2 - textMeasure.x / 2,
            _rect.y + _rect.height / 2 - textMeasure.y / 2 + TILE_PADDING};
        DrawTextEx(_font, std::to_string(_value).c_str(), textPos, _fontSize, 0, DARKGRAY);
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
    (void)deltaTime;
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

void Tile::setMapPosition(TilePos pos)
{
    _mapPosition = pos;
    const float tileSize = _rect.width;
    const float gridSize = 4 * (_rect.width + TILE_PADDING) + TILE_PADDING;

    if (_direction == Direction::Left || _direction == Direction::Right) {
        _rect.x = ((SCREEN_WIDTH - gridSize) / 2) + pos.x * (TILE_PADDING + tileSize) + TILE_PADDING;
    }
    else if (_direction == Direction::Up || _direction == Direction::Down) {
        _rect.y = ((SCREEN_HEIGHT - gridSize) / 2) + pos.y * (TILE_PADDING + tileSize) + TILE_PADDING + GRID_PADDING_VERTICAL;
    }
}
