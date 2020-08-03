#include <stdio.h>

#include "errmgr.h"

void print_err(int type, char* message) {

   const char* label[] = { E_MSG_L, E_WAR_L, E_ERR_L, E_MSGC_L, E_WARC_L, E_ERRC_L };

   printf("%s %s\n", label[type], message);
}