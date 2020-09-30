#include <string.h>

#include "../pmang.h"
#include "../lib/err_codes.h"
#include "../config.h"

extern size_t pjtop;
extern PROJECT* projects;
extern size_t p_curr;

int add_proj(int argc, char** argv) {

   if (argc < 1 || argc > 2) return INVALID_ARGS;
   if (pjtop >= P_MAX) return PROJ_LIMIT;
   if (find_idx(argv[0]) != P_MAX + 1) return PROJ_EXISTS;

   const int pstat = argc == 2 ? atoi(argv[1]) : 0;

   if (pstat > 4 || pstat < 0) return ADD_INVALID_STATUS;

   const size_t nsize = strlen(argv[0]);
   for (size_t i = 0; i < nsize; i++) {
      if (argv[0][i] == ' ') argv[0][i] = '_';
   }

   PROJECT to_ins;
   to_ins.name = malloc((nsize + 1) * sizeof(char));
   to_ins.status = pstat;
   to_ins.valid = 1;

   strcpy(to_ins.name, argv[0]);

   projects[pjtop++] = to_ins;

   return OK;
}

int remove_proj(int argc, char** argv) {

   if (argc != 1) return INVALID_ARGS;

   size_t index = find_idx(argv[0]);

   if (index == P_MAX + 1) return PROJ_DNE;

   if (p_curr == index) p_curr = P_MAX + 1;

   projects[index].valid = 0;
   
   return OK;
}