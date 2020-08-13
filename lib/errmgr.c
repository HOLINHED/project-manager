#include <stdio.h>
#include <stdarg.h>

#include "errmgr.h"

void print_err(int type, const char* message, ...) {

   const char* label[] = { E_MSG_L, E_WAR_L, E_ERR_L, E_MSGC_L, E_WARC_L, E_ERRC_L };

   va_list args;
   va_start(args, message);
   printf("%s ", label[type]);
   vprintf(message, args);
   putchar('\n');
   va_end(args);
}