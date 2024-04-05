#ifndef BRT_H
#define BRT_H
#include <cstdlib>
#include <iostream>



class BRT {
private:
    struct Node {
        int key;
        int size; 
        Node *left, *right;
        Node (int k) { key = k; size = 1; left = right = NULL; }
    };

    Node *T;
    void update_size(Node *n);
    Node *select(Node *root, int r);
    void print_inorder(Node *root);
    std::pair<Node *, Node *> split(Node *root, int r);
    Node *insert(Node *root, int r, int v);
    Node *join(Node *L, Node *R);
    Node *remove(Node *root, int r);
public:
    BRT();
    ~BRT();
    int select(int r);
    void print_inorder();
    void insert(int r, int v);
    void remove(int r);
};


#endif