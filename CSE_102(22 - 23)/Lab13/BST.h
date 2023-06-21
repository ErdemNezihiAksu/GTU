#ifndef BTS_H
#define BTS_H
typedef struct n
{
    int value;
    struct n* left, *right;
}Node;
typedef struct m
{
    Node* root;
}BST;
void Add_tree(Node** tree, int data);
void Display_LNR(Node* tree);
BST* generateBST(const char* filename);
void Add_Node(BST *tree, int data);
void Remove_Node(BST * tree, int data);
Node* Search_Node(BST *tree, int data);
int Count_Nodes(BST *tree);
int Get_Max_Depth(BST *tree);
int Get_Leaf_Count(BST *tree);
#endif