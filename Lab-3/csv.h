#ifndef _CSV_H_
#define _CSV_H_

#include "csv.h"

#include <stdio.h>

typedef struct CsvRow {
	char **fields_;
	int filed_type;
	int numOfFields_;
} CsvRow;

typedef struct CsvParser {
	char *filePath_;
	char *errMsg_;
	CsvRow *header_;
	FILE *fileHandler_;
	int fromString_;
	char *csvString_;
	int csvStringIter_;
} CsvParser;

// Public
CsvParser *CsvParser_new(char *filePath);
CsvParser *CsvParser_new_from_string(char *csvString);
void CsvParser_destroy(CsvParser *csvParser);
void CsvParser_destroy_row(CsvRow *csvRow);
CsvRow *CsvParser_getHeader(CsvParser *csvParser);
CsvRow *CsvParser_getRow(CsvParser *csvParser);
int CsvParser_getNumFields(CsvRow *csvRow);
char **CsvParser_getFields(CsvRow *csvRow);
char *CsvParser_getErrorMessage(CsvParser *csvParser);

// Private
// CsvRow *_CsvParser_getRow(CsvParser *csvParser);
// void _CsvParser_setErrorMessage(CsvParser *csvParser, char *errorMessage);

#endif