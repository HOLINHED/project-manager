#include <stdio.h>

#include "../pmang.h"
#include "../lib/err_codes.h"
#include "../config.h"
#include "../lib/errmgr.h"

extern size_t pjtop;
extern PROJECT* projects;
extern size_t p_curr;

int set_curr(int argc, char** argv) {

   if (argc != 1) return INVALID_ARGS;

   size_t index = find_idx(*argv);

   if (index == P_MAX + 1) return PROJ_DNE;

   p_curr = index;

   return OK;
}

int get_curr(int argc, char** argv) {

   if (argc != 0) return INVALID_ARGS;

   if (p_curr == P_MAX + 1) {
      print_err(E_NOTE, "There is no current task.");
      return OK;
   }

   printf(C_CUR "Current Task: " C_RST "%s\n", projects[p_curr].name);

   return OK;
}

int unset_curr(int argc, char** argv) {
   if (argc != 0) return INVALID_ARGS;
   p_curr = P_MAX + 1;
   return OK;
}