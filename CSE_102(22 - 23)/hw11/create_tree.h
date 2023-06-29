#ifndef create_tree_h
#define create_tree_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct n node;
struct n                //node struct ı ağacın node larını oluşturur. 
{
    char name[20];
    int age;
    node *mother;
    node* father;
    node* spouse;
    node **childs;
};
typedef struct  //tree struct ı, ağacın root larını ve ailenin ismini tutmak için kullanılır.
{
    char family_name[20];
    node *root_father;
    node *root_mother;
}tree;
typedef struct a    //list struct ı bütün tree lerin tutulacağı bir liste oluşturmak için kullanılır.
{
    tree *family;
    struct a *next;
}list;
list *create_new_family(list *liste);
list *Add_roots(list *liste);
void Save_Family_Tree(list *liste);
void write_file(FILE *f, node* root);
#endif