#include "../pmang.h"
#include "../lib/err_codes.h"
#include "../config.h"

extern size_t pjtop;
extern PROJECT* projects;
extern size_t p_curr;

int list(int argc, char** argv, int type) {

   if (argc > 1) return INVALID_ARGS;

   const int pstat = argc == 1 ? atoi(argv[0]) : -1;

   void (*pfunc[2])(char*, size_t) = { print_proj, print_projl };

   for (size_t i = 0; i < pjtop; i++) {
      if (projects[i].valid == 1 && projects[i].status >= pstat) {
         (*pfunc[type])(projects[i].name, i);
      }
   }

   return OK;
}

int get(int argc, char** argv) {

   if (argc == 0) return INVALID_ARGS;

   for (int i = 0; i < argc; i++) {
      print_proj(argv[i], P_MAX + 2);
   }

   return OK;
}