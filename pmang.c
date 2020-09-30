#include <stdio.h>
#include <string.h>

#include "pmang.h"
#include "config.h"
#include "./lib/errmgr.h"
#include "./lib/manual.h"
#include "./lib/info.h"
#include "./lib/err_codes.h"
#include "./lib/proj_file.h"

#define argcmp(x, y, z) strcmp(x, y) == 0 || strcmp(x,z) == 0

const static char* stat_msg[] = { S_NON, S_LOW, S_MED, S_HIG, S_CRT };
const static char* stat_clr[] = { C_NON, C_LOW, C_MED, C_HIG, C_CRT };

static int status = 0;

PROJECT* projects;
size_t pjtop = 0;
size_t p_curr = P_MAX + 1;

static size_t longest_name = 0;
static size_t shortest_name = 0;

size_t find_idx(char* pname) {
   for (size_t i = 0; i < pjtop; i++) 
      if (strcmp(projects[i].name, pname) == 0) return i;
   return P_MAX + 1;
}

void print_proj(char* pname, size_t idx) {

   size_t index = idx;
   if (index == P_MAX + 2) index = find_idx(pname);

   if (index != P_MAX + 1) {
      const int pos = projects[index].status;

      printf("%s%s" C_RST " %s%s\n", stat_clr[pos], stat_msg[pos], index == p_curr ? C_CUR : "\0", pname);
   }
}

void print_projl(char* pname, size_t idx) {

   size_t index = idx;
   if (index == P_MAX + 2) index = find_idx(pname);

   if (index == P_MAX + 1) {
      print_err(E_ERR, "Specified project not found.");
      return;
   }

   size_t l_diff = longest_name - strlen(projects[index].name) + 1;

   const char* bar[] = {"■", "■■■■■■", "■■■■■■■■■■■", "■■■■■■■■■■■■■■■■", "■■■■■■■■■■■■■■■■■■■■■"};
   const int pos = projects[index].status;

   printf("%s%s" C_RST "%*c│ %s%s\n", stat_clr[pos], projects[index].name, l_diff, ' ', 
          index == p_curr ? C_CUR : "\0", bar[pos]);
}

void set_long_short(void) {
   size_t longest = 0;
   size_t shortest = __INT64_MAX__;

   for (size_t i = 0; i < pjtop; i++) {
      size_t len = strlen(projects[i].name);
      if (len > longest) longest = len;
      if (len < shortest) shortest = len;
   }

   longest_name = longest;
   shortest_name = shortest;
}

void sort_projs(void) {
   
   for (int i = 0; i < pjtop; i++) {
      int biggest = i;
      for (int j = i; j < pjtop; j++) {
         if (projects[j].status > projects[biggest].status) biggest = j;
      }
      if (projects[biggest].status > projects[i].status) {
         PROJECT temp = projects[i];
         projects[i] = projects[biggest];
         projects[biggest] = temp;
      }
   }
}

int main(int argc, char** argv) {

   if (argc < 2) {
      print_err(E_NOTE, "Usage: " ALIAS_NAME " <cmd> <args...>");
      print_err(E_NOTEC, "Run help (h) for more information.");
      return USAGE;
   }

   const char* cmd = argv[1];

   argv += 2;
   argc -= 2;

   projects = malloc(P_MAX * sizeof(PROJECT));

   load(projects, &pjtop, &status, &p_curr);

   if (status != 0) return status;

   sort_projs();
   set_long_short();

        if (argcmp(cmd, CMD_ADD, CMD_ADD_A)) status = add_proj(argc, argv);
   else if (argcmp(cmd, CMD_REM, CMD_REM_A)) status = remove_proj(argc, argv);
   else if (argcmp(cmd, CMD_PRM, CMD_PRM_A)) status = pd_proj(argc, argv, 0);
   else if (argcmp(cmd, CMD_DMT, CMD_DMT_A)) status = pd_proj(argc, argv, 1);
   else if (argcmp(cmd, CMD_GET, CMD_GET_A)) status = get(argc, argv);
   else if (argcmp(cmd, CMD_LST, CMD_LST_A)) status = list(argc, argv, 0);
   else if (argcmp(cmd, CMD_LLT, CMD_LLT_A)) status = list(argc, argv, 1);
   else if (argcmp(cmd, CMD_SCR, CMD_SCR_A)) status = set_curr(argc, argv);
   else if (argcmp(cmd, CMD_CUR, CMD_CUR_A)) status = get_curr(argc, argv);
   else if (argcmp(cmd, CMD_RCR, CMD_RCR_A)) status = unset_curr(argc, argv);
   else if (argcmp(cmd, CMD_CLR, CMD_CLR_A)) status = clear(argc, argv);
   else if (argcmp(cmd, CMD_RNM, CMD_RNM_A)) status = rename_proj(argc, argv);
   else if (argcmp(cmd, CMD_VER, CMD_VER_A)) puts("Pmang v" VERSION);
   else if (argcmp(cmd, CMD_HLP, CMD_HLP_A)) puts(MANUAL);
   else if (argcmp(cmd, CMD_RBD, CMD_RBD_A)) {
      int r = system(BUILD_CMD);
      print_err(E_NOTE, "Build process exited with status \"%d\"", r);
   }
   else status = INVALID_CMD;

   save(projects, &pjtop, &status, p_curr);

   switch(status) {
      case INVALID_ARGS: print_err(E_ERR, "Invalid arguments for command \"%s\".", *(argv - 1)); break;
      case PROJ_DNE: print_err(E_ERR, "Project \"%s\" not found.", *argv); break;
      case INVALID_CMD: print_err(E_ERR, "Command \"%s\" not found.", *(argv - 1)); break;
      case PROJ_LIMIT: print_err(E_ERR, "Project limit has been reached (%ld).", P_MAX); break;
      case PROJ_EXISTS: print_err(E_ERR, "Project \"%s\" already exists.", *argv); break;
      case ADD_INVALID_STATUS: print_err(E_ERR, "Invalid initial priority for add. Must be between 0 and 4."); break;
      case PD_MAX: print_err(E_ERR, "Project priority already at the highest."); break;
      case PD_MIN: print_err(E_ERR, "Project priority already at the lowest."); break;
   }

   for (size_t i = 0; i < pjtop; i++) free(projects[i].name);

   free(projects);

   return status;
}