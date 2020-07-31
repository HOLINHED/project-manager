#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define P_PATH "./test.dat"
#define P_MAX 500

#define S_NON "\033[0;36m[     ] \033[0m"
#define S_LOW "\033[0;36m[ LOW ] \033[0m"
#define S_MED "\033[0;33m[ MID ] \033[0m"
#define S_HIG "\033[0;31m[ HIGH ]\033[0m"
#define S_CRT "\033[1;31m[ CRIT ]\033[0m"

typedef struct pmjr_proj {
   char* name;
   int status;
   int valid;
} PROJECT;

static int status = 0;

static PROJECT* projects;
static size_t pjtop = 0;

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

   printf("%s %s\n", stat_msg[projects[index].status], pname);
}

void list_projs() {
   for (size_t i = 0; i < pjtop; i++) {
      if (projects[i].valid == 1) get_proj(projects[i].name, i);  
   }
}

void load_projs() {

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

void save_projs() {

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
      printf("Usage: %s <cmd> <pname>\n", *argv);
      return 1;
   }

   projects = malloc(P_MAX * sizeof(PROJECT));
   load_projs();

   if (status != 0) return status;

   if (strcmp(argv[1], "add") == 0) add_proj(argv[2], 0);
   else if (strcmp(argv[1], "remove") == 0) remove_proj(argv[2]);
   else if (strcmp(argv[1], "promote") == 0) promote_proj(argv[2]);
   else if (strcmp(argv[1], "demote") == 0) demote_proj(argv[2]);
   else if (strcmp(argv[1], "get") == 0) get_proj(argv[2], P_MAX + 2);
   else if (strcmp(argv[1], "list") == 0) list_projs();
   else printf("Unrecognized option \"%s\".\n", argv[1]);

   save_projs();

   for (size_t i = 0; i < pjtop; i++) free(projects[i].name);

   free(projects);

   return status;
}