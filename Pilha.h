template <class T>
class Pilha {
      struct Link {
             T* data;
             Link* next;
             Link (T* dat, Link* nxt) : data(dat), next(nxt) {}
}* topo;
bool own;
public :
       Pilha(bool o = true) : head(0), own(o) {}
       ~Pilha();
       T* pop();
       void push (T* value);
       bool isEmpty();
       bool owns() const {return own;}
};
