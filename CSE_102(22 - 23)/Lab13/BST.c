#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

void Add_tree(Node** tree, int data)
{
    if(*tree == NULL)
    {
        Node *temp = (Node*)malloc(sizeof(Node));
        temp->value = data;
        temp->left = NULL;
        temp->right = NULL;
        *tree = temp;
        return;
    }
    if(data < (*tree)->value)
    {
        Add_tree(&(*tree)->left,data);
    }
    else
    Add_tree(&(*tree)->right,data);
}

void Display_LNR(Node* tree)
{
    if(tree == NULL)
    return;
    Display_LNR(tree->left);
    printf("%d, ",tree->value);
    Display_LNR(tree->right);
}

BST* generateBST(const char* filename)
{
    FILE *f = fopen(filename,"r");
    BST* tree = (BST*)malloc(sizeof(BST));
    int data;

    tree->root = NULL;
    while(fscanf(f,"%d ",&data) == 1)
    {
        Add_tree(&tree->root,data);
    }
    fclose(f);
    return tree;
}

void Add_Node(BST *tree, int data)
{
    Add_tree(&tree->root,data);
}

int Min(Node* tree)
{
    while(tree->left != NULL)
        tree = tree->left;
    return tree->value;
}

int Max(Node* tree)
{
    while(tree->right != NULL)
        tree = tree->right;
    return tree->value;
}

Node* Remove(Node *tree, int data)
{
    if(tree == NULL)
        return NULL;
    if(tree->value == data)
    {
        if(tree->left == NULL && tree->right == NULL)
            return NULL;
        if(tree->right != NULL)
        {
            tree->value = Min(tree->right);
            tree->right = Remove(tree->right,tree->value);
            return tree;
        }
        tree->value = Max(tree->left);
        tree->left = Remove(tree->left,tree->value);
        return tree;
    }
    if(data < tree->value)
        tree->left = Remove(tree->left,data);
    else
        tree->right = Remove(tree->right,data);
    return tree;
}

void Remove_Node(BST * tree, int data)
{
    if(tree->root == NULL)
    {
        printf("No element to delete!!\n");
        return;
    }
    tree->root = Remove(tree->root,data);
}

Node* Search(Node* tree, int data)
{
    if(tree == NULL)
        return NULL;
    if(tree->value == data)
        return tree;
    if(data < tree->value)
        return Search(tree->left,data);
    return Search(tree->right,data);
}
Node* Search_Node(BST *tree, int data)
{
    Node *temp;
    temp = Search(tree->root,data);
    if(temp == NULL)
    {
        printf("Value can not be found!!\n");
        return temp;
    }
    printf("Value %d is found!!\n",temp->value);
    return temp;
}

int Count(Node* tree)
{
    if(tree == NULL)
        return 0;
    return 1 + Count(tree->left) + Count(tree->right);
}

int Count_Nodes(BST *tree)
{
    return Count(tree->root);
}

int Max_depth(Node *tree)
{
    if(tree == NULL)
        return 0;
    int leftdepth = Max_depth(tree->left);
    int rightdepth = Max_depth(tree->right);
    if(leftdepth > rightdepth)
        return leftdepth + 1;
    return rightdepth + 1;
}

int Get_Max_Depth(BST *tree)
{
    return Max_depth(tree->root);
}

int Leaf_Count(Node* tree)
{
    if(tree == NULL)
        return 0;
    if(tree->left == NULL && tree->right == NULL)
        return 1;
    return Leaf_Count(tree->right) + Leaf_Count(tree->left);
}

int Get_Leaf_Count(BST *tree)
{
    return Leaf_Count(tree->root);
}