#include <stdio.h>
#include <string.h>

#include "pmang.h"
#include "config.h"
#include "./lib/errmgr.h"
#include "./lib/manual.h"
#include "./lib/err_codes.h"
#include "./lib/proj_file.h"

#define argcmp(x, y, z) strcmp(x, y) == 0 || strcmp(x,z) == 0
#define C_RST "\033[0m"

const static char* stat_msg[] = { S_NON, S_LOW, S_MED, S_HIG, S_CRT };
const static char* stat_clr[] = { C_NON, C_LOW, C_MED, C_HIG, C_CRT };

static int status = 0;

static PROJECT* projects;
static size_t pjtop = 0;
static size_t p_curr = P_MAX + 1;

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

   const char* bar[] = {"#", "######", "###########", "################", "#####################"};
   const int pos = projects[index].status;

   printf("%s%s" C_RST "%*c| %s%s\n", stat_clr[pos], projects[index].name, l_diff, ' ', 
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

int add_proj(int argc, char** argv) {

   if (argc < 1 || argc > 2) return INVALID_ARGS;
   if (pjtop >= P_MAX) return PROJ_LIMIT;
   if (find_idx(argv[0]) != P_MAX + 1) return PROJ_EXISTS;

   const int pstat = argc == 2 ? atoi(argv[1]) : 0;

   if (pstat > 4 || pstat < 0) return ADD_INVALID_STATUS;

   PROJECT to_ins;
   to_ins.name = malloc((strlen(argv[0]) + 1) * sizeof(char));
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

int get(int argc, char** argv) {

   if (argc == 0) return INVALID_ARGS;

   for (int i = 0; i < argc; i++) {
      print_proj(argv[i], P_MAX + 2);
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

   if (argcmp(cmd, "add", "a")) status = add_proj(argc, argv);
   else if (argcmp(cmd, "remove", "r")) status = remove_proj(argc, argv);
   else if (argcmp(cmd, "promote", "p")) status = pd_proj(argc, argv, 0);
   else if (argcmp(cmd, "demote", "d")) status = pd_proj(argc, argv, 1);
   else if (argcmp(cmd, "get", "g")) status = get(argc, argv);
   else if (argcmp(cmd, "list", "ls")) status = list(argc, argv, 0);
   else if (argcmp(cmd, "llist", "ll")) status = list(argc, argv, 1);
   else if (argcmp(cmd, "setcurr", "sc")) status = set_curr(argc, argv);
   else if (argcmp(cmd, "current", "cr")) status = get_curr(argc, argv);
   else if (argcmp(cmd, "rmcurr", "rc")) status = unset_curr(argc, argv);
   else if (argcmp(cmd, "clear", "c")) status = clear(argc, argv);
   else if (argcmp(cmd, "rename", "rn")) status = rename_proj(argc, argv);
   else if (argcmp(cmd, "version", "v")) puts("PMang v" VERSION);
   else if (argcmp(cmd, "help", "h")) puts(MANUAL);
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