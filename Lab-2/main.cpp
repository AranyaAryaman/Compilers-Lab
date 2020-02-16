#include <bits/stdc++.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
FILE *fp;
int var_state = 0;
int func_def_state = 0;
int func_dec_state = 0;
int lineCount = 1;
int fdefline = 0;
int fdecline = 0;
int vline = 0;
int vCount = 0, fdefCount = 0, fdecCount = 0;

void skipQuotes(char c)
{
	bool escaped = false;

	while (1)
	{
		c = fgetc(fp);
		if (c == '\\')
		{
			escaped = !escaped;
		}
		else if (c == '"' && escaped)
			continue;
		else if (c == '"' && !escaped)
		{
			break;
		}
		else
			escaped = false;
	}
}

void skipMComment(char c)
{
	while (1)
	{
		c = fgetc(fp);
		if (c == '\n')
		{
			break;
		}
	}
}

void skkipSComment(char c)
{
	while (1)
	{
		c = fgetc(fp);
		if (c == '*')
		{
			c = fgetc(fp);
			if (c == '/')
				break;
		}
		else
			continue;
	}
}

int isDataType(char buffer[])
{
	char datatype[17][100] = {"int", "float", "char", "double", "extern", "long", "const", "void", "short", "auto", "enum", "signed", "static", "unsigned", "FILE", "bool", "string"};
	int i, flag = 0;

	for (i = 0; i < 17; ++i)
	{
		if (strcmp(datatype[i], buffer) == 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

int main2(char* argv)
{
	fp = fopen(argv, "r");
	if (!fp)
	{
		fprintf(stderr, "Cannot open file input.txt\n");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	int count = 0;
	char c = '\0';
	char buffer[100] = {0};
	while ((c = fgetc(fp)) != EOF)
	{
		while (1)
		{
			if (c == ' ' || c == '\t' || c == '\n')
			{
				c = fgetc(fp);
			}
			else
				break;
		}
		if (c == '/')
		{
			c = fgetc(fp);
			if (c == '/')
			{
				skipMComment(c);
				continue;
			}
			if (c == '*')
			{
				skkipSComment(c);
				c = fgetc(fp);
				if (c == '\n')
				{
					continue;
				}
			}
		}
		count = 0;
		while (count < 100)
		{
			buffer[count] = c;
			if (c == '"')
			{
				skipQuotes(c);
				c = fgetc(fp);
			}
			if (c == '\n')
			{
				break;
			}
			c = fgetc(fp);
			count++;
			buffer[count] = '\0';

			if (c == ' ' || c == '\t' || c == '\n' || c == '(' || c == '{' || c == '}' || c == '/' || c == ')')
			{
				if (isDataType(buffer))
				{
					if (c == '\n')
					{
						lineCount++;
					}
					i = 0;
					var_state = 1;
					func_dec_state = 0;
					func_def_state = 1;
					while ((c = fgetc(fp)) != EOF)
					{
						if (c == '/')
						{
							c = fgetc(fp);
							if (c == '/')
							{
								skipMComment(c);
							}
							if (c == '*')
							{
								skkipSComment(c);
								c = fgetc(fp);
							}
						}
						if (c == '"')
						{
							skipQuotes(c);
							c = fgetc(fp);
						}
						if (c == '\n')
						{
							lineCount++;
						}
						if (c == '=' || c == ',')
						{
							while ((c = fgetc(fp)) != ';')
							{
								if (c == '/')
								{
									c = fgetc(fp);
									if (c == '/')
									{
										skipMComment(c);
									}
									if (c == '*')
									{
										skkipSComment(c);
										c = fgetc(fp);
									}
								}
								if (c == '\n')
								{
									lineCount++;
								}
							}
							func_dec_state = 0;
							func_def_state = 0;
						}
						else if (c == '(')
						{
							while ((c = fgetc(fp)) != ')')
							{
								if (c == '/')
								{
									c = fgetc(fp);
									if (c == '/')
									{
										skipMComment(c);
									}
									if (c == '*')
									{
										skkipSComment(c);
										c = fgetc(fp);
									}
								}
								if (c == '\n')
								{
									lineCount++;
								}
								continue;
							}
							func_dec_state = 1;
							var_state = 0;
						}
						else if (c == '{' && func_def_state)
						{
							var_state = 0;
							func_dec_state = 0;
							if (!fdefline && func_def_state)
							{
								fdefline = 1;
								fdefCount = fdefCount + 1;
							}
							break;
						}
						if (c == ';')
						{
							if (func_dec_state && !fdecline)
							{
								fdecline = 1;
								fdecCount = fdecCount + lineCount;
							}
							else if (var_state && !vline)
							{
								vline = 1;
								vCount = vCount + lineCount;
							}
							break;
						}
					}
					var_state = 0;
					func_dec_state = 0;
					func_def_state = 0;
					lineCount = 1;
				}
				count = 0;
				buffer[0] = '\0';
				c = fgetc(fp);
			}
			while (1)
			{
				if (c == ' ' || c == '\t')
				{
					c = fgetc(fp);
				}
				else
					break;
			}
			if (c == '\n')
			{
				break;
			}
		}

		fdefline = 0;
		fdecline = 0;
		vline = 0;
	}
	fclose(fp);
	printf("number of variables=%d\n", vCount);
	printf("number of function declaration=%d\n", fdecCount);
	printf("number of function defination=%d\n", fdefCount);
	return 0;
}
int lines(char *filename) {
	ifstream myfile(filename);
	int number_of_lines = 0;
	string line;
	bool emptyfile = true;
	// while(getline(myfile, line))
	// 	++number_of_lines;
	for(istreambuf_iterator<char> i(myfile), e; i != e; ++i) {
		emptyfile = false;
		if(*i == '\n')
			number_of_lines++;
	}
	if(!emptyfile)
		number_of_lines++;
	return number_of_lines;
}
int comments(char *filename) {
	ifstream myfile(filename);
	string line;
	int number_of_comments = 0;
	bool multi = false;
	bool hascomment = false;
	while(getline(myfile, line)) {
		if(multi && line.length() == 0) {
			number_of_comments++;
		}
		hascomment = false;
		int len = line.length();
		for(int a = 0; a < len - 1; a++) {
			if(!multi) {
				if(line[a] == '/' && line[a + 1] == '/') {
					hascomment = true;
					break;
				} else if(line[a] == '/' && line[a + 1] == '*') {
					multi = true;
					hascomment = true;
					a++;
				}
			} else {
				if(line[a] == '*' && line[a + 1] == '/') {
					// print("here");
					multi = false;
					hascomment = true;
					a++;
				}
			}
		}
		if(hascomment)
			number_of_comments++;
	}
	return number_of_comments;
}
int blank(char *filename) {
	ifstream myfile(filename);
	string line;
	int number_of_blank_lines = 0;
	bool maybe = true;
	for(istreambuf_iterator<char> i(myfile), e; i != e; ++i) {
		if(*i == '\n' && maybe) {
			number_of_blank_lines++;
			maybe = false;
		} else if(*i == '\n')
			maybe = true;
		else
			maybe = false;
	}
	return number_of_blank_lines;
}
int macro(char *filename) {
	ifstream myfile(filename);
	bool multi = false;
	string line;
	int number_of_macro = 0;
	// bool firstchar = true;
	while(getline(myfile, line)) {
		int len = line.length();
		// firstchar = true;
		for(int a = 0; a < len - 1; a++) {
			if(!multi) {
				if(line[a] == '/' && line[a + 1] == '/') {
					break;
				} else if(line[a] == '/' && line[a + 1] == '*') {
					multi = true;
					a++;
				} else if(line[a] == '#') {
					number_of_macro++;
					break;
				} else
					break;

			} else {
				if(line[a] == '*' && line[a + 1] == '/') {
					multi = false;
					a++;
				}
			}
		}
	}
	return number_of_macro;
}
const char *data_type[] = {"int", "char", "extern"};
int variable(char *filename) {
	ifstream myfile(filename);
	int number_of_variables = 0;
	bool multi = false;
	bool macro = false;
	string line;
	while(getline(myfile, line)) {
		int len = line.length();
		for(int a = 0; a < len - 1; a++) {
			if(!multi) {
				if(line[a] == '/' && line[a + 1] == '/') {
					break;
				} else if(line[a] == '/' && line[a + 1] == '*') {
					multi = true;
					a++;
				} else {
				}
			} else {
				if(line[a] == '*' && line[a + 1] == '/') {
					multi = false;
					a++;
				}
			}
		}
	}
	return number_of_variables;
}
int main(int argc, char *argv[]) {
	char *filename = "input.txt";
	if(argc == 2)
		filename = argv[1];
	cout << "number_of_lines=" << lines(filename) << endl;
	cout << "number_of_comments=" << comments(filename) << endl;
	cout << "number_of_blank_lines=" << blank(filename) << endl;
	cout << "number_of_macro_definitions=" << macro(filename) << endl;
	main2(filename);
    return 0;
}