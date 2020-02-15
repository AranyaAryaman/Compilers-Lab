#include <bits/stdc++.h>
#include <stdlib.h>
#define True (true)
#define False (false)
using namespace std;
template<class... Args> void print(Args... args) {
	(std::cout << ... << args) << endl;
}
int lines(ifstream &myfile) {
	int number_of_lines = 0;
	string line;
	bool emptyfile = True;
	// while(getline(myfile, line))
	// 	++number_of_lines;
	for(istreambuf_iterator<char> i(myfile), e; i != e; ++i) {
		emptyfile = False;
		if(*i == '\n')
			number_of_lines++;
	}
	if(!emptyfile)
		number_of_lines++;
	return number_of_lines;
}
int comments(ifstream &myfile) {
	string line;
	int number_of_comments = 0;
	bool multi = false;
	bool hascomment = false;
	while(getline(myfile, line)) {
		if(multi &&line.length()==0){
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
int blank(ifstream &myfile) {}
int main(int argc, char *argv[]) {
	ifstream myfile("input.txt");
	cout << "number_of_lines=" << lines(myfile) << endl;
	myfile.seekg(0, myfile.beg);
	cout << "number_of_comments=" << comments(myfile) << endl;
	myfile.seekg(0, myfile.beg);
	cout << "number_of_blank_lines";
	myfile.seekg(0, myfile.beg);
	cout << "number_of_macro_definitions";
	myfile.seekg(0, myfile.beg);
	cout << "number_of_variable_veclarations";
	myfile.seekg(0, myfile.beg);
	cout << "number_of_function_declarations";
	myfile.seekg(0, myfile.beg);
	cout << "number_of_function_definitions";
}
