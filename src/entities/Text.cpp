// Text.cpp
#include "Text.hpp"

Text::Text(const std::string& text, const Vector2& position, const Color& textColor)
    : _text(text), _position(position), _textColor(textColor)
{
}

void Text::draw() const
{
    DrawText(_text.c_str(), static_cast<int>(_position.x), static_cast<int>(_position.y), 20, _textColor);
}

Vector2 Text::getPosition() const
{
    return _position;
}

EntityType Text::getEntityType() const
{
    return EntityType::Text;
}

void Text::setPosition(const Vector2& position)
{
    _position = position;
}

void Text::update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities)
{
    // This implementation does not require any updates.
}

std::string Text::getText() const
{
    return _text;
}

void Text::setText(const std::string& text)
{
    _text = text;
}