#ifndef H_CONFIG
#define H_CONFIG

/* General */
#define ALIAS_NAME "pmang"
#define INSTALL_PATH "/home/dawid/devel/proj-mgr"
#define BUILD_CMD "sh " INSTALL_PATH "/make.sh " INSTALL_PATH

/* Path to save file */
#define P_PATH "/home/dawid/.cache/pmang/pmang.dat"
#define P_PATH_D "./test.dat"

/* Maximum amount of projects */
#define P_MAX 25

/* Command Friendly Names */
#define CMD_ADD "add"
#define CMD_ADD_A "a"
#define CMD_REM "remove"
#define CMD_REM_A "r"
#define CMD_PRM "promote"
#define CMD_PRM_A "p"
#define CMD_DMT "demote"
#define CMD_DMT_A "d"
#define CMD_SCR "setcurr"
#define CMD_SCR_A "sc"
#define CMD_RCR "rmcurr"
#define CMD_RCR_A "rc"
#define CMD_CUR "current"
#define CMD_CUR_A "cr"
#define CMD_RNM "rename"
#define CMD_RNM_A "rn"
#define CMD_LST "list"
#define CMD_LST_A "ls"
#define CMD_LLT "llist"
#define CMD_LLT_A "ll"
#define CMD_GET "get"
#define CMD_GET_A "g"
#define CMD_CLR "clear"
#define CMD_CLR_A "c"
#define CMD_RBD "rebuild"
#define CMD_RBD_A "rb"
#define CMD_VER "version"
#define CMD_VER_A "v"
#define CMD_HLP "help"
#define CMD_HLP_A "h"
#define CMD_INF "info"
#define CMD_INF_A "i"

/* Colors for each status */
#define C_NON "\033[0;36m"
#define C_LOW "\033[0;36m"
#define C_MED "\033[0;33m"
#define C_HIG "\033[0;31m"
#define C_CRT "\033[1;31m"
#define C_CUR "\033[0;32m"
#define C_RST "\033[0m"

/* Label for each status */
#define S_NON "[     ]"
#define S_LOW "[ LOW ]"
#define S_MED "[ MID ]"
#define S_HIG "[ HIG ]"
#define S_CRT "[ CRT ]"

#endif