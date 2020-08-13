#ifndef H_MANUAL
#define H_MANUAL

#include "../config.h"

#define VERSION "0.5.4"

#define MANUAL \
   "                           ╔═════════════════════════╗\n" \
   " ╔═════════════════════════╣ Project Manager (PMang) ╠═════════════════════════╗\n" \
   " ║                         ╚═════════════════════════╝                         ║\n" \
   " ║ Version: " VERSION "                                                              ║\n" \
   " ║                                                                             ║\n" \
   " ║ Usage: " ALIAS_NAME " <cmd> <args...>                                                ║\n" \
   " ║                                                                             ║\n" \
   " ║ Status:                                                                     ║\n" \
   " ║   "C_NON"0 - Idea "C_RST"                                                                 ║\n" \
   " ║   "C_LOW"1 - Low "C_RST"                                                                  ║\n" \
   " ║   "C_MED"2 - Medium "C_RST"                                                               ║\n" \
   " ║   "C_HIG"3 - High "C_RST"                                                                 ║\n" \
   " ║   "C_CRT"4 - Very High "C_RST"                                                            ║\n" \
   " ╠══════════════╦══════════════════════════════════════════════════════════════╣\n" \
   " ║ \033[32madd\033[0m     [a]  ║ Adds a new project.                                          ║\n" \
   " ║ \033[32mremove\033[0m  [r]  ║ Removes a project regardless of it's status.                 ║\n" \
   " ║ \033[32mpromote\033[0m [p]  ║ Increases project priority.                                  ║\n" \
   " ║ \033[32mdemote\033[0m  [d]  ║ Decreases project priority.                                  ║\n" \
   " ║ \033[32msetcurr\033[0m [sc] ║ Sets the current task.                                       ║\n" \
   " ║ \033[32mrmcurr\033[0m  [rc] ║ Unsets current task.                                         ║\n" \
   " ║ \033[32mcurrent\033[0m [cr] ║ Displays the current task.                                   ║\n" \
   " ║ \033[32mrename\033[0m  [rn] ║ Rename a project.                                            ║\n" \
   " ║ \033[32mlist\033[0m    [ls] ║ Lists all projects.                                          ║\n" \
   " ║ \033[32mllist\033[0m   [ll] ║ List all projects in formatted chart.                        ║\n" \
   " ║ \033[32mget\033[0m     [g]  ║ Shows status of a single project.                            ║\n" \
   " ║ \033[32mclear\033[0m   [c]  ║ Clears all projects.                                         ║\n" \
   " ║ \033[32mversion\033[0m [v]  ║ Shows version of the program.                                ║\n" \
   " ║ \033[32mhelp\033[0m    [h]  ║ Shows this menu.                                             ║\n" \
   " ╚══════════════╩══════════════════════════════════════════════════════════════╝"
#endif