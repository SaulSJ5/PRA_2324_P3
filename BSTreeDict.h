#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
  BSTree<TableEntry<V>>* tree;

    public:
  BSTreeDict(){
    tree = new BSTree<TableEntry<V>>();
  }

  ~BSTreeDict(){
    delete tree;
  }

  friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
    out << *bs.tree;
        return out;
  }

  V operator[](string key){
     TableEntry<V> entry(key);
        try {
            return tree->search(entry).value;
        } catch (const runtime_error &e) {
            throw runtime_error("La clave no se encuentra en el diccionario.");
        }
  }

  void insert(string key, V value) override {
        // Implementa la inserción en el árbol
        TableEntry<V> entry(key, value);
        try {
            tree->insert(entry);
        } catch (const runtime_error &e) {
            throw runtime_error("La clave ya existe en el diccionario.");
        }
    }

    V search(string key) override {
        // Implementa la búsqueda en el árbol y devuelve el valor asociado a la clave
        TableEntry<V> entry(key);
        try {
            return tree->search(entry).value;
        } catch (const runtime_error &e) {
            throw runtime_error("La clave no se encuentra en el diccionario.");
        }
    }

    V remove(string key) override {
        // Implementa la eliminación en el árbol y devuelve el valor asociado a la clave
        TableEntry<V> entry(key);
        try {
            V value = tree->search(entry).value;
            tree->remove(entry);
            return value;
        } catch (const runtime_error &e) {
            throw runtime_error("La clave no se encuentra en el diccionario.");
        }
    }

    int entries() override {
        // Implementa la obtención del número de elementos en el árbol
        return tree->size();
    }
        
};

#endif
