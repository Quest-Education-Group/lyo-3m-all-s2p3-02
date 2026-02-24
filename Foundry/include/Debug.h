#ifndef DEBUG__H_
#define DEBUG__H_

//=== ANSI ESCAPE CODE ========
#define ESC "\x1B"
#define ANSI_RED      ESC"[31m"
#define ANSI_GREEN    ESC"[32m"
#define ANSI_GOLD     ESC"[38;5;178m"

#define ANSI_ITALIC   ESC"[3m"
#define ANSI_BOLD     ESC"[1m"

#define ANSI_RESET    ESC"[0m"
//=============================

#ifdef DEBUG_BUILD
#  include <iostream>
#  define DEBUG(x) do { std::cerr << x; } while (0)
#else
#  define DEBUG(x) do {} while (0)
#endif

#define DEBUG_WHILE_TRUE() \
char key; \
do { \
    key = getchar(); \
} while (key != 27) //Escape key \

#endif
