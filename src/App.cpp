#include <App.h>

Application::Application() :    m_running(true),
                                m_width(1366), m_height(768), 
                                m_title("Command Drawer"),
                                m_window(sf::VideoMode(1366, 768, 32), "Command Drawer", sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_textbox(),
                                m_input(""),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.move(m_width/2.0f, m_height/2.0f);
    m_textbox.setPosition(30, 30);
    m_font.loadFromFile("fonts/arial.ttf");
    m_status.setFont(m_font);
    m_status.setPosition(0, m_height - 20);
    m_status.setFillColor(sf::Color::White);
    m_status.setCharacterSize(15);
    m_status.setString("Ready");
}

Application::Application(uint width, uint height, const std::string& title) :    
                                m_running(true),
                                m_width(width), m_height(height), 
                                m_title(title),
                                m_window(sf::VideoMode(width, height, 32), title, sf::Style::Default),
                                m_engine(),
                                m_drawer(),
                                m_textbox(25, 20),
                                m_input(""),
                                appState(state::START)
{
    m_window.setFramerateLimit(60);
    m_drawer.move(m_width/2.0f, m_height/2.0f);
    m_textbox.setPosition(30, 30);
    m_font.loadFromFile("fonts/arial.ttf");
    m_status.setFont(m_font);
    m_status.setPosition(0, m_height - 20);
    m_status.setCharacterSize(15);
    m_status.setFillColor(sf::Color::White);
    m_status.setString("Ready");
}

Application::~Application() 
{
    m_window.close();
}

bool Application::isRunning() const
{
    return m_running;
}

void Application::reset()
{
    m_drawer.reset();
    m_drawer.move(m_width/2.0f, m_height/2.0f);
    m_engine.reset();
    m_textbox.clear();
    appState = state::IDLE;
    m_status.setString("Ready");
}

void Application::handleEvents()
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

void Application::update()
{
    switch(appState)
    {
        case state::START:
            m_window.clear();
            m_window.draw(m_drawer);
            m_status.setString("Ready");
        break;
        case state::MOVE:
            m_window.clear();
            m_drawer.move(m_engine.parameters[0], m_engine.parameters[1]);
            m_window.draw(m_drawer);
            m_status.setString("Drawer moved successfully...");
        break;
        case state::DRAW_LINE:
            m_window.clear();
            m_drawer.drawLine(m_engine.parameters[0], m_engine.parameters[1]);
            m_window.draw(m_drawer);
            m_status.setString("Line drawn successfully...");
        break;
        case state::RESET:
            m_window.clear();
            reset();
            m_window.draw(m_drawer);
            m_status.setString("Ready");
        break;
        case state::QUIT:
            m_running = false;
            m_status.setString("Exiting...");
        break;
        case state::UNKNOWN:
            m_status.setString(m_engine.errorMessage);
        break;
        default:
            m_window.clear();
            m_window.draw(m_drawer);
        break;
    }
    m_window.draw(m_status);
    m_window.draw(m_textbox);
    appState = state::IDLE;
}

void Application::display()
{
    m_window.display();
}