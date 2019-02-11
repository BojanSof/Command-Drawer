#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <Common.h>
#include <SFML/Graphics.hpp>
#include <string>


class TextBox : public sf::Transformable, public sf::Drawable
{
    public:
        TextBox(uint maxSize);
        ~TextBox();

        void handleInput(sf::Event event);
        bool contains(sf::Vector2f point) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        const std::string getText() const;
        void setFocus(bool focus);
        void setPosition(float x, float y);
        void clear();

    private:
        uint m_size;
        bool m_focus;
        sf::Font m_font;
        std::string m_text;
        sf::Text m_renderText;
        sf::RectangleShape m_rect;
};

#endif //TEXTBOX_H