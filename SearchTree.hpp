/* 
 * File:   Tree.hpp
 * Author: helmuth
 *
 * Created on 8 de abril de 2020, 22:07
 */
#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP
#include "Node.hpp"

template <class T>
class SearchTree {
   
    public:
        SearchTree();
        SearchTree(Node<T>* root);
        void setRoot(Node<T>* root);
        Node<T>* getRoot();
        bool isEmpty();
        Node<T>* search(T value);
        void insert(T value);
        void remove(T value);
        void preOrder();
        void inOrder();
        void postOrder();
        virtual ~SearchTree();
        
    private:
        Node<T>* root;
        Node<T>* search(Node<T>* subRoot, T value);
        Node<T>* insert(Node<T>* subRoot, T value);
        Node<T>* remove(Node<T>* subRoot, T value);
        Node<T>* replace(Node<T>* currentNode);
        void preOrder(Node<T>* root);
        void inOrder(Node<T>* root);
        void postOrder(Node<T>* root);
};

//Constructores de la clase.
template <class T>
SearchTree<T>::SearchTree(){
    root = NULL;
}

template <class T>
SearchTree<T>::SearchTree(Node<T>* root){
    this->root = root;
}

//Setter de la clase.
template <class T>
void SearchTree<T>::setRoot(Node<T>* root){
    this->root = root;
}

//Getters de la clase.
template <class T>
Node<T>* SearchTree<T>::getRoot(){
    return root;
}

/*
 * Metodo encargado de valida si el arbol se encuentra vacio. Devuelve un valor boleano
 * dependiendo si la raiz apunta o no a null.
 */
template <class T>
bool SearchTree<T>::isEmpty(){
    return root == NULL;
}

/*
 * Metodo encargado de insertar un nuevo dato dentro del arbol.
 */
template <class T>
void SearchTree<T>::insert(T value){
    root = insert(root, value);
}

/*
 * Metodo encargado de realizar la insercion.
 * Si la subRaiz es nula se crea un nuevo nodo dentro de la misma.
 * Si el valor es menor al valor contenido dentro la hoja actual, se crea un nuevo nodo 
 * y se llama recursivamente al metodo enviando como subRaiz la referencia al nodo izquierdo
 * de la hoja actual, por ultimo se establece el hijo izquierdo de la hoja actual al nodo 
 * recien creado.
 * Si el valor es mayor al valor contenido dentro la hoja actual, se crea un nuevo nodo 
 * y se llama recursivamente al metodo enviando como subRaiz la referencia al nodo derecho
 * de la hoja actual, por ultimo se establece el hijo derecho de la hoja actual al nodo 
 * recien creado.
 * Si no se cumple con ninguno de los criterios anteriores se lanza una excepcion.
 */
template <class T>
Node<T>* SearchTree<T>::insert(Node<T>* subRoot, T value){
    if(subRoot == NULL){
        subRoot = new Node<T>(value);
    }
    else if(value < subRoot->getValue()){
        Node<T>* left;
        left = insert(subRoot->getLeft(), value);
        subRoot->setLeft(left);
    }
    else if(value > subRoot->getValue()){
        Node<T>* rigth;
        rigth = insert(subRoot->getRigth(), value);
        subRoot->setRigth(rigth);    
    } 
    else{
        std::string msg = "Nodo duplicado";
        throw  msg;
        
    }
    return subRoot;
}
/*
 * Metodo encargado de buscar un dato dentro del arbol. Devuelve la referencia del nodo que
 * contiene el dato buscado.
 */
template <class T>
Node<T>* SearchTree<T>::search(T value){
    return search(root, value);
}

/*
 * Metodo encargado de realizar una busqueda.
 * Si la subRaiz es nula se retorna null.
 * Si el valor es igual al valor de la hoja actual, se retorna un referencia a la hoja actual.
 * Si el valor es menor al valor contenido dentro la hoja actual, se retorna un llamado recursivo
 * al metodo enviando como parametros el hijo izquierdo de la hoja actual y el valor buscado.
 * Si no se cumple con ninguno de los criterios anteriores se retorna un llamado recursivo
 * al metodo enviando como parametros el hijo derecho de la hoja actual y el valor buscado.
 */
template <class T>
Node<T>* SearchTree<T>::search(Node<T>* subRoot, T value){
    if(subRoot == NULL){
        return NULL;
    }
    else if(value == subRoot->getValue()){
        return subRoot;
    }
    else if(value < subRoot->getValue()){
        return search(subRoot->getLeft(), value);
    }
    else{ 
        return search(subRoot->getRigth(), value);
    } 
}

/*
 * Metodo encargado de remover un dato dentro del arbol.
 */
template <class T>
void SearchTree<T>::remove(T value){
    root = remove(root, value);
}

/*
 * Metodo encargado de eliminar un nodo del arbol.
 * Realiza una busqueda del nodo que se desea eliminar.
 * Al encontrarlo establece si es un nodo son un solo hijo izquierdo, con un solo hijo 
 * derecho o con ambos hijos.
 *  Hijo izquierdo: Establece el valor del nodo actual al valor de hijo izquierdo del mismo.
 *  Hijo derecho: Establece el valor del nodo actual al valor de hijo derecho del mismo. 
 *  Ambos hijos: Llama al metodo replace enviando como parametro el nodo actual.
 */
template <class T>
Node<T>* SearchTree<T>::remove(Node<T>* subRoot, T value){
    if(subRoot == NULL){
        std::string msg = "No se encontro ningun nodo con ese valor";
        throw  msg;
    }
    else if(value < subRoot->getValue()){
        Node<T>* left;
        left = remove(subRoot->getLeft(), value);
        subRoot->setLeft(left);
    }
    else if(value > subRoot->getValue()){
        Node<T>* rigth;
        rigth = remove(subRoot->getRigth(), value);
        subRoot->setRigth(rigth);    
    }
    //Nodo encontrado
    else{
        Node<T>* node;
        node = subRoot;
        if(node->getLeft() == NULL){
            subRoot = node->getRigth();
        }
        else if(node->getRigth() == NULL){
            subRoot = node->getLeft();
        }
        //Nodo con hijos derechos e izquierdos
        else{
            node = replace(node);
        } 
        node = NULL;
        return subRoot;
    }
}

/*
 * Metodo encargado de eliminar un nodo con dos hijos y modificar la estructura del
 * arbol para que cumpla con los criterios de un arbol de busqueda.
 */
template <class T>
Node<T>* SearchTree<T>::replace(Node<T>* currentNode){
    Node<T>* auxNode;
    Node<T>* node;
    node = currentNode;
    auxNode = currentNode->getLeft();
    while(auxNode->getRigth() != NULL){
        node = auxNode;
        auxNode = auxNode->getRigth();
    }
    currentNode->setValue(auxNode->getValue());
    if(node == currentNode){
        node->setLeft(auxNode->getLeft());
    }
    else{
        node->setRigth(auxNode->getLeft());
    }
}

/*
 * Recorrido pre-Orden del arbol.
 */
template <class T>
void SearchTree<T>::preOrder(){
    preOrder(root);
    std::cout<<"\n";
}

template <class T>
void SearchTree<T>::preOrder(Node<T>* root){
    if(root != NULL){
        std::cout<<root->getValue()<<" ";
        preOrder(root->getLeft());
        preOrder(root->getRigth());
    }
}

/*
 * Recorrido in-Orden del arbol.
 */
template <class T>
void SearchTree<T>::inOrder(){
    inOrder(root);
    std::cout<<"\n";
}

template <class T>
void SearchTree<T>::inOrder(Node<T>* root){
    if(root != NULL){
        inOrder(root->getLeft());
        std::cout<<root->getValue()<<" ";
        inOrder(root->getRigth());
    }
}

/*
 * Recorrido post-Orden del arbol.
 */
template <class T>
void SearchTree<T>::postOrder(){
    postOrder(root);
    std::cout<<"\n";
}

template <class T>
void SearchTree<T>::postOrder(Node<T>* root){
    if(root != NULL){
        postOrder(root->getLeft());
        postOrder(root->getRigth());
        std::cout<<root->getValue()<<" ";
    }
}

template <class T>
SearchTree<T>::~SearchTree(){
    delete root;
}
#endif /* SEARCHTREE_HPP */

