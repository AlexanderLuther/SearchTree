/* 
 * File:   Node.hpp
 * Author: helmuth
 *
 * Created on 8 de abril de 2020, 22:07
 */
#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>

template <class T>
class Node {
    
    public:
        Node();
        Node(T value);
        Node(T value, Node<T>* left, Node<T>* rigth);
        void setValue(T value);
        void setLeft(Node<T>* left);
        void setRigth(Node<T>* rigth);
        T getValue();
        Node<T>* getLeft();
        Node<T>* getRigth();  
        virtual ~Node();
    
    private:
        Node<T>* rigth;
        Node<T>* left;
        T value;
        

};

template <class T>
Node<T>::Node(){
    this->value = NULL;
    this->left = NULL;
    this->rigth = NULL;
}

template <class T>
Node<T>::Node(T value){
    this->value = value;
    this->left = NULL;
    this->rigth = NULL;
}

template <class T>
Node<T>::Node(T value, Node<T>* left, Node<T>* rigth){
    this->value = value;
    this->left = left;
    this->rigth = rigth;
}

/*
 * Setters de la clase.
 */
template <class T>
void Node<T>::setValue(T value){
    this->value = value;
}

template <class T>
void Node<T>::setLeft(Node<T>* left){
    this->left = left;
}

template <class T>
void Node<T>::setRigth(Node<T>* rigth){
    this->rigth = rigth;
}

/*
 * Getters de la clase.
 */
template <class T>
T Node<T>::getValue(){
    return this->value;
}

template <class T>
Node<T>* Node<T>::getLeft(){
    return this->left;
}

template <class T>
Node<T>* Node<T>::getRigth(){
    return this->rigth;
}

template <class T>
Node<T>::~Node(){
    delete left;
    delete rigth;
}
#endif /* NODE_HPP */


