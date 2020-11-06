

//главната функция за строене на автомат
//взема израз,гледа дали може да се разбие на подизрази, разбива го, за всеки под израз прави същото и така докато не се стигне до нещо по-просто, което веднага да бъде построено
//функцията поема вектор където се записват вс финални състояния, след края на всяко от тях се казва че е финално
template<class T>
void Automa<T>::to_automa_help(string izraz,Node<T>* lst,vector<Node<T>*>& result)
{
    if(izraz=="")
    {
        result.push_back(lst);
    }
    else if(izraz=="@")
    {
        result.push_back(lst);
    }
    else if(izraz[0]=='.')
    {
        to_automa_help(izraz.erase(0,1),lst,result);
    }
    else if(should_split(izraz)==0)
    {
        if(izraz.size()>1)
        {
            if(izraz[1]=='*')
            {
                string s="";
                s+=izraz[0];
                lst->build_cycle(s);
                to_automa_help(izraz.erase(0,2),lst,result);
                return;
            }
            else if(izraz[0]=='@')
            {
                string s=izraz;
                s.erase(0,1);
                to_automa_help(s,lst,result);
                return;
            }
            string s=izraz;
            s.erase(0,1);
            lst->add_node(izraz[0],0);
            lst=lst->get_node(izraz[0]);
            to_automa_help(s,lst,result);
        }
        else
        {
            string s=izraz;
            s.erase(0,1);
            lst->add_node(izraz[0],0);
            lst=lst->get_node(izraz[0]);
            to_automa_help(s,lst,result);
        }
    }
    else
    {
        vector<string>podizrazi;
        split(izraz,podizrazi);
        for(int i=0; i<podizrazi.size(); i++)
        {
            if(podizrazi[i][0]=='+')
            {
                podizrazi[i].erase(0,1);
            }
            string before="";
            string inner="";
            string after="";

            devide(podizrazi[i],before,inner,after);
            Node<T>*last=lst;
            for(int j=0; j<before.size(); j++)
            {
                if(before[j]=='@'&&before.size()==1)
                {
                    result.push_back(last);
                    continue;
                }
                else if(before[j]=='@'&&before.size()!=1)
                {
                    continue;
                }
                if(j+1<before.size())
                {
                    if(before[j+1]=='*')
                    {
                        string gg="";
                        gg+=before[j];
                        last->build_cycle(gg);
                        j++;
                        continue;
                    }
                    last->add_node(before[j],0);
                    last=last->get_node(before[j]);
                }
                else
                {
                    last->add_node(before[j],0);
                    last=last->get_node(before[j]);
                }
            }
            vector<Node<T>*>ss;
            to_automa_help(inner,last,ss);
            for(int i=0; i<ss.size(); i++)
            {
                if(after.size()>0&&after[0]=='*')
                {
                    ss[i]->connections.push_back(make_pair('@',last));
                }
                else
                {
                    to_automa_help(after,ss[i],result);
                }
            }
            if(after.size()>0&&after[0]=='*')
            {
                after.erase(0,1);
                to_automa_help(after,last,result);
            }
        }
    }

}

//изтрива целия автомат
template<class T>
void Automa<T>::delete_automa()
{
    if(start!=nullptr)
    {
        vector<Node<T>*>del;
        start->get_all_nodes(del);
        for(int i=0; i<del.size(); i++)
        {
            delete del[i];
        }
        start=nullptr;
    }
    else
    {
        return;
    }
}

//взема израз проверява дали е правилен и го подава на главната функция за строене
template<class T>
void Automa<T>::to_automa(string izraz)
{
    if(start!=nullptr)
    {
        delete_automa();
    }
    if(izraz=="@")
    {
        this->add_node("",' ',1);
    }
    else if(izraz=="")
    {
        this->add_node("",' ',0);
    }
    else if(is_proper_expr(izraz))
    {
        vector<Node<T>*>c;
        this->add_node("",' ',0);
        clear_dot(izraz);
        to_automa_help(izraz,start,c);
        for(int i=0; i<c.size(); i++)
        {
            c[i]->final=true;
        }
    }
    else
    {
        cout<<"Something went wrong"<<endl;
    }
}

//чете файл ред по ред и казва кои редове се приемат от автомата
template<class T>
void Automa<T>::read(string file_name)
{
    string line;
    ifstream file(file_name);
    if (file.is_open())
    {
        cout<<"Accepted lines:"<<endl;
        while(getline(file,line))
        {
            if(this->recognise(line))
            {
                cout<<line<<endl;
            }
        }
        file.close();
    }
}

//прави допълнение на автомат
template<class T>
void Automa<T>::completion()
{
    vector<Node<T>*>all;
    start->get_all_nodes(all);
    for(int i=0; i<all.size(); i++)
    {
        if(all[i]->final==1)
        {
            all[i]->final=0;
        }
        else
        {
            all[i]->final=1;
        }
    }
}

//бета версия на това да превърне автомат към низ
template<class T>
void Automa<T>::to_izraz()
{
    if(this->start!=nullptr)
    {
        vector<Node<T>*>past_nodes;
        vector<Node<T>*>brackets;
        vector<string> result;
        start->to_izraz_help(result,past_nodes,brackets);

        for(int i=0; i<result.size(); i++)
        {
            prettyfy(result[i]);
            if(result[i]=="")
            {
                result[i]="@";
            }
            cout<<result[i];
            if(i!=result.size()-1)
            {
                cout<<" + ";
            }
        }
        cout<<endl;
    }
}

//казва какъв е езика на даден автомат
template<class T>
void Automa<T>::check_language()
{
    if(start==nullptr)
    {
        cout<<"Empty"<<endl;
    }
    else
    {
        vector<pair<bool,Node<T>*>>nodes;
        start->get_all_nodes_special(nodes,0);

        int counter=0;
        bool pulen=true;
        bool kraen=true;
        for(int i=0; i<nodes.size(); i++)
        {
            //cout<<nodes[i].first;
            if(nodes[i].second->final==false)
            {
                counter++;
                pulen=false;
            }
            if(nodes[i].second->final==true&&nodes[i].first==true)
            {
                kraen=false;
            }
        }
        if(counter==nodes.size())
        {
            cout<<"Prazen"<<endl;
        }
        else if(pulen==true)
        {
            cout<<"Pulen"<<endl;
        }
        else if(kraen==true)
        {
            cout<<"Kraen"<<endl;
        }
        else
        {
            cout<<"Neither"<<endl;
        }
    }
}
