#include <stdlib.h>

#ifndef H_PMANG
#define H_PMANG

typedef struct {
   char* name;
   int status;
   int valid;
} PROJECT;

size_t find_inx(char* pname);

void print_proj(char* pname, size_t idx);
void print_projl(char* pname, size_t idx);
void set_long_short(void);
void sort_projs(void);
size_t find_idx(char*);

int list(int argc, char** argv, int type);
int pd_proj(int argc, char** argv, int type);

int add_proj(int argc, char** argv);
int remove_proj(int argc, char** argv);
int get_proj(int argc, char** argv);
int clear(int argc, char** argv);
int get(int argc, char** argv);
int rename_proj(int argc, char** argv);
int set_curr(int argc, char** argv);
int get_curr(int argc, char** argv);
int unset_curr(int argc, char** argv);

#endif