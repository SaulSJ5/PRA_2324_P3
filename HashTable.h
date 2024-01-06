#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
  int n;
  int max;

  ListLinked<TableEntry<V>>* table;

  
    public:
  
  int h(string key){
    int i,suma = 0;

    for(i = 0; i< key.size(); i++){
      suma +=  int(key.at(i));
    }

    int res = (suma%max);

    return res;
  }

  HashTable(int size){

    this->table = new ListLinked<TableEntry<V>>[size];
    
    this->max = size;
    this->n = 0;
   

  }

  ~HashTable(){
    
    delete[] table;

  }

  int capacity(){
    return max;
  }


  
  friend ostream& operator<<(ostream &out, const HashTable<V> &th){
    
    for (int i = 0; i < th.max; i++) {
        out << "CUBETA " << i << ": ";
        
        Node<TableEntry<V>>* aux = th.table[i].getFirst();
        while (aux != nullptr) {
            out << "(" << aux->data.key << ", " << aux->data.value << ") ";
            aux = aux->next;
        }

        out << endl;
    }
    return out;

  }

  V operator[](string key){
    
    int indice = h(key);
     TableEntry<V> s(key);
       
        Node<TableEntry<V>>* aux = table[indice].getFirst();
	
        while (aux != nullptr) {
	  
            if (aux->data == key) {
               
                return aux->data.value;
            }
            aux = aux->next;
        }

      
        throw runtime_error("La clave no se encuentra en el diccionario.");

  }


  void insert(string key, V value) override{
  
    int indice = h(key);
    
   TableEntry<V> entry(key, value);
   Node<TableEntry<V>>* aux = table[indice].getFirst();

   while(aux != nullptr){
     
        if (aux->data == entry) {
            throw runtime_error("La clave ya existe en el diccionario.");
        }
	aux = aux->next;
   }
       
        table[indice].append(entry);
        n++;
  }

  V search(string key) override{
   
    int indice = h(key);

  
    Node<TableEntry<V>>* aux = table[indice].getFirst();
    
    while (aux != nullptr) {
        if (aux->data.key == key) {
          
            return aux->data.value;
        }
        aux = aux->next;
    }

    
    throw runtime_error("La clave no se encuentra en el diccionario.");
   

    }

  V remove(string key) override{
    int indice = h(key);
    int cont = 0;
    
    TableEntry<V> s(key);
    Node<TableEntry<V>>* aux = table[indice].getFirst();
    
    while (aux != nullptr) {
      
        if (aux->data == s) {
	  V val = aux->data.value;
	   table[indice].remove(cont);
	  n--;
            return val;
        }
	aux = aux->next;
	cont++;
        
    }
    
    throw runtime_error("La clave no se encuentra en el diccionario.");
    
  }

  int entries() override{
    return n;
  }

  
        
};

#endif
