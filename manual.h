#ifndef H_MANUAL
#define H_MANUAL

#define VERSION "0.2.0 (BETA)"

const static char* MANUAL = 
   "=====================================================================\n"
   "Version: " VERSION "\n\n"
   "Usage: pmang <cmd> <?args>\n\n"
   "0 - Idea\n1 - Low\n2 - Medium\n3 - High\n4 - Very High\n"
   "=====================================================================\n"
   "\033[32madd\033[0m     | Adds  a new project with status 0. (Idea)\n"
   "\033[32mremove\033[0m  | Removes a project regardless of it's status.\n"
   "\033[32mpromote\033[0m | Increases project priority.\n"
   "\033[32mdemote\033[0m  | Decreases project priority.\n"
   "\033[32mget\033[0m     | Shows status of a single project.\n"
   "\033[32mfetch\033[0m   | Lists all projects above a specified status.\n"
   "\033[32mversion\033[0m | Shows version of the program.\n"
   "\033[32mhelp\033[0m    | Shows this menu.\n"
   "====================================================================="
   ;
#endif