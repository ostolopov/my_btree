#ifndef MY_BTREE_FUNCS_H
#define MY_BTREE_FUNCS_H

#include <iostream>
#include <fstream>

using namespace std;

struct BTree {
    int data;
    BTree *left;
    BTree *right;
};

inline BTree *broot = nullptr;

BTree *create_node (int data);
BTree *btree_insert (BTree *node, int data);
void btree_inorder (BTree *node);
void btree_preorder (BTree *node);
void btree_postorder (BTree *node);
void find_min (BTree *node);
void find_max (BTree *node);


struct Queue {
    BTree** arr;
    int start;
    int end;
    int capacity;
};

Queue* create_queue(int capacity);
bool is_empty(Queue* queue);
void enable_queue(Queue* queue, BTree* node);
BTree* delete_queue(Queue* queue);
int count_nodes(BTree* root);
void btree_wideorder(BTree* root);
BTree *btree_delete (BTree *node, int data);
BTree *BTree_search (BTree *node, int data);
void btree_destroy(BTree* node);

void writeNodes(BTree* current, int parentID, ofstream& dotFile) ;
void print_tree_graph(BTree* node, char* filename);
#endif
