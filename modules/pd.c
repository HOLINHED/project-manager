#include "../pmang.h"
#include "../lib/err_codes.h"
#include "../config.h"

extern size_t pjtop;
extern PROJECT* projects;
extern size_t p_curr;

int pd_proj(int argc, char** argv, int type) {

   if (argc < 1 || argc > 2) return INVALID_ARGS;

   const int amount = argc == 2 ? atoi(argv[1]) : 1;
   const size_t index = find_idx(argv[0]);

   if (index == P_MAX + 1) return PROJ_DNE;

   int new_status = type == 0 ? 
      projects[index].status + amount :
      projects[index].status - amount;

   if (new_status < 0) return PD_MIN;
   if (new_status > 4) return PD_MAX;

   projects[index].status = new_status;

   return OK;
}