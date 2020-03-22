#include "helpers.h"

#include "sql_runner.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int to_int(char *str, int *ok) {
// 	char *p;
// 	int ret = strtol(str, &p, 10);
// 	if(ok != 0)
// 		*ok = (*p == 0) ? 1 : 0;
// 	return ret;
// }

int match_on(char **headerFields, char **rowFields, int nh, int nr, ast *root) {
	if(root->operation == E_AND)
		return (match_on(headerFields, rowFields, nh, nr, root->child[0]) &&
				match_on(headerFields, rowFields, nh, nr, root->child[1])) ?
				   1 :
				   0;
	if(root->operation == E_OR)
		return (match_on(headerFields, rowFields, nh, nr, root->child[0]) ||
				match_on(headerFields, rowFields, nh, nr, root->child[1])) ?
				   1 :
				   0;
	if(root->operation == E_NOT)
		return match_on(headerFields, rowFields, nh, nr, root->child[0]) ? 0 : 1;
	if(root->operation != E_LT && root->operation != E_LTEQ && root->operation != E_GT && root->operation != E_GTEQ &&
	   root->operation != E_EQ && root->operation != E_NEQ)
		printf("Unknown operator %s\n", E_TO_STR[root->operation]);
	char *val1, *val2;
	double val3, val4;
	if(root->operand_type[0] == E_STR) {
		val1 = root->str[0];
		val3 = atof(root->str[0]);
	} else if(root->operand_type[0] == E_NUM) {
		val3 = root->num[0];
	} else {
		int index = get_header_index(headerFields, nh, root->str[0]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[0]);
			return 0;
		}
		val3 = atof(rowFields[index]);
		val1 = rowFields[index];
	}

	if(root->operand_type[1] == E_STR) {
		val2 = root->str[1];
		val4 = atof(root->str[1]);
	} else if(root->operand_type[1] == E_NUM) {
		val4 = root->num[1];
	} else {
		int index = get_header_index(headerFields, nh, root->str[1]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[1]);
			return 0;
		}
		val4 = atof(rowFields[index]);
		val2 = rowFields[index];
	}
	if(root->operand_type[0] == E_NUM || root->operand_type[1] == E_NUM)
		return num_compare(val3, val4, root->operation);
	return str_compare(val1, val2, root->operation);
}

int ast_ok(char **headerFields, int nh, ast *root) {
	if(root->operation == E_AND)
		return (ast_ok(headerFields, nh, root->child[0]) + ast_ok(headerFields, nh, root->child[1]) == 2) ? 1 : 0;
	if(root->operation == E_OR)
		return (ast_ok(headerFields, nh, root->child[0]) + ast_ok(headerFields, nh, root->child[1]) == 2) ? 1 : 0;
	if(root->operation == E_NOT)
		return ast_ok(headerFields, nh, root->child[0]) ? 1 : 0;
	int ok = 1;
	if(root->operand_type[0] == E_VAR && get_header_index(headerFields, nh, root->str[0]) == -1) {
		printf("[ERRR]No column by name %s\n", root->str[0]);
		ok = 0;
	}

	if(root->operand_type[1] == E_VAR && get_header_index(headerFields, nh, root->str[1]) == -1) {
		printf("[ERRR]No column by name %s\n", root->str[1]);
		ok = 0;
	}
	return ok;
}

int num_compare(double val3, double val4, int operation) {
	if(operation == E_LT)
		return (val3 < val4) ? 1 : 0;
	else if(operation == E_LTEQ)
		return (val3 <= val4) ? 1 : 0;
	else if(operation == E_GT)
		return (val3 > val4) ? 1 : 0;
	else if(operation == E_GTEQ)
		return (val3 >= val4) ? 1 : 0;
	else if(operation == E_EQ)
		return (val3 == val4) ? 1 : 0;
	else if(operation == E_NEQ)
		return (val3 != val4) ? 1 : 0;
}

int str_compare(char *val1, char *val2, int operation) {
	if(operation == E_LT)
		return (strcmp(val1, val2) < 0) ? 1 : 0;
	else if(operation == E_LTEQ)
		return (strcmp(val1, val2) <= 0) ? 1 : 0;
	else if(operation == E_GT)
		return (strcmp(val1, val2) > 0) ? 1 : 0;
	else if(operation == E_GTEQ)
		return (strcmp(val1, val2) >= 0) ? 1 : 0;
	else if(operation == E_EQ)
		return (strcmp(val1, val2) == 0) ? 1 : 0;
	else if(operation == E_NEQ)
		return (strcmp(val1, val2) != 0) ? 1 : 0;
}

int get_header_index(char **headerFields, int nh, char *str) {
	for(int i = 0; i < nh; i++)
		if(!strcmp(headerFields[i], str))
			return i;
	return -1;
}

clq *rev_clq(clq *head) {
	clq *current = head;
	clq *prev = 0, *next = 0;

	while(current != 0) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	head = prev;
	return head;
}