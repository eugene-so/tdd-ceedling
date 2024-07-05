#ifndef SERIAL_CONSOLE_H
#define SERIAL_CONSOLE_H

#include <stdio.h>


#include "ignore.h"
#include "text.h"

#define PRINTF printf

static inline int DUMMY_PRINTF(const char* fmt, ...)
{
    IGNORE(fmt);
    return 0;
}

#define DEBUG_PRINTF_0                  DUMMY_PRINTF
#define DEBUG_PRINTF_1                  PRINTF

#define DEBUG_PRINTF_X(option)          JOINOF(DEBUG_PRINTF_, option)


#endif // SERIAL_CONSOLE_H
