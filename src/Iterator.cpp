#include "Iterator.h"




template<class T>
Iterator<T>::Iterator(Node<T>* contr)
{
    currents.push_back(make_pair(contr,0));
}

template<class T>
void Iterator<T>::operator ++()
{
    if(currents[currents.size()-1].first->connections.size()>currents[currents.size()-1].second)
    {
        if(element(currents, currents[currents.size()-1].first->connections[currents[currents.size()-1].second].second))
        {
            if(currents[currents.size()-1].first->connections.size()>currents[currents.size()-1].second+1)
            {
                currents[currents.size()-1].second++;
                currents.push_back(make_pair(currents[currents.size()-1].first->connections[currents[currents.size()-1].second].second,0));
            }
            else
            {
                if(currents.size()==1)
                {
                    currents.pop_back();
                    currents.push_back(make_pair(nullptr,0));
                }
                else
                {
                    currents.pop_back();
                    currents[currents.size()-1].second++;
                }
            }
        }
        else
        {
            currents.push_back(make_pair(currents[currents.size()-1].first->connections[currents[currents.size()-1].second].second,0));
        }
    }
    else
    {
        if(currents.size()==1)
        {
            currents.pop_back();
            currents.push_back(make_pair(nullptr,0));
        }
        else
        {
            currents.pop_back();
            currents[currents.size()-1].second++;
        }
    }
}

template<class T>
T Iterator<T>::operator*()
{
    if(currents.size()>1)
    {
        return currents[currents.size()-2].first->connections[currents[currents.size()-2].second].first;
    }
}

template<class T>
bool Iterator<T>::operator == (const Iterator& a)
{
    return this->currents[0].first==a.currents[0].first;
}

template<class T>
bool Iterator<T>::operator != (const Iterator& a)
{
    return this->currents[0].first!=a.currents[0].first;
}

template<class T>
bool Iterator<T>:: element(const vector<pair<Node<T>*,int>> a,const Node<T>* c)
{
    for(int i=0; i<a.size(); i++)
    {
        if(a[i].first==c)
        {
            return true;
        }
    }
    return false;
}
