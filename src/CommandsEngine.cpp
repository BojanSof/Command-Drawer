#include <CommandsEngine.h>

state CommandsEngine::processCommand(const std::string& command)
{
    state newState;
    reset();
    m_parser.str(command);
    std::string token;
    while(std::getline(m_parser, token, ' '))
    {
        m_tokens.push_back(token);
    }
    std::transform(m_tokens[0].begin(), m_tokens[0].end(), m_tokens[0].begin(), ::tolower);
    if(m_tokens[0] == "move")
    {
        newState = state::MOVE;
        if(m_tokens.size() != 3) 
        {
            newState = state::UNKNOWN;
            errorMessage = "Usage: move <x-coordinate> <y-coordinate>";
        }
        else
        {
            try
            {
                uint param1 = std::stoul(m_tokens[1]);
                uint param2 = std::stoul(m_tokens[2]);
                parameters.push_back(param1);
                parameters.push_back(param2);
            }
            catch(const std::invalid_argument& e)
            {
                newState = state::UNKNOWN;
                errorMessage = "Usage: move <x-coordinate> <y-coordinate>";
            }
        }
        
    } 
    else if(m_tokens[0] == "draw")
    {
        std::transform(m_tokens[1].begin(), m_tokens[1].end(), m_tokens[1].begin(), ::tolower);
        if(m_tokens[1] == "line")
        {
            newState = state::DRAW_LINE;
            if(m_tokens.size() != 4) 
            {
                newState = state::UNKNOWN;
                errorMessage = "Usage: move <x-coordinate> <y-coordinate>";
            }
            else
            {
                try
                {
                    uint param1 = std::stoul(m_tokens[2]);
                    uint param2 = std::stoul(m_tokens[3]);
                    parameters.push_back(param1);
                    parameters.push_back(param2);
                }
                catch(const std::invalid_argument& e)
                {
                    newState = state::UNKNOWN;
                    errorMessage = "Usage: draw line <x-coordinate> <y-coordinate>";
                }
            }
        }
        else
        {
            newState = state::UNKNOWN;
            errorMessage = "Usage: draw <shape> <param1> <param2>";
        }
        
    }
    else if(m_tokens[0] == "reset")
    {
        newState = state::RESET;
    }
    else if(m_tokens[0] == "quit")
    {
        newState = state::QUIT;
    }
    else
    {
        newState = state::UNKNOWN;
        errorMessage = "Unknow command: " + m_tokens[0];
    }
    return newState;
}

void CommandsEngine::reset()
{
    m_parser.clear();
    m_tokens.clear();
    parameters.clear();
    errorMessage = "";
}