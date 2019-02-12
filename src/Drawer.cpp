#include <Drawer.h>

Drawer::Drawer() : m_radius(5.0f), m_x(0), m_y(0), m_body(5.0f), m_shape(sf::Lines)
{
    m_body.setFillColor(sf::Color(0, 191, 255));
    m_body.setOrigin(m_radius, m_radius);
    m_body.setPosition(0, 0);
}

Drawer::Drawer(float radius, float x, float y) : m_radius(radius), m_x(x), m_y(y), m_body(radius), m_shape(sf::Lines)
{
    m_body.setFillColor(sf::Color(0, 191, 255));
    m_body.setOrigin(m_radius, m_radius);
    m_body.setPosition(0, 0);
}

Drawer::~Drawer()
{
}

void Drawer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_body, states);
    target.draw(m_shape, states);
}

void Drawer::move(float x, float y)
{
    m_x = x;
    m_y = y;
    m_body.setPosition(x, y);
}

void Drawer::drawLine(float x, float y)
{
    sf::Vertex start(sf::Vector2f(m_x, m_y), sf::Color::Red);
    sf::Vertex end(sf::Vector2f(x, y), sf::Color::Red);
    m_shape.append(start);
    m_shape.append(end);
    m_x = x;
    m_y = y;
    this->move(m_x, m_y);
}

void Drawer::reset()
{
    m_x = 0;
    m_y = 0;
    m_body.setPosition(m_x, m_y);
    m_shape.clear();
}