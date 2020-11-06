#include "Execute.h"


void Execute::ex()
{
    string command;
start:
    cout<<"Enter command \nif you don't know what is supported enter ?"<<endl;
    cin>>command;
    if(command=="?")
    {
        cout<<"Enter expresion to build automa - build \n"<<
            "Combine two automas from expr - comb \n"<<
            "Concat two automas from expr - conc \n"<<
            "Recognise word - recgn \n"<<
            "Recognise file - recfl \n"<<
            "Inverse Automa - inv\n"<<
            "Print automa as regexp - prntexp\n"<<
            "Print to console - prntcnsl \n"<<
            "Print to file - prntfl \n"<<
            "Check my language - chkln \n"<<
            "To expresion (demo) - toexp\n"<<
            "Exit - ext"<<endl;
        goto start;
    }
    else if(command=="iter")
    {
        for(char x:str)
        {
            cout<<x;
        }
        goto start;
    }
    else if(command=="toexp")
    {
        str.to_izraz();
        goto start;
    }
    else if(command=="build")
    {
        cout<<"Enter expression ";
        string exp;
        cin>>exp;
        str.to_automa(exp);
        goto start;
    }
    else if(command=="chkln")
    {
        str.check_language();
        goto start;
    }
    else if(command=="prntexp")
    {
        str.to_izraz();
        cout<<"\nTo be clear this is not the expr you build me with"<<endl;
        goto start;
    }
    else if(command=="conc")
    {
        cout<<"Enter expression 1 ";
        string exp1;
        cin>>exp1;
        cout<<"Enter expression 2 ";
        string exp2;
        cin>>exp2;
        Automa<char>x;
        x.to_automa(exp1);
        Automa<char>y;
        y.to_automa(exp2);
        str.concat(x,y);
        goto start;
    }
    else if(command=="comb")
    {
        cout<<"Enter expression 1 ";
        string exp1;
        cin>>exp1;
        cout<<"Enter expression 2 ";
        string exp2;
        cin>>exp2;
        Automa<char>x;
        x.to_automa(exp1);
        Automa<char>y;
        y.to_automa(exp2);
        str=x+y;
        goto start;
    }
    else if(command=="recfl")
    {
        cout<<"Enter file name ";
        string exp;
        cin>>exp;
        str.read(exp);
        goto start;
    }
    else if(command=="inv")
    {
        str.completion();
        cout<<"Automa inverted"<<endl;
        goto start;
    }
    else if(command=="recgn")
    {
        cout<<"Enter word to recognise ";
        cin>>str;
        goto start;
    }
    else if(command=="prntcnsl")
    {
        str.print();
        goto start;
    }
    else if(command=="prntfl")
    {
        string name;
        cout<<"Enter file name you want:"<<endl;
        cin>>name;
        string check=name;
        string f=name;
        if(check.erase(0,name.size()-4)!=".dot")
        {
            f=name;
            name+=".dot";
        }
        else
        {
            f.erase(f.size()-4,f.size());
        }
        str.print_dot(name);
        cout<<"There are 2 new files:"<<endl;
        cout<<"1. "<<name<<endl;
        cout<<"2. converter_"<<name.erase(name.size()-4,name.size())<<".cmd"<<endl;
        cout<<"To see automa open cmd file and then open your new pdf file called "<<f<<".pdf"<<endl;
        goto start;
    }
    else if(command=="ext")
    {
        exit(0);
    }
    else
    {
        cout<<"Invalid command"<<endl;
        goto start;
    }
}
