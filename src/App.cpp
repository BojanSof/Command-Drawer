#include <App.h>

Application::Application() :    m_running(true),
                                m_width(1366), m_height(768), 
                                m_title("Command Drawer"),
                                m_window(sf::VideoMode(1366, 768, 32), "Command Drawer", sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_input(""),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
    std::cout << "\nCommand Drawer" << std::endl; 
}

Application::Application(uint width, uint height, const std::string& title) :    
                                m_running(true),
                                m_width(width), m_height(height), 
                                m_title(title),
                                m_window(sf::VideoMode(width, height, 32), title, sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_input(),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
    std::cout << "\nCommand Drawer" << std::endl;
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

void Application::Reset()
{
    m_drawer.Reset();
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
    m_engine.Reset();
    appState = state::IDLE;
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
            case sf::Event::TextEntered:
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    std::cout << "Length of command:" << m_input.length() << std::endl;
                    appState = m_engine.processCommand(m_input);
                    m_input = "";
                }
                else if(event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);
                    m_input += c;
                    std::cout << m_input << std::endl;
                }
            }
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
    switch(appState)
    {
        case state::START:
            m_window.clear();
            m_window.draw(m_drawer.getBody());
        break;
        case state::MOVE:
            m_window.clear();
            m_drawer.Move(m_engine.parameters[0], m_engine.parameters[1]);
            m_window.draw(m_drawer.getBody());
            m_window.draw(m_drawer.getShapes());
        break;
        case state::DRAW_LINE:
            m_window.clear();
            m_window.draw(m_drawer.DrawLine(m_engine.parameters[0], m_engine.parameters[1]));
            m_window.draw(m_drawer.getBody());
        break;
        case state::RESET:
            m_window.clear();
            Reset();
            m_window.draw(m_drawer.getBody());
        break;
        case state::QUIT:
            m_running = false;
        break;
        case state::UNKNOWN:
            std::cout << m_engine.errorMessage << std::endl;
        break;
        default:
        break;
    }
    appState = state::IDLE;
    /*if(appState == state::DRAW_LINE)
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
    }*/
}

void Application::Display()
{
    m_window.display();
}