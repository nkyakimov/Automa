#include "Automa.h"
#include "other.h"

template<class T>
//добавя нов възел по подаден път и по буква с която да се свърже, и булева променлива да каже дали е финално състояние
void Automa<T>::add_node(string path,char concetion,bool fin)
{
    if(start==nullptr&&path=="")
    {
        Node<T>* n = new Node<T>;
        n->final=fin;
        start=n;
        return;
    }
    Node<T>* current=start;
    for(size_t i=0; i<path.size(); i++)
    {
        current=current->get_node(path[i]);
        if(current==nullptr)
        {
            return;
        }
    }
    current->add_node(concetion,fin);
}

//принтира автомат като казва накрая колко състояния има и колко са финалните
template<class T>
void Automa<T>::print()
{
    if(start==nullptr)
    {
        cout<<"Nothing to print \n";
        return;
    }
    if(start!=nullptr)
    {
        vector<Node<char>*>printed;
        printed.push_back(start);
        start->print(2,printed);
    }
    vector<Node<T>*>temp;
    start->get_all_nodes(temp);
    int finals=0;
    for(int i=0; i<temp.size(); i++)
    {
        if(temp[i]->final==true)
        {
            finals++;
        }
    }
    cout<<endl<<"# of nodes "<<temp.size()<<" # of final nodes "<<finals<<"\n\n";
}

//принтира автомата като dot файл
template <class T>
void Automa<T>::print_dot(string name)
{
    ofstream myfile(name);
    if (myfile.is_open())
    {
        myfile << "digraph G {";
        if(start!=nullptr)
        {
            vector<Node<char>*>printed;
            start->print_dot(printed,myfile);
        }
        myfile << "}";
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }

    string c=name;
    ofstream convert("convert_"+name.erase(name.size()-4,name.size())+".cmd");
    if (convert.is_open())
    {
        convert <<"@echo off \n";
        convert<<"cd C:\\Users\\Nick\\Desktop\\PROEKT AUTOMA\\automa \ndot -Tpdf ";
        convert<<c;
        convert<<" -o "<<name<<".pdf";
        convert.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

//казва дали дадена дума е разпозната от автомата
template<class T>
bool Automa<T>::recognise(string a)
{
    return start->recognise(a);
}

//добавя цикъл към автомата като path посочва от къде да почва, а cycle е самия път на цикъла
template<class T>
void Automa<T>::add_cycle(string path,string cycle)
{
    start->get_node(path)->build_cycle(cycle);
}

//прави копие на автомат и връща началото
template<class T>
Node<T>* Automa<T>::node_copy()const
{
    vector<Node<T>*>all;
    vector<Node<T>*>old;
    this->start->copy_nodes(all,old);
    return all[0];
}

//прави копие на двата автомата, след което създава новия който е тяхното обединение,като към новия автомат прави @ преходи кум началата на другите два
template<class T>
Automa<T>& Automa<T>::operator+(const Automa& t)
{
    Automa<T>* n = new Automa<T>;
    Node<T>* s = new Node<T>;
    s->connections.push_back(make_pair('@',t.node_copy()));
    s->connections.push_back(make_pair('@',this->node_copy()));
    n->start=s;
}
/*
Automa<T>& operator(Automa& t)
{
    this->print();
    t.print();
    vector<Node<T>*>all;
    this->start->get_all_nodes(all);
    for(int i=0; i<all.size(); i++)
    {
        if(all[i]->final==1)
        {
            all[i]->connections.push_back(make_pair('@',t.start));
            cout<<"Transfer"<<endl;
        }
    }
    this->print();
    Automa<T>* n = new Automa<T>;
    n->start=this->start;
}
*/

//прави копеи на двата автомата след което създава тяхната конкатенация като на всяко финално състояние на първия слага един @ преход кум началото на втория
template<class T>
void Automa<T>::concat(Automa& t1,Automa& t2)
{
    Node<T>* start1 = copy_automa(t1);
    Node<T>* start2 = copy_automa(t2);
    vector<Node<T>*>all;
    start1->get_all_nodes(all);
    for(size_t i=0; i<all.size(); i++)
    {
        if(all[i]->final==1)
        {
            all[i]->connections.push_back(make_pair('@',start2));
            all[i]->final=false;
        }
    }
    this->start=start1;
}

//връща броя на всички възли
template<class T>
int Automa<T>::size()
{
    vector<Node<T>*>all;
    this->start->get_all_nodes(all);
    return all.size();
}

template<class T>
Automa<T>& Automa<T>::operator=(const Automa<T>& t)
{
    delete_automa();
    this->start=t.start;
}

//копира автомат връх по връх
template<class T>
Node<T>* Automa<T>::copy_automa(Automa& other)
{
    vector<Node<T>*>all;
    vector<Node<T>*>old;
    other.start->copy_nodes(all,old);
    return all[0];
}


template<class T>
void Automa<T>::copy(Automa& other)
{
    this.delete_automa();
    this->start=copy_automa(other);
}

template<class T>
Iterator<T> Automa<T>::begin()
{
    return Iterator<T>(start);
}

template<class T>
Iterator<T> Automa<T>::end()
{
    return Iterator<T>(nullptr);
}





