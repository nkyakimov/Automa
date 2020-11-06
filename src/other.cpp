#include <string>
#include <vector>

#include "other.h"


using namespace std;


//ФУНКЦИЯ КОЯТО ПО ПОДАДЕН string ПРЕМАВА СИМВОЛА ЗА КОНКАТЕНАЦИЯ
void clear_dot(string& c)
{
    for(int i=0; i<c.size(); i++)
    {
        if(c[i]=='.')
        {
            c.erase(i,1);
        }
    }
}

//функция която маха епсолон преходи ако те не са съществени
void prettyfy(string& c)
{
    for(int i=0; i<c.size(); i++)
    {
        if(c.size()>i+1)
        {
            if(c[i]=='@'&&c[i+1]=='*')
            {
                c.erase(i,2);
            }
            else if(c[i]=='@')
            {
                c.erase(i,1);
            }
        }
        if(c[i]=='@'&&c.size()>1)
        {
            c.erase(i,1);
        }
    }
}

//тази функция взема регулярен израз и го разбива на под изрази
void split(const string izraz,vector<string>& sub_izraz)
{
    int skobi=0;
    string to_add="";
    for(int i=0; i<izraz.size(); i++)
    {
        if(izraz[i]=='(')
        {
            skobi++;
            to_add+=izraz[i];
        }
        else if(izraz[i]==')')
        {
            skobi--;
            to_add+=izraz[i];
        }
        else if(izraz[i]=='+'||izraz[i]=='&')
        {
            if(skobi==0)
            {

                if(to_add!="")
                {
                    sub_izraz.push_back(to_add);
                }
                to_add="";
                to_add+=izraz[i];
            }
            else
            {
                to_add+=izraz[i];
            }

        }
        else
        {
            to_add+=izraz[i];
        }
    }
    if(to_add!="")
    {
        sub_izraz.push_back(to_add);
    }


}


// тази функция казва дали регулярен израз има смисъл да се разбива
bool should_split(const string s)
{
    for(int i=0; i<s.size(); i++)
    {
        if(s[i]==')'||s[i]=='('||s[i]=='+'||s[i]=='&')
        {
            return true;
        }
    }
    return false;
}


//тази функция разбива регулярен израз на 3 части  пример:: ab(a+b).(c+g)k -> 1: ab, 2:(a+b) , 3:.(c+g)k
void devide(const string all,string& before,string& inner,string& after)
{
    int skobi=0;
    bool pass=0;
    for(int i=0; i<all.size(); i++)
    {
        if(pass==0)
        {
            if(all[i]=='(')
            {
                if(skobi==0)
                {
                    skobi++;
                    continue;
                }
                skobi++;
                inner+=all[i];
            }
            else if(all[i]==')')
            {
                if(skobi==1)
                {
                    skobi--;
                    pass=true;
                    continue;
                }
                skobi--;
                inner+=all[i];
            }
            else if(skobi==0)
            {
                before+=all[i];
            }
            else
            {
                inner+=all[i];
            }
        }
        if(pass==1)
        {
            after+=all[i];
        }
    }
}

//функция която проверява дали израза е коректен
bool is_proper_expr(const string exp)
{
    int skobi=0;
    for(int i=0; i<exp.size(); i++)
    {
        if(exp[i]=='(')
        {
            skobi++;
        }
        if(exp[i]==')')
        {
            if(exp[i-1]=='+'||exp[i-1]=='.')
            {
                return false;
            }
            skobi--;
        }
        if(skobi<0)
        {
            return false;
        }
    }

    return skobi==0;
}

