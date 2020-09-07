#include <stdio.h>
#include <string.h>

#include "proj_file.h"
#include "errmgr.h"
#include "err_codes.h"
#include "../config.h"

void load(PROJECT* projects, size_t* pjtop, int* status, size_t* p_curr) {

   FILE* file = fopen(P_PATH, "r");

   if (file == NULL) {
      print_err(E_ERR, "[LOAD] Cannot open storage file.");
      print_err(E_NOTE, "Attempting file creation...");
      file = fopen(P_PATH, "w");
      if (file) {
         fprintf(file, "%d\n", P_MAX + 1);
         print_err(E_NOTEC, "Automatic file creation success!");
         fclose(file);
      } else {
         print_err(E_ERR, "Automatic file creation failed.");
         *status = 2;
      }
      return;
   }

   char* cline = NULL;
   size_t len = 0;
   size_t read = 0;
   size_t line = 0;

   while((read = getline(&cline, &len, file)) != EOF) {

      if (line++ == 0) {
         *p_curr = atoi(cline);
         continue;
      }

      char* pname = strtok(cline, " ");
      int pstat = atoi(strtok(NULL, " "));

      PROJECT to_ins;
      to_ins.name = malloc((strlen(pname) + 1) * sizeof(char));
      to_ins.status = pstat;
      to_ins.valid = 1;

      strcpy(to_ins.name, pname);

      projects[*pjtop] = to_ins;
      *pjtop += 1;
   }

   if (cline) free(cline);
   fclose(file);
}

void save(PROJECT* projects, size_t* pjtop, int* status, size_t p_curr) {

   FILE* file = fopen(P_PATH, "w");

   if (file == NULL) {
      print_err(E_ERR, "[SAVE] Cannot open storage file.");
      *status = 4;
      return;
   }

   fprintf(file, "%ld\n", p_curr);

   for (size_t i = 0; i < *pjtop; i++) {
      if (projects[i].valid == 1) 
         fprintf(file, "%s %d\n", projects[i].name, projects[i].status);
   }

   fclose(file);
}