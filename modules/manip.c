#include <stdio.h>
#include <string.h>

#include "../pmang.h"
#include "../lib/err_codes.h"
#include "../lib/errmgr.h"
#include "../config.h"

extern size_t pjtop;
extern PROJECT* projects;
extern size_t p_curr;

int clear(int argc, char** argv) {

   if (argc > 1) return INVALID_ARGS;

   const int clear_stat = argc == 1 ? atoi(argv[0]) : -1;

   if (clear_stat == -1) {
      print_err(E_WARN, "You are about to clear all projects.");
      print_err(E_WARNC, "Type in \"CONFIRM\" to continue.");

      char input[100];
      printf("> ");
      scanf("%s", &input);

      if (strcmp(input, "CONFIRM") != 0) return OK;
   }

   for (size_t i = 0; i < pjtop; i++) {
      if (clear_stat == -1 || projects[i].status == clear_stat) {
         projects[i].valid = 0;
      }
   }

   return OK;
}

int rename_proj(int argc, char** argv) {

   if (argc != 2) return INVALID_ARGS;

   const int index = find_idx(argv[0]);
   
   if (index == P_MAX + 1) return PROJ_DNE;

   projects[index].name = realloc(projects[index].name, (strlen(argv[1]) + 1) * sizeof(char));

   strcpy(projects[index].name, argv[1]);

   return OK;
}