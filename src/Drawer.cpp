#include <Drawer.h>

Drawer::Drawer() : m_radius(5.0f), m_x(0), m_y(0), m_body(5.0f), m_shape(sf::Lines)
{
    m_body.setFillColor(sf::Color(0, 191, 255));
    m_body.setOrigin(m_radius, m_radius);
    m_body.setPosition(0, 0);
}


Drawer::~Drawer()
{
}

const sf::CircleShape& Drawer::getBody() const
{
    return m_body;
}

const sf::VertexArray& Drawer::getShapes() const
{
    return m_shape;
}

void Drawer::Move(float x, float y)
{
    m_x = x;
    m_y = y;
    m_body.setPosition(x, y);
}

void Drawer::Reset()
{
    m_x = 0;
    m_y = 0;
    m_body.setPosition(m_x, m_y);
    m_shape.clear();
}

sf::VertexArray& Drawer::DrawLine(float x, float y)
{
    sf::Vertex start(sf::Vector2f(m_x, m_y), sf::Color::Red);
    sf::Vertex end(sf::Vector2f(x, y), sf::Color::Red);
    m_shape.append(start);
    m_shape.append(end);
    m_x = x;
    m_y = y;
    Move(m_x, m_y);
    return m_shape;
}