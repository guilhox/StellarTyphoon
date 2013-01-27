template <class T>
T* Pilha<T>:: pop() {
   if(isEmpty()){return 0;}
   T* dat = topo->data;
   Link* oldTopo = topo;
   topo = oldTopo->next;
   delete oldTopo;
   return dat;
}

template <class T>
Pilha<T> :: ~Pilha() {
         if(!own) return;
         while(!isEmpty ()) {
              delete pop();
       }
}

template <class T>
void Pilha<T>:: push(T* dat){
   topo = new Link (dat, topo);
}

template <class T>
bool Pilha<T>:: isEmpty(){
     return topo == 0;
}
