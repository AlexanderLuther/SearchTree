/* 
 * File:   main.cpp
 * Author: helmuth
 *
 * Created on 8 de abril de 2020, 22:06
 */
#include <cstdlib>
#include "SearchTree.hpp"
using namespace std;

int main() {
    try{
        SearchTree<char> tree;
        tree.insert('a');
        tree.insert('d');
        tree.insert('s');
        tree.insert('w');
        tree.insert('e');
        tree.insert('p');
        tree.insert('h');
        tree.insert('u');
        tree.remove('s');
        tree.remove('d');
        tree.preOrder();
        tree.inOrder();
        tree.postOrder();   
    }
    catch(string s){
        cout<<s<<endl;
    }
    return 0;
}
