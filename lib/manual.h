#ifndef H_MANUAL
#define H_MANUAL

#define VERSION "0.3.5 (Beta) [Rewrite Prep]"

const static char* MANUAL = 
   "=====================================================================\n"
   "Project Manager (PMang)\n\n"
   "Version: " VERSION "\n\n"
   "Usage: pmang <cmd> <?args>\n\n"
   "Status:\n"
   "  0 - Idea\n  1 - Low\n  2 - Medium\n  3 - High\n  4 - Very High\n"
   "=====================================================================\n"
   "\033[32madd\033[0m     (a)  | Adds  a new project with status 0. (Idea)\n"
   "\033[32mremove\033[0m  (r)  | Removes a project regardless of it's status.\n"
   "\033[32mpromote\033[0m (p)  | Increases project priority.\n"
   "\033[32mdemote\033[0m  (d)  | Decreases project priority.\n"
   "\033[32mlist\033[0m    (ls) | Lists all projects.\n"
   "\033[32mllist\033[0m   (ll) | List all projects in formatted chart.\n"
   "\033[32mget\033[0m     (g)  | Shows status of a single project.\n"
   "\033[32mfetch\033[0m   (f)  | Lists all projects above a specified status.\n"
   "\033[32mversion\033[0m (v)  | Shows version of the program.\n"
   "\033[32mhelp\033[0m    (h)  | Shows this menu.\n"
   "====================================================================="
   ;
#endif