#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config.h"
#include "../lib/info.h"
#include "../lib/errmgr.h"

#define MAN_PATH INSTALL_PATH "/lib/manual.h"

int main(int argc, char** argv) {

   char entries[][3][51] = {
   {CMD_ADD,      CMD_ADD_A,    "Adds a new project."},
   {CMD_REM,      CMD_REM_A,    "Removes a project regardless of the status."},
   {CMD_PRM,      CMD_PRM_A,    "Increases project priority."},
   {CMD_DMT,      CMD_DMT_A,    "Decreases project priority."},
   {CMD_SCR,      CMD_SCR_A,    "Sets the current task."},
   {CMD_RCR,      CMD_RCR_A,    "Removes the current task."},
   {CMD_CUR,      CMD_CUR_A,    "Displays current task."},
   {CMD_RNM,      CMD_RNM_A,    "Renames a project."},
   {CMD_LST,      CMD_LST_A,    "Lists all projects."},
   {CMD_LLT,      CMD_LLT_A,    "Lists all projects in formatted chart."},
   {CMD_GET,      CMD_GET_A,    "Fetches status of projects."},
   {CMD_CLR,      CMD_CLR_A,    "Clears project list."},
   {CMD_RBD,      CMD_RBD_A,    "Rebuilds binary."},
   {CMD_VER,      CMD_VER_A,    "Displays version of program."},
   {CMD_HLP,      CMD_HLP_A,    "Displays this menu."},
   };

   int vdist = 67 - (int)strlen(VERSION);
   if (vdist < 0) {
      print_err(E_ERR, "[BUILD] Cannot generate manual. Version string too long.");
      return 1;
   }

   int adist = 53 - (int)strlen(ALIAS_NAME);
   if (adist < 0) {
      print_err(E_ERR, "[BUILD] Cannot generate manual. Alias string too long.");
      return 1;
   }

   FILE* file = fopen(MAN_PATH, "w");
   fprintf(file, "#ifndef H_MANUAL\n");
   fprintf(file, "#define H_MANUAL\n\n");
   fprintf(file, "#include \"../config.h\"\n");
   fprintf(file, "#include \"../lib/info.h\"\n\n");
   fprintf(file, "#define MANUAL \\\n");
   fprintf(file, "\"                          ╔═════════════════════════╗\\n\" \\\n");
   fprintf(file, "\"╔═════════════════════════╣ Project Manager (PMang) ╠═════════════════════════╗\\n\" \\\n");
   fprintf(file, "\"║                         ╚═════════════════════════╝                         ║\\n\" \\\n");
   fprintf(file, "\"║ Version: \" VERSION \"\%*c║\\n\" \\\n", vdist, ' ');
   fprintf(file, "\"║                                                                             ║\\n\" \\\n");
   fprintf(file, "\"║ Usage: \" ALIAS_NAME \" <cmd> <args...>%*c║\\n\" \\\n", adist, ' ');
   fprintf(file, "\"║                                                                             ║\\n\" \\\n");
   fprintf(file, "\"║ Status:                                                                     ║\\n\" \\\n");
   fprintf(file, "\"║ \" C_NON \"0 - Idea\" C_RST \"                                                                    ║\\n\" \\\n");
   fprintf(file, "\"║ \" C_LOW \"1 - Low\" C_RST \"                                                                     ║\\n\" \\\n");
   fprintf(file, "\"║ \" C_MED \"2 - Medium\" C_RST \"                                                                  ║\\n\" \\\n");
   fprintf(file, "\"║ \" C_HIG \"3 - High\" C_RST \"                                                                    ║\\n\" \\\n");
   fprintf(file, "\"║ \" C_CRT \"4 - Very High\" C_RST \"                                                               ║\\n\" \\\n");
   fprintf(file, "\"╠══════════════╦══════════════════════════════════════════════════════════════╣\\n\" \\\n");
   
   size_t size = sizeof(entries) / sizeof(entries[0]);

   for (size_t i = 0; i < size; i++) {

      int name_dist = 8 - (int)strlen(entries[i][0]);
      int abbr_dist = 3 - (int)strlen(entries[i][1]);
      int desc_dist = 61 - (int)strlen(entries[i][2]);

      if (name_dist < 0) {
         print_err(E_ERR, "[BUILD] Cannot add entry \"%s\" to manual. Name too long.", entries[i][0]);
         continue;
      }

      if (abbr_dist < 0) {
         print_err(E_ERR, "[BUILD] Cannot add entry \"%s\" to manual. Abbreviation too long.", entries[i][0]);
         continue;
      }

      fprintf(file, "\"║ \\033[32m%s\\033[0m%*c[%s]%*c║ %s%*c║\\n\" \\\n", entries[i][0], name_dist, ' ', entries[i][1], abbr_dist, ' ', entries[i][2], desc_dist, ' ');   
   }
   
   fprintf(file, "\"╚══════════════╩══════════════════════════════════════════════════════════════╝\"\n\n");
   fprintf(file, "#endif");

   fclose(file);

   return 0;
}