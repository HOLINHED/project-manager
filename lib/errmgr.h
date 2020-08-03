#ifndef H_ERRMGR
#define H_ERRMGR

#define E_NOTE 0
#define E_WARN 1
#define E_ERR 2
#define E_NOTEC 3
#define E_WARNC 4
#define E_ERRC 5

#define E_MSG_L "\033[0;36mNote:\033[0m"
#define E_WAR_L "\033[0;33mWarning:\033[0m"
#define E_ERR_L "\033[0;31mError:\033[0m"
#define E_MSGC_L "\033[0;36m     \033[0m"
#define E_WARC_L "\033[0;33m        \033[0m"
#define E_ERRC_L "\033[0;31m      \033[0m"

void print_err(int, char*);

#endif