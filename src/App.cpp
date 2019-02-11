#include <App.h>

Application::Application() :    m_running(true),
                                m_width(1366), m_height(768), 
                                m_title("Command Drawer"),
                                m_window(sf::VideoMode(1366, 768, 32), "Command Drawer", sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_textbox(30),
                                m_input(""),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
    m_textbox.setPosition(30, 30);
    std::cout << "\nCommand Drawer" << std::endl; 
}

Application::Application(uint width, uint height, const std::string& title) :    
                                m_running(true),
                                m_width(width), m_height(height), 
                                m_title(title),
                                m_window(sf::VideoMode(width, height, 32), title, sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_textbox(30),
                                m_input(""),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.Move(m_width/2.0f, m_height/2.0f);
    m_textbox.setPosition(30, 30);
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
            case sf::Event::MouseButtonReleased:
            {
                m_textbox.setFocus(false);
                sf::Vector2i pos = sf::Mouse::getPosition(m_window);
                if(m_textbox.contains(sf::Vector2f(pos)))
                {
                    m_textbox.setFocus(true);
                }
            }
            break;
            /*case sf::Event::TextEntered:
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
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
            break;*/
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Escape:
                        m_running = false;
                    break;
                    case sf::Keyboard::Return:
                        appState = m_engine.processCommand(m_input);
                        m_input = "";
                        m_textbox.clear();
                    break;
                    default:
                    break;
                }
            }
            break;
            default:
                m_textbox.handleInput(event);
                m_input = m_textbox.getText();
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
            m_window.clear();
            m_window.draw(m_drawer.getBody());
            m_window.draw(m_drawer.getShapes());
        break;
    }
    m_window.draw(m_textbox);
    appState = state::IDLE;
}

void Application::Display()
{
    m_window.display();
}