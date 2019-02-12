#ifndef COMMANDSENGINE_H
#define COMMANDSENGINE_H

#include <Common.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class CommandsEngine
{
    public:
        state processCommand(const std::string& command);
        void reset();
    private:
        std::istringstream m_parser;
        std::vector<std::string> m_tokens;
    public:
        std::vector<uint> parameters;
        std::string errorMessage;
};

#endif //COMMANDSENGINE_H