#include "tree.h"

node* Deallocate_tree(node *family, char *root_name) //bir ağacı deallocate eder.
{
    if(family == NULL)
        return family;
    if(strcmp((family)->name,root_name) == 0 && (family)->childs[0] == NULL)
    {
        //printf("%s",family->name);
        if(family->spouse != NULL)
        {
            //printf(",%s",family->spouse->name);
            free(family->spouse);
        }
        //printf("\n");
        free(family);
        return family;
    }
    for(int i = 0; (family)->childs[i] != NULL; i++) //recursive bir şekilde rootun çocucğunun cocuğunun... diye sona giderek silme işlemi yapılır
        family->childs[i] = Deallocate_tree(family->childs[i], root_name);
        
    //printf("%s, ",(family)->name);
    if(family->spouse != NULL)
    {
        //printf("%s,",family->spouse->name);
        free(family->spouse);
    }
    free(family);
}

void Deallocate_list(list **liste) //listenin tamamını yani her ağacı siler.
{
    if(*liste == NULL)
        return;
    list *iter = (*liste)->next;
    char filename[25];
    sprintf(filename,"%s.txt",(*liste)->family->family_name); 
    *liste = Remove_family_tree(*liste,(*liste)->family->family_name,filename); //family lerin txt dosyaları da silinr.
    Deallocate_list(liste);
}

list* Remove_family_tree(list *liste, char* family_name, char* filename) //liste den bir family i (ağacını,txt sini) siler.
{
    if(liste == NULL)
    {
        printf("No family!!\n");
        return liste;
    }
    FILE *f = fopen(filename,"r");
    if(f == NULL)
    {
        printf("\nFile does not exist!!\n");
        return liste;
    }
    fclose(f);
    list *iter = liste;
   
    if(strcmp(iter->family->family_name,family_name) == 0)
    {
        liste->family->root_father = Deallocate_tree(liste->family->root_father,liste->family->root_father->name); //ilk başta aile ağacı silinir.
        liste = liste->next;
        free(iter);  //sonra aile ağacını tutan list struct ı listeden silinir
        remove(filename); //sonra txt file silinir.
        printf("\n%s is removed succesfully\n",family_name);
        return liste;
    }
    while(iter->next != NULL)
    {
        if(strcmp(iter->next->family->family_name,family_name) == 0)
            break;
        iter = iter->next;
    }
    if(iter->next == NULL)
    {
        printf("Family does not exist!!\n");
        return liste;
    }

    list *removed = iter->next; //family listeden çıkartılır.
    iter->next = removed->next;
    removed->family->root_father = Deallocate_tree(removed->family->root_father,removed->family->root_father->name); //ağaç silinir
    free(removed);
    remove(filename);  //txt silinir
    printf("\n%s is removed succesfully\n",family_name);
    return liste;
}

int get_child_count(node *parent)
{
    int i;
    for(i = 0; parent->childs[i] != NULL; i++);
    return i;
}
node* Search_tree(node *root, char* name)
{
    node* search = NULL;
    if(root == NULL)
        return NULL;
    if(strcmp(root->name,name) == 0)
        return root;
    if(root->spouse != NULL && strcmp(root->spouse->name,name) == 0)
        return root->spouse;
    for(int i = 0; root->childs[i] != NULL; i++)
    {
        search = Search_tree(root->childs[i],name);
        if(search != NULL)
            return search;
    }
    return NULL;;
}
void Add_new_person(list **iter)
{
    node *new_person = (node*)malloc(sizeof(node)), *father, *mother, *spouse;
    char name[20], choice;
    int child_count;

    while(getchar()!='\n');
    printf("Enter new person's name: ");
    scanf("%[^\n]",new_person->name);
    printf("Enter %s's age: ",new_person->name);
    scanf("%d",&new_person->age);
    printf("is the person an original member of the family(1) or spouse of a family member(0): ");
    scanf(" %c",&choice);       //eklenecek kişinin orijinal aileden biri mi yoksa orijinal aile üyesinin eşi mi olacağı seçilir.
    new_person->childs = (node**)malloc(sizeof(node*));
    new_person->childs[0] = NULL;
    if(choice == '1')
    {
        label1:
        while(getchar()!='\n');
        printf("Enter %s's father: ",new_person->name); //eğer orijinal aile üyesiyse sırayla baba ve anne bilgileri sorulur.
        scanf("%[^\n]",name);
        father = Search_tree((*iter)->family->root_father,name);
        if(father == NULL)
        {
            printf("This person is not in the tree!!\n");
            goto label1;
        }
        else if(father->spouse == NULL)
        {
            printf("This person is single!!\n");
            goto label1;
        }
        new_person->father = father; //yeni kişinin babası atanır.
        child_count = get_child_count(father);
        father->childs = (node**)realloc(father->childs,sizeof(node*) * (child_count+2)); //babanın çocuk sayısı arttırılır
        father->childs[child_count] = new_person; //yeni kişi babanın son çocuğu olarak eklenir.
        father->childs[child_count+1] = NULL;

        label2:
        while(getchar()!='\n');
        printf("Enter %s's mother: ",new_person->name); //anne içinde aynı şeyler yapılır.
        scanf("%[^\n]",name);
        mother = Search_tree((*iter)->family->root_mother,name);
        if(mother == NULL)
        {
            printf("This person is not in the tree!!\n");
            goto label2;
        }
        else if(mother->spouse == NULL || strcmp(mother->spouse->name,father->name) != 0)
        {
            printf("These mother and father are not a couple!!\n");
            goto label2;
        }
        new_person->mother = mother;
        mother->childs = (node**)realloc(mother->childs,sizeof(node*) * (child_count+2));
        mother->childs[child_count] = new_person;
        mother->childs[child_count+1] = NULL;
        new_person->spouse = NULL;
    }
    else //eğer eklenen kişi birinin eşi olacaksa
    {
        label3:
        while(getchar()!='\n');
        printf("Enter the name of %s's spouse: ",new_person->name);
        scanf("%[^\n]",name);
        spouse = Search_tree((*iter)->family->root_father,name);
        if(spouse == NULL)
        {
            printf("This person is not in the tree!!\n");
            goto label3;
        }
        else if(spouse->spouse != NULL)
        {
            printf("This person has already a spouse!!\n");
            goto label3;
        }
        child_count = get_child_count(spouse);
        if(child_count == 0) //eğer çiftin çocukları yoksa
        {
            new_person->childs = (node**)malloc(sizeof(node*)); //yeni kişinin child pointer ı null yapılır.
            new_person->childs[0] = NULL;
        }
        else
        {
            new_person->childs = (node**)malloc(sizeof(node) * (child_count+2)); //eğer çocukları varsa yeni kişi içinde çocuk sayısı kadar hafıza oluşturulur
            for(int i = 0; i < child_count; i++)
            new_person->childs[i] = spouse->childs[i]; //yeni kişinin tüm child pointerları eşininkileri gösterir.
        }
        new_person->spouse = spouse; //yeni kişinin eş pointerı atanır
        spouse->spouse = new_person; //eşininde eş pointer ı yeni kişiye atanır
        new_person->father = NULL;
        new_person->mother = NULL; // yeni kişi orijinal aileden olmadığı için anne baba sı null yapılır.
    }
    char filename[25];
    sprintf(filename,"%s.txt",(*iter)->family->family_name); //ekleme yapılan ailenın txt file ının ismi bulunur
    FILE *f = fopen(filename,"w");
    write_file(f,(*iter)->family->root_father); //txt güncellenilir.
    fclose(f);
    printf("\n%s is added succesfully\n",new_person->name);
}

int Remove_person(list **iter, list **liste)
{
    char name[20], choice[4], filename[25];
    node *person, *father;

    while(getchar()!='\n');
    printf("Enter the name of the person you want to remove: ");
    scanf("%[^\n]",name);
    person = Search_tree((*iter)->family->root_father,name);
    if(person == NULL)
    {
        printf("This person is not in the tree!!\n");
        return 0;
    }
    if(person->childs[0] != NULL) //eğer silinecek kişinin çocukları varsa uyarı verilir
    {
        label1:
        while(getchar()!='\n');
        printf("Warning: %s has children, removing %s also will remove children too.\nDo you still want to continue: ",person->name,person->name);
        scanf("%s",choice);
        if(strcmp(choice,"Yes") != 0 && strcmp(choice,"No") != 0)
        {
            printf("Please type \"Yes\" or \"No\"!!\n");
            goto label1;
        }
        if(strcmp(choice,"No") == 0)
        {
            printf("\n%s is not removed\n",person->name);
            return 0;
        }
    }
    if((*iter)->family->root_father == person || (*iter)->family->root_mother == person) //eğer silinecek kişi rootlardan biriyse
    {
        sprintf(filename,"%s.txt",(*iter)->family->family_name);
        *liste = Remove_family_tree(*liste,(*iter)->family->family_name,filename); //aile ağacı komple silinir ve listeden çıkartılır.
        return 1; //ağacın komple silindiğini belirtir
    }
    int i,a;
    if(person->father != NULL) //eğer silinicek kişi orijinal aileden ise (orijinal üyelerden birinin eşi değilse)
    {
        father = person->father;
        for(i = 0; strcmp(father->childs[i]->name,person->name) != 0; i++); //silinecek kişiyi gösteren pointer bulunur.
    }
    else
    {
        father = person->spouse->father;
        for(i = 0; strcmp(father->childs[i]->name,person->spouse->name) != 0; i++); //silinecek kişinin eşini gösteren pointer bulunur
    }
    for(a = i; father->childs[a] != NULL; a++)
    {
        father->childs[a] = father->childs[a+1]; //silinecek kişi, eşi ve çocukları ağaçtan çıkartılıt
    }
    person = Deallocate_tree(person,person->name); //o kişi,eşi,cocukları vs silinir.
    father->childs = (node**)realloc(father->childs,sizeof(node*)* a); //child pointerlar yeniden düzenlenir
    father->spouse->childs = (node**)realloc(father->childs,sizeof(node*)* a);
    if(a == 1)
    {
        father->childs[0] = NULL;
        father->spouse->childs[0] = NULL;
    }
    printf("\n%s is removed succesfully\n",name);
    return 0;
}

void print_nuclear_family(list *iter)
{
    char name[20];
    node *person;

    while(getchar()!='\n');
    printf("Enter the name of the person: ");
    scanf("%[^\n]",name);
    person = Search_tree(iter->family->root_father,name);
    if(person == NULL)
    {
        printf("\n%s is not in the tree!!\n",name);
        return;
    }
    if(person->father != NULL)
        printf("Father: %s\n",person->father->name);
    if(person->mother != NULL)
    {
        printf("Mother: %s\n",person->mother->name);
        if(person->mother->childs[1] != NULL) //eğer kişinin kardeşi varsa koşulaa girer
        {
            printf("Siblings:");
            int sibling_counter = 0;
            for(int i = 0; person->mother->childs[i] != NULL; i++)
            {
                if(person->mother->childs[i] != person)
                {   
                    if(sibling_counter == 0)
                        printf(" %s",person->mother->childs[i]->name);
                    else
                        printf(", %s",person->mother->childs[i]->name);
                    sibling_counter++;
                }
            }
            printf("\n");
        }
    }
    if(person->spouse != NULL)
        printf("Spouse: %s\n",person->spouse->name);
    if(person->childs[0] != NULL) //kişinin çocuğu varsa koşula girer.
    {
        printf("Children:");
        for(int i = 0; person->childs[i] != NULL; i++)
        {
            if(person->childs[i+1] == NULL)
                printf(" %s",person->childs[i]->name);
            else
                printf(" %s,",person->childs[i]->name);
        }
        printf("\n");
    }
}

void Search_relatives(list *iter)
{
    char name[20];
    int choice;
    node *person, *grandparent;

    while(getchar()!='\n');
    printf("Enter the name of the person: ");
    scanf("%[^\n]",name);
    person = Search_tree(iter->family->root_mother,name);
    if(person == NULL)
    {
        printf("\n%s is not a part of the family!!\n",person->name);
        return;
    }
    printf("Select type of relative:\n1. Parents\n2. Spouse\n3. Children\n4. Grandparents\n5. Cousins\n> ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        if(person->father == NULL && person->mother == NULL)
        {
            printf("\nThere is no parent data for %s in the family tree\n",person->name);
            break;
        }
        printf("\nFather: %s\nMother: %s\n",person->father->name,person->mother->name);
        break;
    case 2:
        if(person->spouse == NULL)
        {
            printf("\n%s has no spouse\n",person->name);
            break;
        }
        printf("\nSpouse: %s\n",person->spouse->name);
        break;
    case 3:
        if(person->childs[0] == NULL)
        {
            printf("\n%s has no children\n",person->name);
            break;
        }
        printf("\nChildren:");
        for(int i = 0; person->childs[i] != NULL; i++)
        {
            printf(" %s",person->childs[i]->name);
            if(person->childs[i+1] != NULL)
                printf(",");
        }
        printf("\n");
        break;
    case 4:
        if(person->father == NULL) //eğer kişi orijinal aile üyesi değilse koşula girer
        {
            printf("\nThere is no granparent data for %s in the family tree\n",person->name);
            break;
        }
        if(person->father->father == NULL && person->mother->father == NULL) //eğer kişi root un çocuklarından biriyse koşula girer
        {
            printf("\nThere is no granparent data for %s in the family tree\n",person->name);
            break;
        }
        if(person->father->father == NULL)
            grandparent = person->mother->father;
        else
            grandparent = person->father->father;
        printf("\nGrandfather: %s\nGrandmother: %s\n",grandparent->name,grandparent->spouse->name);
        break;
    case 5:
        printf("\nCousins:");
        if(person->father == NULL)//kişi root sa veya orijinal üye değilse kuzeni yoktur
        {
            printf(" None\n");
            break;
        }
        if(person->father->father == NULL && person->mother->father == NULL)
        {
            printf(" None\n");
            break;
        }
        if(person->father->father == NULL)
            grandparent = person->mother->father;
        else
            grandparent = person->father->father;
        if(grandparent->childs[1] == NULL) //eğer kişini dedesinin tek çocuğu varsa kuzeni yoktur
        {
            printf(" None\n");
            break;
        }
        int cousin_counter = 0;
        for(int i = 0; grandparent->childs[i] != NULL; i++)
        {
            if(grandparent->childs[i] != person->father && grandparent->childs[i] != person->mother)
            {
                for(int a = 0; grandparent->childs[i]->childs[a] != NULL; a++)
                {
                    cousin_counter++;
                    printf(" %s",grandparent->childs[i]->childs[a]->name);
                    if(grandparent->childs[i+1] != NULL || grandparent->childs[i]->childs[a+1] != NULL)
                        printf(",");
                }
            }
        }
        if(cousin_counter == 0)
            printf(" None");
        printf("\n");
        break;
    default:
        break;
    }
}