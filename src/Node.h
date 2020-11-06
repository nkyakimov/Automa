#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

template<class T>
struct Node
{
    bool final=0;
    vector<pair<char,Node<T>*>>connections;

    bool already_printed(const vector<Node<T>*>p,const Node<T>* curr);
    Node<T>* get_node(const char a);
    void get_nodes_with_epsi_or_quest(vector<pair<char,Node<T>*>>&temp,const char a);
    void add_node(const char a,const bool fin);
    void print(int j,vector<Node<T>*>printed);
    void print_dot(vector<Node<T>*>printed,ofstream& myfile);
    bool recognise(string a);
    Node<T>* build_cycle_help(string abc);
    void build_cycle(string abc);
    Node<T>* get_node(string a);
    void get_all_nodes(vector<Node<T>*>& all);
    void get_all_nodes_special(vector<pair<bool,Node<T>*>>& all,int);
    int get_index(vector<Node<T>*>a,Node<T>* b);
    Node<T>* copy_nodes_help(vector<Node<T>*>&all,vector<Node<T>*>&old);
    void copy_nodes(vector<Node<T>*>&all,vector<Node<T>*>&old);
    bool to_izraz_help(vector<string>&,vector<Node<T>*>,vector<Node<T>*>&);
    bool already_printed_special(const vector<pair< bool , Node<T>* >>p,const Node<T>* curr);
    int get_index_pair(const vector<pair< bool , Node<T>* >>,Node<T>* b);
};


#endif // NODE_H_INCLUDED
