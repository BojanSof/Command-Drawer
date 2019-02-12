#ifndef APP_H
#define APP_H

#include <Common.h>
#include <CommandsEngine.h>
#include <Drawer.h>
#include <Textbox.h>
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
        void reset();
        void handleEvents();
        void update();
        void display();

    private:
        sf::RenderWindow m_window;
        std::string m_title;
        bool m_running;
        uint m_width;
        uint m_height;
        CommandsEngine m_engine;
        Drawer m_drawer;
        TextBox m_textbox;
        sf::Text m_status;
        sf::Font m_font;
        std::string m_input;
    public:
        state appState;
};

#endif //APP_H