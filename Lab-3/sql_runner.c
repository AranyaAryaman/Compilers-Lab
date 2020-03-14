#include "sql_runner.h"

#include "csv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int stmt_type;
char tables[2][MAX_STRLEN];
char cols[MAX_COLS][MAX_STRLEN];
int col_num;
conditions cond_list[MAX_CONDS];
int cond_num;
char equi_id[2][MAX_STRLEN];
char equi_tables[2][MAX_STRLEN];
void run_select();
void run_project();
void run_cartprod();
void run_equijoin();

void init_ds() {
	col_num = 0;
	cond_num = 0;
}

void run_sql() {
	switch(stmt_type) {
		case E_SELECT: run_select(); break;
		case E_PROJECT: run_project(); break;
		case E_CARTPROD: run_cartprod(); break;
		case E_EQUIJOIN: run_equijoin(); break;
		default: break;
	}
}

void run_project() {
	char tablename[MAX_STRLEN];
	strcpy(tablename, tables[0]);
	strcat(tablename, ".csv");
	CsvParser *csvparser = CsvParser_new(tablename);
	CsvRow *row;
	CsvRow *header = CsvParser_getHeader(csvparser);

	if(header == NULL) {
		printf("%s\n", CsvParser_getErrorMessage(csvparser));
		return;
	}
	char **headerFields = CsvParser_getFields(header);
	int *headers = (int *)malloc(sizeof(int) * CsvParser_getNumFields(header));
	int c = 0;
	int found = 0;
	for(int j = 0; j < col_num; j++) {
		found = 0;
		for(int i = 0; i < CsvParser_getNumFields(header); i++)
			if(strcmp(cols[j], headerFields[i]) == 0) {
				headers[c++] = i;
				found = 1;
			}
		if(!found) {
			printf("\033[01;31mERROR:\033[00mColumn %s not found for projection\n", cols[j]);
			free(headers);
			CsvParser_destroy(csvparser);
			return;
		}
	}
	for(int i = 0; i < c; i++)
		printf("%s\t\t", headerFields[headers[i]]);
	printf("\n");

	while((row = CsvParser_getRow(csvparser))) {
		char **rowFields = CsvParser_getFields(row);
		for(int i = 0; i < c; i++) {
			printf("%s\t\t", rowFields[headers[i]]);
		}
		printf("\n");
		CsvParser_destroy_row(row);
	}
	CsvParser_destroy(csvparser);
	free(headers);
}

void run_cartprod() {
	char tablename1[MAX_STRLEN], tablename2[MAX_STRLEN];
	strcpy(tablename1, tables[0]);
	strcpy(tablename2, tables[1]);
	strcat(tablename1, ".csv");
	strcat(tablename2, ".csv");
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
}

void run_equijoin() {
	// TODO chek if changes are correct in bison
	char tablename1[MAX_STRLEN], tablename2[MAX_STRLEN];
	int ok = 0;
	if(strcmp(tables[0], equi_tables[0]) == 0 && strcmp(tables[1], equi_tables[1]) == 0)
		ok = 1;
	if(strcmp(tables[1], equi_tables[0]) == 0 && strcmp(tables[0], equi_tables[1]) == 0) {
		char temp[25];

		strcpy(temp, equi_tables[0]);
		strcpy(equi_tables[0], equi_tables[1]);
		strcpy(equi_tables[1], temp);

		strcpy(temp, equi_id[0]);
		strcpy(equi_id[0], equi_id[1]);
		strcpy(equi_id[1], temp);

		ok = 1;
	}
	if(!ok) {
		printf("EquiJoin condition error\n");
		return;
	}
	strcpy(tablename1, tables[0]);
	strcpy(tablename2, tables[1]);
	strcat(tablename1, ".csv");
	strcat(tablename2, ".csv");
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
}
void run_select() {}