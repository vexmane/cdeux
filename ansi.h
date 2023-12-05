#ifndef ANSI_H
#define ANSI_H

// ANSI escape codes for text colors and others
// https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
// FOREGROUND DEFAULT
#define ACLR_FG_BLACK   "\x1b[30m"
#define ACLR_FG_RED     "\x1b[31m"
#define ACLR_FG_GREEN   "\x1b[32m"
#define ACLR_FG_YELLOW  "\x1b[33m"
#define ACLR_FG_BLUE    "\x1b[34m"
#define ACLR_FG_MAGENTA "\x1b[35m"
#define ACLR_FG_CYAN    "\x1b[36m"
#define ACLR_FG_WHITE   "\x1b[37m"
// FOREGROUND BRIGHT
#define ACLR_FG_GRAY           "\x1b[90m"
#define ACLR_FG_BRIGHT_RED     "\x1b[91m"
#define ACLR_FG_BRIGHT_GREEN   "\x1b[92m"
#define ACLR_FG_BRIGHT_YELLOW  "\x1b[93m"
#define ACLR_FG_BRIGHT_BLUE    "\x1b[94m"
#define ACLR_FG_BRIGHT_MAGENTA "\x1b[95m"
#define ACLR_FG_BRIGHT_CYAN    "\x1b[96m"
#define ACLR_FG_BRIGHT_WHITE   "\x1b[97m"
// BACKGROUND DEFAULT
#define ACLR_BG_BLACK   "\x1b[40m"
#define ACLR_BG_RED     "\x1b[41m"
#define ACLR_BG_GREEN   "\x1b[42m"
#define ACLR_BG_YELLOW  "\x1b[43m"
#define ACLR_BG_BLUE    "\x1b[44m"
#define ACLR_BG_MAGENTA "\x1b[45m"
#define ACLR_BG_CYAN    "\x1b[46m"
#define ACLR_BG_WHITE   "\x1b[47m"
// BACKGROUND BRIGHT
#define ACLR_BG_GRAY           "\x1b[100m"
#define ACLR_BG_BRIGHT_RED     "\x1b[101m"
#define ACLR_BG_BRIGHT_GREEN   "\x1b[102m"
#define ACLR_BG_BRIGHT_YELLOW  "\x1b[103m"
#define ACLR_BG_BRIGHT_BLUE    "\x1b[104m"
#define ACLR_BG_BRIGHT_MAGENTA "\x1b[105m"
#define ACLR_BG_BRIGHT_CYAN    "\x1b[106m"
#define ACLR_BG_BRIGHT_WHITE   "\x1b[107m"

#define ACLR_RESET   "\x1b[0m"
#define ANSI_CLEAR   "\033[2J"
#define ANSI_HOME    "\033[H"

#endif
