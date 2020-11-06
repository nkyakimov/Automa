#include "Node.h"

// казва дали даден връх е дете на друг
template<class T>
bool is_child(Node<T>* node,vector<Node<T>*> nodes)
{
    for(int i=0; i<nodes.size(); i++)
    {
        if(node==nodes[i])
        {
            return true;
        }
    }
    return false;
}

//абсолютно същата, само дето името е по подходящо за работата и, помага ми да разбера дали има цикъл, за да знам да спре да принтира даден път
template<class T>
bool Node<T>::already_printed(const vector<Node<T>*>p,const Node<T>* curr)
{
    for(int i=0; i<p.size(); i++)
    {
        if(p[i]==curr)
        {
            return 1;
            break;
        }
    }
    return 0;
}

//връша съседа на даден връх който е свързан с конкретна бъква, ако не цъшествува връща nullptr
template<class T>
Node<T>* Node<T>::get_node(const char a)
{
    for(size_t i=0; i<connections.size(); i++)
    {
        if(a==connections[i].first)
        {
            return connections[i].second;
            break;
        }
    }
    return nullptr;
}

//връща всички съседи които са свързани с бъква или @ или ? . Използва се предимно в разпознаването на дума
template<class T>
void Node<T>::get_nodes_with_epsi_or_quest(vector<pair<char,Node<T>*>>&temp,const char a)
{
    for(int i=0; i<connections.size(); i++)
    {
        if(connections[i].first=='@')
        {
            temp.push_back(make_pair('@',connections[i].second));
            continue;
        }
        if(connections[i].first=='?'&&a!='@')
        {
            temp.push_back(make_pair('?',connections[i].second));
            continue;
        }
        if(a==connections[i].first&&a!='@')
        {
            temp.push_back(make_pair(a,connections[i].second));
            continue;
        }
    }
}

//добавя към връх нов връх свързани с дадена буква, ако такъв вече не съшествува
template<class T>
void Node<T>::add_node(const char a,const bool fin)
{
    if(get_node(a)==nullptr)
    {
        //||a=='@' към условието беше
        Node<T>* b = new Node<T>;
        b->final=fin;
        connections.push_back(make_pair(a,b));
    }
}

// принтиране на автомат, като се подава вектор в който се пазят миналите върхове и ако случайно се среще някой пак, значи има цикъл
// int j го използвам за индентация и казва колко ' ' да бъдат добавени
template<class T>
void Node<T>::print(int j,vector<Node<T>*>printed)
{
    if(final==1)
    {
        cout<<"[f]";
        j++;
        // тук j расте за да може децата на този връх коитоще са на друг ред да са правилно отдалечени в дясно
    }
    else
    {
        cout<<"[]";
    }
    for(size_t i=0; i<connections.size(); i++)
    {
        if(already_printed(printed,connections[i].second))
        {
            if(i>0)
            {
                cout<<string(j,' ');
            }
            cout<<"--"<<connections[i].first<<"--loop"<<endl;
            continue;
        }
        if(i!=0)
        {
            cout<<string(j,' ');
        }
        cout<<"--"<<connections[i].first<<"--";
        printed.push_back(connections[i].second);
        connections[i].second->print(j+7,printed);
    }
    if(connections.size()==0)
    {
        cout<<endl;
    }
}

// принтира автомат като pdf
template<class T>
void Node<T>::print_dot(vector<Node<T>*> printed, ofstream& myfile)
{
    printed.push_back(this);
    if(this->final==1)
    {
        myfile<<(long long)this<<" [label=\""<<"X"<<"\"];\n";
    }
    else
    {
        myfile<<(long long)this<<" [label=\""<<" "<<"\"];\n";
    }
    for(size_t i=0; i<connections.size(); i++)
    {
        if(already_printed(printed,connections[i].second))
        {
            myfile<<(long long)this<<"->"<<(long long)connections[i].second<<"[label=\""<<connections[i].first<<"\"];\n";
        }
        else
        {
            myfile<<(long long)this<<"->"<<(long long)connections[i].second<<"[label=\""<<connections[i].first<<"\"];\n";
            printed.push_back(connections[i].second);
            connections[i].second->print_dot(printed,myfile);
        }
    }
}


// разпознава дали даден стринг от конкретно начало бива разпознаван от автомата
template<class T>
bool Node<T>::recognise(string a)
{
    if(final==1&&a=="@")
    {
        return 1;
    }
    else if(a.size()>0)
    {
        vector<pair<char,Node<T>*>>temp;
        get_nodes_with_epsi_or_quest(temp,a[0]);
        if(temp.size()==0)
        {
            return 0;
        }
        else
        {
            for(size_t i=0; i<temp.size(); i++)
            {
                if(temp[i].first=='@')
                {
                    if(temp[i].second->recognise(a))
                    {
                        return 1;
                        break;
                    }
                }
                else if(temp[i].first=='?')
                {
                    string n=a;
                    n.erase(0,1);
                    if(temp[i].second->recognise(n))
                    {
                        return 1;
                        break;
                    }
                }
                else
                {
                    string n=a;
                    n.erase(0,1);
                    if(temp[i].second->recognise(n))
                    {
                        return 1;
                        break;
                    }
                }
            }
            return 0;
        }
    }
    else if(final==1)
    {
        return 1;
    }
    else
    {
        vector<pair<char,Node<T>*>>temp;
        get_nodes_with_epsi_or_quest(temp,'@');
        if(temp.size()==0)
        {
            return 0;
        }
        else
        {
            for(size_t i=0; i<temp.size(); i++)
            {
                if(temp[i].first=='@')
                {
                    if(temp[i].second->recognise(a))
                    {
                        return 1;
                        break;
                    }
                }
            }
            return 0;
        }
    }
}

//по даден string създава път, но без да създава последния връх. Тя връща предпоследния и после главната функция ги зашива заедно
template<class T>
Node<T>* Node<T>::build_cycle_help(string abc)
{
    if(abc.size()>1)
    {
        if(get_node(abc[0])!=nullptr)
        {
            string v=abc;
            return get_node(abc[0])->build_cycle_help(v.erase(0,1));
        }
        else
        {
            Node<T>* curr = new Node<T>;
            this->connections.push_back(make_pair(abc[0],curr));
            return curr->build_cycle_help(abc.erase(0,1));
        }
    }
    else
    {
        return this;
    }
}
