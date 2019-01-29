#ifndef APP_H
#define APP_H

#include <Common.h>
#include <Drawer.h>
#include <SFML/Graphics.hpp>
#include <string>

enum class state {IDLE, DRAWING};

class Application
{
    public:
        Application();
        Application(uint width, uint height, const std::string& title);
        ~Application();
        
        bool isRunning() const;
        const sf::RenderWindow& getWindow() const;
        Drawer& getDrawer();
        
        void HandleEvents();
        void Update();
        void Display();


    private:
        Drawer m_drawer;
        sf::RenderWindow m_window;
        std::string m_title;
        bool m_running;
        uint m_width;
        uint m_height;
    public:
        state appState;
};

#endif //APP_H