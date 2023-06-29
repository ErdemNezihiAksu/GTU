#include "linked_list.h"

void print_list(Node *head)
{
    Node *iter = head;
    Asset1 *p1;
    Asset2 *p2;
    Asset3 *p3;
    Asset4 *p4;
    char type[20];
    while(iter != NULL)
    {
        strcpy(type,((Asset1*)iter->data)->type);
        if(strcmp(type,"Asset1") == 0)
        {
            p1 = (Asset1*)iter->data;
            printf("%s, %d, %lf\n",p1->type,p1->ivals[0],p1->svals[0]);
        }
        else if(strcmp(type,"Asset2") == 0)
        {
            p2 = (Asset2*)iter->data;
            printf("%s, %d, %d, %lf, %lf\n",p2->type,p2->ivals[0],p2->ivals[1],p2->svals[0],p2->svals[1]);
        }
        else if(strcmp(type,"Asset3") == 0)
        {
            p3 = (Asset3*)iter->data;
            printf("%s, %s, %s\n",p3->type,p3->string1,p3->string2);
        }
        else
        {
            p4 = (Asset4*)iter->data;
            printf("%s, %lf, %f, %lf\n",p4->type,p4->value1,p4->value2,p4->value3);
        }
        iter = iter->next;
    }
}

int main()
{
    srand(time(NULL));
    srand48(time(NULL));
    Node *head = NULL, *read = NULL;
   
    fillLinkedList(&head);
    print_list(head);
    serializeLinkedList(head);
    deserializeLinkedList(&read);
    printf("-------------------\n");
    print_list(read);
    Deallocte_list(&head);
    Deallocte_list(&read);
}