#include <bits/stdc++.h>
#include <stdlib.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"
using namespace std;

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
	cout << "number_of_variable_declarations=" << variable(filename) << endl;
	cout << "number_of_function_declarations=" << endl;
	cout << "number_of_function_definitions=" << endl;
}

// data_type	->	name	->	= or ;
//							->	( ... )	->	;
// 										->	{
// ' ', '\t', '\n'
// ';', '}', '*'
//
