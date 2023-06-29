#include "linked_list.h"

void fillLinkedList(Node **head)
{
    int asset_number, n;
    void *data;
    Node *iter, *temp;

    n = (rand() % 11) + 10;
    //n = 4;
    for (int i = 0; i < n; i++)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->next = NULL;
        asset_number = (rand() % 4) + 1;
        int ivals = (rand() % 10);
        double svlas = drand48();
        switch (asset_number)
        {
        case 1:
            temp->data = malloc(sizeof(Asset1));
            Asset1 *p1 = (Asset1 *)(temp->data);
            strcpy(p1->type, "Asset1");
            (p1->ivals)[0] = ivals;
            (p1->svals)[0] = svlas;
            break;
        case 2:
            temp->data = malloc(sizeof(Asset2));
            Asset2 *p2 = (Asset2 *)temp->data;
            strcpy(p2->type, "Asset2");
            p2->ivals[0] = ivals;
            p2->ivals[1] = ivals + 1;
            p2->svals[0] = svlas;
            p2->svals[1] = svlas + 0.4;
            break;
        case 3:
            temp->data = malloc(sizeof(Asset3));
            Asset3 *p3 = (Asset3 *)temp->data;
            strcpy(p3->type, "Asset3");
            strcpy(p3->string1, "CSE");
            strcpy(p3->string2, "102");
            break;
        case 4:
            temp->data = malloc(sizeof(Asset4));
            Asset4 *p4 = (Asset4 *)temp->data;
            strcpy(p4->type, "Asset4");
            p4->value1 = svlas;
            p4->value2 = svlas + 1;
            p4->value3 = svlas * 0.8;
            break;
        default:
            break;
        }
        if (*head == NULL)
        {
            *head = temp;
            iter = *head;
        }
        else
        {
            iter->next = temp;
            iter = iter->next;
        }
    }
}

void Deallocte_list(Node **head)
{
    if (*head == NULL)
        return;
    Node *iter = *head, *iter1 = iter->next;
    while (iter != NULL)
    {
        free(iter->data);
        free(iter);
        iter = iter1;
        if (iter1 != NULL)
            iter1 = iter1->next;
    }
}

void serializeLinkedList(Node *head)
{
    if (head == NULL)
    {
        printf("Linked list is empty...\n");
        return;
    }
    FILE *f = fopen("linkedlist.bin", "wb");
    if (f == NULL)
    {
        printf("Failed to open file...\n");
        return;
    }
    char type[20];
    Node *iter = head;
    while (iter != NULL)
    {
        strcpy(type, ((Asset1 *)iter->data)->type);
        fwrite(type, sizeof(char), 20, f);
        if (strcmp(type, "Asset1") == 0)
        {
            fwrite(iter->data, sizeof(Asset1), 1, f);
        }
        else if (strcmp(type, "Asset2") == 0)
        {
            fwrite(iter->data, sizeof(Asset2), 1, f);
        }
        else if (strcmp(type, "Asset3") == 0)
        {
            fwrite(iter->data, sizeof(Asset3), 1, f);
        }
        else
        {
            fwrite(iter->data, sizeof(Asset4), 1, f);
        }
        iter = iter->next;
    }
    fclose(f);
}

void deserializeLinkedList(Node **head)
{
    FILE *f = fopen("linkedlist.bin", "rb");
    if (f == NULL)
    {
        printf("Failed to open file...\n");
        return;
    }
    Node *iter, *temp;
    char type[20];
    while (1)
    {
        size_t bytes_read = fread(type, sizeof(char), 20, f);
        if (bytes_read != 0)
        {
            temp = (Node *)malloc(sizeof(Node));
            temp->next = NULL;
            if (strcmp(type, "Asset1") == 0)
            {
                temp->data = malloc(sizeof(Asset1));
                fread(temp->data, sizeof(Asset1), 1, f);
            }
            else if (strcmp(type, "Asset2") == 0)
            {
                temp->data = malloc(sizeof(Asset2));
                fread(temp->data, sizeof(Asset2), 1, f);
            }
            else if (strcmp(type, "Asset3") == 0)
            {
                temp->data = malloc(sizeof(Asset3));
                fread(temp->data, sizeof(Asset3), 1, f);
            }
            else
            {
                temp->data = malloc(sizeof(Asset4));
                fread(temp->data, sizeof(Asset4), 1, f);
            }
            if(*head == NULL)
            {
                *head = temp;
                iter = *head;
            }
            else
            {
                iter->next = temp;
                iter = iter->next;
            }
        }
        else if(feof(f))
            break;
        else
        {
            printf("Error reading the file...\n");
            break;
        }
    }
    fclose(f);
}
