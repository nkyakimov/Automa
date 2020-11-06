#include "Node.h"

//тази функция строи цикъл който започва и свършва в даден връх, като за аргумент взема пътя който ще е цикъла
template<class T>
void Node<T>::build_cycle(string abc)
{
    if(this==nullptr)
    {
        return;
    }
    Node<T>* curr=this->build_cycle_help(abc);
    curr->connections.push_back(make_pair(abc[abc.size()-1],this));
}

//по подадено изречение тази функция връща върха след тази буква пример::[q1]-a->[q2]  get_node("a")=>q2
template<class T>
Node<T>* Node<T>::get_node(string a)
{
    if(a.size()==0)
    {
        return this;
    }
    Node<T>* curr=get_node(a[0]);
    if(curr!=nullptr)
    {
        return curr->get_node(a.erase(0,1));
    }
    else
    {
        return nullptr;
    }
}

//тази функция по подадено начало връща всички върхове които са свъразни с началния
template<class T>
void Node<T>::get_all_nodes(vector<Node<T>*>& all)
{
    if(already_printed(all,this)==0)
    {
        all.push_back(this);
        for(int i=0; i<connections.size(); i++)
        {
            connections[i].second->get_all_nodes(all);
        }
    }
    else
    {
        return;
    }
}

//по подаден вектор от върхове и конкретен връх намира на кой индекс е той, ако го няма връща -1
template<class T>
int Node<T>::get_index(vector<Node<T>*>a,Node<T>* b)
{
    for(int i=0; i<a.size(); i++)
    {
        if(a[i]==b)
        {
            return i;
            break;
        }
    }
    return -1;
}


//следващите две функциии правят едно и също но едната връща връх а другата е void
//целта им е по подадено начало да копират цял автомат както си е
//идеята е имам два вектора нови и стари като при извикване стария се пълни с вички минали върхове а новия с техните нови версии, целта на стария е да казва дали по случайност няма цикъл някъде
template<class T>
Node<T>* Node<T>::copy_nodes_help(vector<Node<T>*>&all,vector<Node<T>*>&old)
{
    Node<T>* a = new Node<T>;
    all.push_back(a);
    old.push_back(this);
    if(this->final==1)
    {
        a->final=1;
    }
    for(int i=0; i<this->connections.size(); i++)
    {
        if(already_printed(old,this->connections[i].second)==0)
        {
            a->connections.push_back(make_pair(connections[i].first,this->connections[i].second->copy_nodes_help(all,old)));
        }
        else
        {
            int index=get_index(old,this->connections[i].second);
            a->connections.push_back(make_pair(connections[i].first,all[index]));
        }
    }
    return a;
}

//по подадено начало, тази функция създава копие на съответното дърво, тя поема два вектора като първия служи да върне новите върхове, а втория да гледа дали няма цикъл.
template<class T>
void Node<T>::copy_nodes(vector<Node<T>*>&all,vector<Node<T>*>&old)
{
    Node<T>* a = new Node<T>;
    all.push_back(a);
    old.push_back(this);
    if(this->final==1)
    {
        a->final=1;
    }
    for(int i=0; i<this->connections.size(); i++)
    {
        if(already_printed(old,this->connections[i].second)==0)
        {
            a->connections.push_back(make_pair(connections[i].first,this->connections[i].second->copy_nodes_help(all,old)));
        }
        else
        {
            int index=get_index(old,this->connections[i].second);
            a->connections.push_back(make_pair(connections[i].first,all[index]));
        }
    }
}

//бета версия на функция за превръщане на автомат към израз // има по особенни случаи за които не работи
template<class T>
bool Node<T>::to_izraz_help(vector<string>& to_return,vector<Node<T>*> past_nodes,vector<Node<T>*>& put_brackets)
{
    if(this->connections.size()==0)
    {
        if(this->final==true)
        {
            to_return.push_back("");
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        string put_in_loop;
        int pp=put_brackets.size();
        past_nodes.push_back(this);
        vector<string> backup;
        for(int i=0; i<connections.size(); i++)
        {
            if(is_child(connections[i].second,past_nodes))
            {
                if(connections[i].second==this)
                {
                    string s;
                    s += connections[i].first;
                    s+="*";
                    to_return.push_back(s);
                    //put_brackets.push_back(connections[i].second);

                }
                else if(connections[i].second->final==true)
                {
                    string s;
                    s += connections[i].first;
                    s+=")*";
                    to_return.push_back(s);
                    put_brackets.push_back(connections[i].second);
                }
                else
                {
                    put_in_loop="";
                    put_in_loop += connections[i].first;
                    put_in_loop+="*";
                }
            }
            else if(connections[i].second->to_izraz_help(backup,past_nodes,put_brackets))
            {
                put_in_loop="";
                for(int j=0; j<backup.size(); j++)
                {
                    string s;
                    if(is_child(this,put_brackets))
                    {
                        //cout<<"yes";
                        s+="(";
                    }
                    if(put_in_loop!="")
                    {
                        s+=put_in_loop;
                    }
                    s += connections[i].first;
                    backup[j]=s+backup[j];
                    // cout<<backup[j]<<endl;
                    to_return.push_back(backup[j]);

                }
                //cout<<endl;
                backup.clear();
                put_brackets.erase(put_brackets.begin()+pp,put_brackets.end());
            }
            backup.clear();

        }
        if(this->final)
        {
            to_return.push_back("");
        }
        return to_return.size()>0;
    }
}

//тези три функции , вече ги има дефиниране, с единствената разлика какъв вектор приемат, те са помощни функции за горната
template<class T>
bool Node<T>::already_printed_special(const vector<pair< bool , Node<T>* >>p,const Node<T>* curr)
{
    for(int i=0; i<p.size(); i++)
    {
        if(p[i].second==curr)
        {
            return 1;
            break;
        }
    }
    return 0;
}

template<class T>
int Node<T>::get_index_pair( const vector<pair< bool , Node<T>* >> a,Node<T>* b)
{
    for(int i=0; i<a.size(); i++)
    {
        if(a[i].second==b)
        {
            return i;
            break;
        }
    }
    return -1;
}

template<class T>
void Node<T>::get_all_nodes_special(vector<pair< bool , Node<T>* >>& all,int distance)
{
    if(already_printed_special(all,this)==0)
    {
        all.push_back(make_pair(false,this));
        for(int i=0; i<connections.size(); i++)
        {
            connections[i].second->get_all_nodes_special(all,distance+1);
        }
    }
    else
    {
        for(int i=distance-get_index_pair(all,this)-1;i>0;i--)
        {
            all[all.size()-i].first=true;
        }
        all[get_index_pair(all,this)].first=true;
    }
}
