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
        state processCommand(std::string command);
        void Reset();
    private:
        std::istringstream m_parser;
    public:
        std::vector<uint> parameters;
        std::string errorMessage;
};

#endif //COMMANDSENGINE_H