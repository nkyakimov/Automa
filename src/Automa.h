#ifndef AUTOMA_H_INCLUDED
#define AUTOMA_H_INCLUDED
#include <vector>
#include <iostream>
#include <string>

#include "Node1.cpp"
#include "Node2.cpp"

#include "Iterator.cpp"





template<class T>
class Automa
{
private:
    Node<T>* start=nullptr;
    void add_node(string path,char concetion,bool fin);
    void add_cycle(string path,string cycle);
    void to_automa_help(string izraz,Node<T>* lst,vector<Node<T>*>&);
    Node<T>*  node_copy()const;
    Node<T>* copy_automa(Automa& other);

public:
    void print();
    bool recognise(string a);
    void print_dot(string name);
    Automa<T>& operator+(const Automa& t);
    void concat(Automa& t1,Automa& t2);
    int size();
    Automa& operator=(const Automa& t);
    void copy(Automa& other);
    void to_automa(string izraz);
    void read(string file_name);
    void completion();
    void delete_automa();
    void to_izraz();
    void check_language();

    Iterator<T> begin();
    Iterator<T> end();

};

#endif // AUTOMA_H_INCLUDED
