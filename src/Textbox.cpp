#include <Textbox.h>

TextBox::TextBox(uint maxSize) :    m_size(maxSize),
                                    m_focus(false),
                                    m_text(""),
                                    m_rect(sf::Vector2f(15 * m_size, 20))
{
            m_font.loadFromFile("fonts/arial.ttf");
            m_renderText.setFont(m_font);
            m_renderText.setString("Input command here...");
            m_renderText.setFillColor(sf::Color::Black);
            m_renderText.setCharacterSize(15);
            m_rect.setOutlineThickness(2);
            m_rect.setFillColor(sf::Color::White);
            m_rect.setOutlineColor(sf::Color(127,127,127));
            m_rect.setPosition(this->getPosition());
}

TextBox::~TextBox() {}

void TextBox::handleInput(sf::Event event)
{
    if (!m_focus || event.type != sf::Event::TextEntered)
        return;
    if (event.text.unicode == 8)
    {
        try
        {
            m_text = m_text.erase(m_text.size() - 1, 1);
        }
        catch(std::out_of_range& e)
        {
            m_text = "";
        }
    }
    else if (m_text.size() < m_size)
    {
        if( (event.text.unicode >= '0' && event.text.unicode <= '9') || 
            (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
            (event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
            event.text.unicode == ' ')
                m_text += event.text.unicode;
    }
    m_renderText.setString(m_text);
}

bool TextBox::contains(sf::Vector2f point) const
{
    return m_rect.getGlobalBounds().contains(point);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_rect, states);
    target.draw(m_renderText, states);
}

const std::string TextBox::getText() const
{
    return m_text;
}

void TextBox::setPosition(float x, float y)
{
    sf::Transformable::setPosition(x, y);
    m_rect.setPosition(x, y);
    m_renderText.setPosition(x, y);
}

void TextBox::setFocus(bool focus)
{
    m_focus = focus;
    if (focus)
    {
        m_rect.setOutlineColor(sf::Color::Blue);
    }
    else
    {
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
    }
}

void TextBox::clear()
{
    m_text = "";
    m_renderText.setString("");
}