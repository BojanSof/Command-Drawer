#ifndef APP_H
#define APP_H

#include <Common.h>
#include <CommandsEngine.h>
#include <Drawer.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Application
{
    public:
        Application();
        Application(uint width, uint height, const std::string& title);
        ~Application();
        
        bool isRunning() const;
        const sf::RenderWindow& getWindow() const;
        Drawer& getDrawer();
        void Reset();
        
        void HandleEvents();
        void Update();
        void Display();

    private:
        CommandsEngine m_engine;
        Drawer m_drawer;
        sf::RenderWindow m_window;
        std::string m_title;
        bool m_running;
        uint m_width;
        uint m_height;
        std::string m_input;
    public:
        state appState;
};

#endif //APP_H