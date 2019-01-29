#include <App.h>

Application::Application() :    m_running(true),
                                m_width(1366), m_height(768), 
                                m_title("Command Drawer"),
                                m_window(sf::VideoMode(1366, 768, 32), "Command Drawer", sf::Style::Default),
                                m_drawer(),
                                appState(state::DRAWING)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);  
}

Application::Application(uint width, uint height, const std::string& title) :    
                                m_running(true),
                                m_width(width), m_height(height), 
                                m_title(title),
                                m_window(sf::VideoMode(width, height, 32), title, sf::Style::Default),
                                m_drawer(),
                                appState(state::DRAWING)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
}

Application::~Application() 
{
    m_window.close();
}

bool Application::isRunning() const
{
    return m_running;
}

const sf::RenderWindow& Application::getWindow() const
{
    return m_window;
}

void Application::HandleEvents()
{
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
                m_running = false;
            break;
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_running = false;
                    break;
                    default:
                    break;
                }
            }
            break;
            default:
            break;
        }    
    }
}

void Application::Update()
{
    if(appState == state::DRAWING)
    {
        m_window.clear();
        m_drawer.Move(100, 100);
        m_window.draw(m_drawer.DrawLine(100, 500));
        m_window.draw(m_drawer.DrawLine(400, 500));
        m_window.draw(m_drawer.DrawLine(400, 300));
        m_window.draw(m_drawer.DrawLine(100, 300));
        m_drawer.Move(100, 100);
        m_window.draw(m_drawer.DrawLine(400, 100));
        m_window.draw(m_drawer.getBody());
        appState = state::IDLE;
    }
}

void Application::Display()
{
    m_window.display();
}