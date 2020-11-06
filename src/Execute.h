#ifndef EXECUTE_H_INCLUDED
#define EXECUTE_H_INCLUDED


template<class T>
void operator>>(istream& stn,Automa<T> t)
{
    string n;
    stn>>n;
    if(t.recognise(n))
    {
        cout<<"\nCorrect\n\n";
    }
    else
    {
        cout<<"\nNo\n\n";
    }
}


class Execute{
private:
    Automa<char> str;
public:
    void ex();
};

#endif // EXECUTE_H_INCLUDED
