#include "sql_runner.h"

#include "csv.h"
#include "gc.h"
#include "str.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stmt_type;
char *tables[2];
char *equi_id[2];
char *equi_tables[2];
ast *ast_root;
clq *clq_head;
int int_compare(int val3, int val4, int operation);
int str_compare(char *val1, char *val2, int operation);
int get_header_index(char **headerFields, int nh, char *str);
int match_on(char **headerFields, char **rowFields, int nh, int nr, ast *root);
void rev_clq();
int ast_ok(char **headerFields, int nh, ast *root);

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

void rev_clq() {
	clq *current = clq_head;
	clq *prev = NULL, *next = NULL;

	while(current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	clq_head = prev;
}

ast *new_ast_node() {
	ast *ret = (ast *)gc_malloc(sizeof(ast));
	memset(ret, 0, sizeof(ast));		// zero bomb all fields in ret
	return ret;
}

clq *new_clq_node() {
	clq *ret = (clq *)gc_malloc(sizeof(clq));
	memset(ret, 0, sizeof(clq));
	return ret;
}

int get_header_index(char **headerFields, int nh, char *str) {
	for(int i = 0; i < nh; i++)
		if(!strcmp(headerFields[i], str))
			return i;
	return -1;
}

void run_sql(void) {
	switch(stmt_type) {
		case E_SELECT: run_select(); break;
		case E_PROJECT: run_project(); break;
		case E_CARTPROD: run_cartprod(); break;
		case E_EQUIJOIN: run_equijoin(); break;
		default: break;
	}
	gc_collect();
}

void run_project(void) {
	int query_count = 0;
	char *tablename = str_concat(tables[0], ".csv");
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	int nh = CsvParser_getNumFields(header);
	int *headers_arr = (int *)gc_malloc(sizeof(int) * nh);
	memset(headers_arr, 0, sizeof(int) * nh);
	int c = 0;
	int c2 = -1;
	rev_clq();
	clq *temp = clq_head;
	while(temp != NULL) {
		c2++;
		int index = get_header_index(headerFields, nh, temp->str);
		if(index == -1) {
			printf("Column %s not found for projection\n", temp->str);
			// free(headers_arr);
			CsvParser_destroy(csvparser);
			return;
		}
		if(headers_arr[index] < nh) {
			headers_arr[c] += index;
			headers_arr[index] += nh;
			c++;
		} else {
			printf("[WARN]Duplicate fields in project, skipping %s(#%d)\n", temp->str, c2);
		}
		temp = temp->next;
	}

	for(int i = 0; i < c; i++)
		printf("%s\t\t", headerFields[headers_arr[i] % nh]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		for(int i = 0; i < c; i++) {
			query_count++;
			printf("%s\t\t", rowFields[headers_arr[i] % nh]);
		}
		printf("\n");
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	// free(headers_arr);
	// free_clq(clq_head);
	printf("%d rows displayed\n", query_count);
}

void run_cartprod(void) {
	int query_count = 0;
	char *tablename1 = str_concat(tables[0], ".csv");
	char *tablename2 = str_concat(tables[1], ".csv");
	CsvParser *csvparser1 = CsvParser_new(tablename1);
	CsvRow *row1;
	CsvRow *header1 = CsvParser_getHeader(csvparser1);
	CsvParser *temp_csvparser2 = CsvParser_new(tablename2);
	CsvRow *temp_header2 = CsvParser_getHeader(temp_csvparser2);
	if(header1 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser1));
		return;
	}
	if(temp_header2 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(temp_csvparser2));
		return;
	}
	char **headerFields1 = CsvParser_getFields(header1);
	char **headerFields2 = CsvParser_getFields(temp_header2);
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		printf("%s.%s\t\t", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s\t\t", tables[1], headerFields2[i]);
	printf("\n");
	CsvParser_destroy(temp_csvparser2);

	while((row1 = CsvParser_getRow(csvparser1))) {
		char **rowFields1 = CsvParser_getFields(row1);
		// printf("%s\t\t", rowFields[i]);
		CsvParser *csvparser2 = CsvParser_new(tablename2);
		CsvRow *row2;
		CsvRow *header2 = CsvParser_getHeader(csvparser2);

		if(header2 == NULL) {
			printf("%s\n", CsvParser_getErrorMessage(csvparser2));
			CsvParser_destroy_row(row1);
			CsvParser_destroy(csvparser1);
			return;
		}
		while((row2 = CsvParser_getRow(csvparser2))) {
			char **rowFields2 = CsvParser_getFields(row2);
			query_count++;
			for(int j = 0; j < CsvParser_getNumFields(row1); j++)
				printf("%s\t\t", rowFields1[j]);
			for(int j = 0; j < CsvParser_getNumFields(row2); j++)
				printf("%s\t\t", rowFields2[j]);
			printf("\n");
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("%d rows displayed\n", query_count);
}

void run_equijoin(void) {
	int query_count = 0;
	char *tablename1, *tablename2;
	int ok = 0;
	if(strcmp(tables[0], equi_tables[0]) == 0 && strcmp(tables[1], equi_tables[1]) == 0)
		ok = 1;
	if(strcmp(tables[1], equi_tables[0]) == 0 && strcmp(tables[0], equi_tables[1]) == 0) {
		char *temp;

		temp = equi_tables[0];
		equi_tables[0] = equi_tables[1];
		equi_tables[1] = temp;

		temp = equi_id[0];
		equi_id[0] = equi_id[1];
		equi_id[1] = temp;

		ok = 1;
	}
	if(!ok) {
		printf("EquiJoin condition error\n");
		return;
	}
	tablename1 = str_concat(tables[0], ".csv");
	tablename2 = str_concat(tables[1], ".csv");
	CsvParser *csvparser1 = CsvParser_new(tablename1);
	CsvRow *row1;
	CsvRow *header1 = CsvParser_getHeader(csvparser1);
	CsvParser *temp_csvparser2 = CsvParser_new(tablename2);
	CsvRow *temp_header2 = CsvParser_getHeader(temp_csvparser2);
	if(header1 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser1));
		return;
	}
	if(temp_header2 == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(temp_csvparser2));
		return;
	}
	char **headerFields1 = CsvParser_getFields(header1);
	char **headerFields2 = CsvParser_getFields(temp_header2);
	int h1 = -1;
	int h2 = -1;
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		if(!strcmp(headerFields1[i], equi_id[0]))
			h1 = i;

	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		if(!strcmp(headerFields2[i], equi_id[1]))
			h2 = i;
	if(h1 == -1 || h2 == -1) {
		printf("EQUIJOIN columns wrong in condition\n");
		return;
	}
	for(int i = 0; i < CsvParser_getNumFields(header1); i++)
		printf("%s.%s\t\t", tables[0], headerFields1[i]);
	for(int i = 0; i < CsvParser_getNumFields(temp_header2); i++)
		printf("%s.%s\t\t", tables[1], headerFields2[i]);
	printf("\n");
	CsvParser_destroy(temp_csvparser2);

	while((row1 = CsvParser_getRow(csvparser1))) {
		char **rowFields1 = CsvParser_getFields(row1);
		CsvParser *csvparser2 = CsvParser_new(tablename2);
		CsvRow *row2;
		CsvRow *header2 = CsvParser_getHeader(csvparser2);

		if(header2 == NULL) {
			printf("%s\n", CsvParser_getErrorMessage(csvparser2));
			CsvParser_destroy_row(row1);
			CsvParser_destroy(csvparser1);
			return;
		}
		while((row2 = CsvParser_getRow(csvparser2))) {
			char **rowFields2 = CsvParser_getFields(row2);
			if(!strcmp(rowFields1[h1], rowFields2[h2])) {
				query_count++;
				for(int j = 0; j < CsvParser_getNumFields(row1); j++)
					printf("%s\t\t", rowFields1[j]);
				for(int j = 0; j < CsvParser_getNumFields(row2); j++)
					printf("%s\t\t", rowFields2[j]);
				printf("\n");
			}
			CsvParser_destroy_row(row2);
		}
		CsvParser_destroy(csvparser2);
		CsvParser_destroy_row(row1);
	}
	CsvParser_destroy(csvparser1);
	printf("%d rows displayed\n", query_count);
}

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

	if(root->operand_type[0] == E_STR && root->operand_type[1] == E_INT) {
		printf("[WARN]String to int comparision, returning false\n");
		return 0;
	}
	if(root->operand_type[0] == E_INT && root->operand_type[1] == E_STR) {
		printf("[WARN]String to int comparision, returning false\n");
		return 0;
	}
	if(root->operation != E_LT && root->operation != E_LTEQ && root->operation != E_GT && root->operation != E_GTEQ &&
	   root->operation != E_EQ && root->operation != E_NEQ)
		printf("Unknown operator %s\n", E_TO_STR[root->operation]);
	char *val1, *val2;
	int val3, val4;
	int is_int_comparision = 0;
	if(root->operand_type[0] == E_INT || root->operand_type[1] == E_INT)
		is_int_comparision = 1;
	// WARNING: var to  var comparisions are str by default
	if(root->operand_type[0] == E_STR) {
		val1 = root->str[0];
	} else if(root->operand_type[0] == E_INT) {
		val3 = root->num[0];
	} else {
		int index = get_header_index(headerFields, nh, root->str[0]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[0]);
			return 0;
		}
		if(is_int_comparision)
			val3 = atoi(rowFields[index]);
		else
			val1 = rowFields[index];
	}

	if(root->operand_type[1] == E_STR) {
		val2 = root->str[1];
	} else if(root->operand_type[1] == E_INT) {
		val4 = root->num[1];
	} else {
		int index = get_header_index(headerFields, nh, root->str[1]);
		if(index == -1) {
			printf("[WARN]No column by name %s, returning false\n", root->str[1]);
			return 0;
		}
		if(is_int_comparision)
			val4 = atoi(rowFields[index]);
		else
			val2 = rowFields[index];
	}
	if(is_int_comparision)
		return int_compare(val3, val4, root->operation);
	return str_compare(val1, val2, root->operation);
}

void run_select(void) {
	int query_count = 0;
	char *tablename = str_concat(tables[0], ".csv");
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	if(!ast_ok(headerFields, CsvParser_getNumFields(header), ast_root))
		return;
	for(int i = 0; i < CsvParser_getNumFields(header); i++)
		printf("%s\t\t", headerFields[i]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		int res = -1;
		res = match_on(headerFields, rowFields, CsvParser_getNumFields(header), CsvParser_getNumFields(row), ast_root);
		if(res == 1) {
			query_count++;
			for(int i = 0; i < CsvParser_getNumFields(row); i++) {
				printf("%s\t\t", rowFields[i]);
			}
			printf("\n");
		}
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	// free_ast(ast_root);
	printf("%d rows displayed\n", query_count);
}

int int_compare(int val3, int val4, int operation) {
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

// void free_ast(ast *root) {
// 	if(root->operation == E_OR || root->operation == E_AND || root->operation == E_NOT) {
// 		if(root->operation != E_NOT)
// 			free_ast(root->child[1]);
// 		free_ast(root->child[0]);
// 	}
// 	// free(root);
// }

// void free_clq(clq *head) {
// 	clq *temp = head;
// 	while(temp != NULL) {
// 		head = head->next;
// 		// free(temp);
// 		temp = head;
// 	}
// }