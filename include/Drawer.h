#ifndef DRAWER_H
#define DRAWER_H

#include <Common.h>
#include <SFML/Graphics.hpp>

class Drawer : public sf::Drawable
{
    public:
        Drawer();
        Drawer(float radius, float x, float y);
        ~Drawer();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        
        void move(float x, float y);
        void drawLine(float x, float y);
        void reset();        
    private:
        sf::CircleShape m_body;
        float m_radius; 
        float m_x;
        float m_y;
        sf::VertexArray m_shape;
};

#endif //DRAWER_H