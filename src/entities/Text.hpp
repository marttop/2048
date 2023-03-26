// Text.hpp
#ifndef TEXT_HPP_
#define TEXT_HPP_

#include "IEntity.hpp"

class Text : public IEntity
{
   public:
    Text(const std::string& text, const Vector2& position, const Color& textColor = DARKGRAY);

    virtual void draw() const override;
    virtual Vector2 getPosition() const override;
    virtual EntityType getEntityType() const override;
    virtual void setPosition(const Vector2& position) override;
    virtual void update(float deltaTime, std::vector<std::shared_ptr<IEntity>>& m_entities) override;

    std::string getText() const;
    void setText(const std::string& text);

   private:
    std::string _text;
    Vector2 _position;
    Color _textColor;
};

#endif /* !TEXT_HPP_ */