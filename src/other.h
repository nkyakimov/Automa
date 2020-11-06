#ifndef OTHER_H_INCLUDED
#define OTHER_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;


void clear_dot(string& c);
void split(const string izraz,vector<string>& sub_izraz);
bool should_split(const string s);
void devide(const string all,string& before,string& inner,string& after);
void prettyfy(string& c);
bool is_proper_expr(const string exp);




#endif // OTHER_H_INCLUDED
