#include <stdlib.h>
#include <stdio.h>
#include "BST.h"

int Menu()
{
    int n;
    label:
    printf("\nChoose an operation:\n1. Add Node\n2. Remove Node\n3. Search Node\n4. Count Nodes\n5. Get Max Depth\n6. Count Leaf Nodes\n7. Print tree\n8. Exit\n> ");
    scanf("%d",&n);
    if(n < 1 || n > 8)
    {
        goto label;
    }
    return n;
}

int main()
{
    BST *tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    int value;

    tree = generateBST("file.txt");

    while(1)
    {
        int n = Menu();
        switch (n)
        {
        case 1:
            printf("Enter a value: ");
            scanf("%d",&value);
            Add_Node(tree,value);
            break;
        case 2:
            printf("Enter a value: ");
            scanf("%d",&value);
            Remove_Node(tree,value);
            break;
        case 3:
            printf("Enter a value: ");
            scanf("%d",&value);
            Search_Node(tree,value);
            break;
        case 4:
            printf("\nThe count is : %d\n", Count_Nodes(tree));
            break;
        case 5:
            printf("\nMax depth is : %d\n",Get_Max_Depth(tree));
            break;
        case 6:
            printf("\nLeaf count is : %d\n", Get_Leaf_Count(tree));
            break;
        case 7:
            Display_LNR(tree->root);
            break;
        default:
            return 0;
        }
    }
}