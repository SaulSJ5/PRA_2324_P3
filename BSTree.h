#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
  
  int nelem;
  BSNode<T>* root;

  BSNode<T>* search(BSNode<T>* n, T e) const{
    if (n == nullptr || n->elem == e) {
        return n;
    }

    if (e < n->elem) {
        return search(n->left, e);
    } else {
        return search(n->right, e);
    }
   
  }

  BSNode<T>* insert(BSNode<T>* n, T e){
    if(n == nullptr){
      nelem++;
      return new BSNode<T>(e);
    }
    else if(n->elem == e){
      throw runtime_error("El elemento ya ha sido encontrado en el árbol.");  
  }
    else if(n->elem < e){
      n->right = insert(n->right, e);
    }
    else{
      n->left = insert(n->left, e);

    }
   
    return n;
  }

  
  void print_inorder(ostream &out, BSNode<T>* n) const{
    if (n != nullptr) {
      
      print_inorder(out, n->left);
        out << n->elem << " ";
        print_inorder(out, n->right);
    }
    
  }

  BSNode<T>* remove(BSNode<T>* n, T e){
    if (n == nullptr) {
        throw runtime_error("Elemento no encontrado en el árbol.");
	
    } else if (n->elem < e) {
      
        n->right = remove(n->right, e);
	
    } else if (n->elem > e) {
      
        n->left = remove(n->left, e);
	
    } else {

     
        if (n->left != nullptr && n->right != nullptr) {
	  
            n->elem = max(n->left);
	    
            n->left = remove_max(n->left);
	    
        } else {
	  
            BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
	    
            delete n;
            return temp;
        }
    }
    nelem--;
    return n;

  }

  T max(BSNode<T>* n) const{

    if (n == nullptr) {
        throw std::runtime_error("Elemento no encontrado en el árbol.");
	
    } else if (n->right != nullptr) {
      
        return max(n->right);
	
    } else {
      
        return n->elem;
    }
  }

  BSNode<T>* remove_max(BSNode<T>* n){
    
    if (n->right == nullptr) {
      
        BSNode<T>* temp = n->left;
        delete n;

        return temp;
    } else {
        n->right = remove_max(n->right);
        return n;
    }

  }

  void delete_cascade(BSNode<T>* n){
    if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }

  }

  
    public:
  
  BSTree(){
    root = nullptr;
    nelem = 0;
  }

  int size() const{
    return nelem;
  }

  T search(T e) const{
    BSNode<T>* busq = search(root, e);

    if (busq != nullptr) {
        return busq->elem;
    } else {
       
        throw runtime_error("Elemento no encontrado en el árbol.");
    }
  }

  T operator[](T e) const{
    BSNode<T>* result = search(root, e);
        if (result != nullptr) {
            return result->elem;
        } else {
            
            throw runtime_error("Elemento no encontrado en el árbol.");
        }

  }

  void insert(T e){

    root = insert(root, e);
  }

  friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
    
    bst.print_inorder(out, bst.root);
    return out;
  }

  void remove(T e){
    root = remove(root, e);
  }

  ~BSTree(){

    delete_cascade(root);
    
  }

  

  
       
    
};

#endif
