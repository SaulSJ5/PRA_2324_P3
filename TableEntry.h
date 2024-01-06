#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V> 
class TableEntry {
    public:

  string key;

  V value;

  
  TableEntry(string key, V value){
    this->key = key;
    this->value = value;

  }

  TableEntry(string key){
    this->key = key;
 
  }

  TableEntry(){
    this->key = "";
  }

  friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
    return te1.key != te2.key;
    

  }

  friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
    return te1.key == te2.key;
  }

  friend ostream& operator<<(std::ostream &out, const TableEntry<V> &te){
    out<<" KEY-> "<<te.key<<"  VALOR-> "<<te.value<<endl;

    return out;
    
  }
  friend bool operator<(const TableEntry<V> &te1, const TableEntry<V> &te2){
    return te1.key < te2.key;

  }
  
  friend bool operator>(const TableEntry<V> &te1, const TableEntry<V> &te2){
    return te1.key > te2.key;

  }

    
};

#endif
