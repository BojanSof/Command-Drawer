#include <CommandsEngine.h>

state CommandsEngine::processCommand(std::string command)
{
    state newState;
    Reset();
    m_parser.str(command);
    std::vector<std::string> tokens;
    std::string token;
    while(std::getline(m_parser, token, ' '))
    {
        tokens.push_back(token);
        std::cout << "Token: " << token << std::endl;
    }
    std::transform(tokens[0].begin(), tokens[0].end(), tokens[0].begin(), ::tolower);
    if(tokens[0] == "move")
    {
        newState = state::MOVE;
        if(tokens.size() != 3) 
        {
            newState = state::UNKNOWN;
            errorMessage = "Usage: move <x-coordinate> <y-coordinate>";
        }
        else
        {
            try
            {
                uint param1 = std::stoul(tokens[1]);
                uint param2 = std::stoul(tokens[2]);
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
    else if(tokens[0] == "draw")
    {
        std::transform(tokens[1].begin(), tokens[1].end(), tokens[1].begin(), ::tolower);
        if(tokens[1] == "line")
        {
            newState = state::DRAW_LINE;
            if(tokens.size() != 4) 
            {
                newState = state::UNKNOWN;
                errorMessage = "Usage: move <x-coordinate> <y-coordinate>";
            }
            else
            {
                try
                {
                    uint param1 = std::stoul(tokens[2]);
                    uint param2 = std::stoul(tokens[3]);
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
            errorMessage = "Usage: draw <shape> <param1> <param2> ...";
        }
        
    }
    else if(tokens[0] == "reset")
    {
        newState = state::RESET;
    }
    else if(tokens[0] == "quit")
    {
        newState = state::QUIT;
    }
    else
    {
        newState = state::UNKNOWN;
        errorMessage = "Unknow command: " + tokens[0];
    }
    return newState;
}

void CommandsEngine::Reset()
{
    m_parser.clear();
    parameters.clear();
    errorMessage = "";
}