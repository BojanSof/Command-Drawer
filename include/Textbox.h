#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <Common.h>
#include <SFML/Graphics.hpp>
#include <string>


class TextBox : public sf::Transformable, public sf::Drawable
{
    public:
        TextBox();
        TextBox(uint maxSize, uint charSize);
        ~TextBox();

        bool contains(sf::Vector2f point) const;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void handleInput(sf::Event event);
        const std::string getText() const;
        void setFocus(bool focus);
        void setPosition(float x, float y);
        void clear();

    private:
        sf::RectangleShape m_rect;
        sf::Text m_renderText;
        sf::Font m_font;
        std::string m_text;
        uint m_size;
        uint m_charSize;
        bool m_focus;
};

#endif //TEXTBOX_H