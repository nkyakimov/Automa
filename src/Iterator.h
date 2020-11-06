#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED




template<class T>
class Iterator{
private:
    vector<pair<Node<T>*,int>>currents;
public:
   Iterator (Node<T>* contr);
    void operator ++();
    T operator* ();
    bool operator == (const Iterator& a);
    bool operator != (const Iterator& a);
    bool element(const vector<pair<Node<T>*,int>>,const Node<T>*);
};

#endif // ITERATOR_H_INCLUDED
