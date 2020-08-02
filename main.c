#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "manual.h"
#include "config.h"

typedef struct pmjr_proj {
   char* name;
   int status;
   int valid;
} PROJECT;

static int status = 0;

static PROJECT* projects;
static size_t pjtop = 0;

static size_t longest_name = 0;
static size_t shortest_name = 0;

size_t find_idx(char* pname) {
   for (size_t i = 0; i < pjtop; i++) 
      if (strcmp(projects[i].name, pname) == 0) return i;
   return P_MAX + 1;
}

void add_proj(char* pname, int pstat) {

   if (pjtop >= P_MAX) {
      printf("Project limit has been reached. (%d)\n", P_MAX);
      return;
   }

   if (find_idx(pname) != P_MAX + 1) {
      printf("A project by that name already exists.\n");
      return;
   }

   PROJECT to_ins;
   to_ins.name = malloc((strlen(pname) + 1) * sizeof(char));
   to_ins.status = pstat;
   to_ins.valid = 1;

   strcpy(to_ins.name, pname);

   projects[pjtop++] = to_ins;
}

void remove_proj(char* pname) {
   size_t index = find_idx(pname);

   if (index != P_MAX + 1) {
      projects[index].valid = 0;
   }
}

void promote_proj(char* pname) {

   size_t index = find_idx(pname);

   if (index == P_MAX + 1) {
      printf("Project \"%s\" not found.\n", pname);
      return;
   }

   int new_status = projects[index].status + 1;

   if (new_status > 4) {
      printf("\"%s\" priority is already at the highest.\n", pname);
   } else {
      projects[index].status = new_status;
   }
}

void demote_proj(char* pname) {

   size_t index = find_idx(pname);

   if (index == P_MAX + 1) {
      printf("Project \"%s\" not found.\n", pname);
      return;
   }

   int new_status = projects[index].status - 1;

   if (new_status < 0) {
      printf("\"%s\" priority is already at the lowest.\n", pname);
   } else {
      projects[index].status = new_status;
   }
}

void get_proj(char* pname, size_t idx) {
   
   size_t index = idx;
   if (index == P_MAX + 2) index = find_idx(pname);

   if (index == P_MAX + 1) {
      printf("Project \"%s\" not found.\n", pname);
      return;
   }

   const char* stat_msg[] = {S_NON, S_LOW, S_MED, S_HIG, S_CRT};
   const char* stat_clr[] = {C_NON, C_LOW, C_MED, C_HIG, C_CRT};
   const int pos = projects[index].status;

   printf("%s%s" C_RST " %s\n", stat_clr[pos], stat_msg[pos], pname);
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

void get_projl(char* pname, size_t idx) {

   size_t index = idx;
   if (index == P_MAX + 2) index = find_idx(pname);

   if (index == P_MAX + 1) {
      printf("Project \"%s\" not found.\n", pname);
      return;
   }

   size_t l_diff = longest_name - strlen(projects[index].name) + 1;

   const char* stat_clr[] = {C_NON, C_LOW, C_MED, C_HIG, C_CRT};
   const char* bar[] = {"", "#####", "##########", "###############", "####################"};
   const int pos = projects[index].status;

   printf("%s%s" C_RST "%*c| %s\n", stat_clr[pos], projects[index].name, l_diff, ' ', bar[pos]);
}

void list_projs(int pstat, int ltype) {

   void (*pfunc[2])(char*, size_t) = { get_proj, get_projl };

   for (size_t i = 0; i < pjtop; i++) {
      if (projects[i].valid == 1 && projects[i].status > pstat) {
         (*pfunc[ltype])(projects[i].name, i);
      }
   }
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

void load_projs(void) {

   FILE* file = fopen(P_PATH, "r");

   if (file == NULL) {
      printf("[LOAD] Cannot open storage file.\n");
      status = 2;
      return;
   }

   char* cline = NULL;
   size_t len = 0;
   size_t read = 0;

   while((read = getline(&cline, &len, file)) != EOF) {

      char* pname = strtok(cline, " ");
      int pstat = atoi(strtok(NULL, " "));

      add_proj(pname, pstat);
   }

   if (cline) free(cline);
   fclose(file);
}

void save_projs(void) {

   FILE* file = fopen(P_PATH, "w");

   if (file == NULL) {
      printf("[SAVE] Cannot open storage file.\n");
      status = 4;
      return;
   }

   for (size_t i = 0; i < pjtop; i++) {
      if (projects[i].valid == 1) 
         fprintf(file, "%s %d\n", projects[i].name, projects[i].status);
   }

   fclose(file);
}

int main(int argc, char** argv) {

   if (argc > 3 || argc < 2) {
      printf("Usage: pmang <cmd> <pname>\n", *argv);
      return 1;
   }

   projects = malloc(P_MAX * sizeof(PROJECT));
   load_projs();
   sort_projs();
   set_long_short();

   if (status != 0) return status;

   if (strcmp(argv[1], "add") == 0) add_proj(argv[2], 0);
   else if (strcmp(argv[1], "remove") == 0) remove_proj(argv[2]);
   else if (strcmp(argv[1], "promote") == 0) promote_proj(argv[2]);
   else if (strcmp(argv[1], "demote") == 0) demote_proj(argv[2]);
   else if (strcmp(argv[1], "get") == 0) get_proj(argv[2], P_MAX + 2);
   else if (strcmp(argv[1], "list") == 0 || strcmp(argv[1], "ls") == 0) list_projs(-1, 0);
   else if (strcmp(argv[1], "llist") == 0 || strcmp(argv[1], "ll") == 0) list_projs(-1, 1);
   else if (strcmp(argv[1], "fetch") == 0) list_projs(atoi(argv[2]), 0);
   else if (strcmp(argv[1], "version") == 0) printf("%s\n", VERSION);
   else if (strcmp(argv[1], "help") == 0) printf("%s\n", MANUAL);
   else printf("Unrecognized option \"%s\".\n", argv[1]);

   save_projs();

   for (size_t i = 0; i < pjtop; i++) free(projects[i].name);

   free(projects);

   return status;
}