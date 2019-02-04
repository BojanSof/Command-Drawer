#ifndef COMMON_H
#define COMMON_H

#include <stdexcept>

typedef unsigned int uint;
typedef unsigned long long ullong;

enum class state {UNKNOWN, RESET, QUIT, START, IDLE, MOVE, DRAW_LINE};

#endif //COMMON_H