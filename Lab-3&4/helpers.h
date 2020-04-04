#ifndef _HELPERS_
#define _HELPERS_

#include "helpers.h"
#include "sql_runner.h"

clq *rev_clq(clq *head);
int get_header_index(char **headerFields, int nh, char *str);
int str_compare(char *val1, char *val2, int operation);
int num_compare(double val3, double val4, int operation);
int ast_ok(char **headerFields, int nh, ast *root);
int match_on(char **headerFields, char **rowFields, int nh, int nr, ast *root);

#endif
