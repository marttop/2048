/*
** 2048
** File description:
** Ball
*/

#ifndef BALL_HPP_
#define BALL_HPP_

#include "IEntity.hpp"

enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
};

typedef struct TilePos {
    int x;
    int y;
} TilePos;

class Tile : public IEntity {
    public:
        Tile(const Rectangle &rect, const TilePos &mapPosition, const bool isActive = false);
        ~Tile();

        void draw() const override;
        Vector2 getPosition() const override;
        Rectangle getRect() const override;
        EntityType getEntityType() const override;
        void setPosition(const Vector2& position) override;
        void update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities) override;

        bool isActive() const;
        int getValue() const;
        Direction getDirection() const;
        TilePos getMapPosition() const;
        void setValue(int value);
        void setDirection(Direction direction);
        void setMapPosition(TilePos pos);
    protected:
    private:
        Rectangle _rect;
        TilePos _mapPosition;
        Color _color;
        int _value;
        Direction _direction;
        bool _isActive;
        Font _font;
        int _fontSize;
};

extern std::unordered_map<std::string, Color> tileColors;

#endif /* !BALL_HPP_ */
