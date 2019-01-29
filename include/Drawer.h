#ifndef DRAWER_H
#define DRAWER_H

#include <Common.h>
#include <SFML/Graphics.hpp>

class Drawer
{
    public:
        Drawer();
        ~Drawer();

        const sf::CircleShape& getBody() const;
        
        void Move(float x, float y);
        sf::VertexArray& DrawLine(float x, float y);
        
    private:
        sf::CircleShape m_body;
        float m_radius; 
        float m_x;
        float m_y;
        sf::VertexArray m_shape;
};

#endif //DRAWER_H