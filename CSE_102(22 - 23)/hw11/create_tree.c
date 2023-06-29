#include "create_tree.h"

list *create_new_family(list *liste)
{
    char name[20], filename[25];
    FILE *f;
    list *iter = liste;
    list *new_family = (list *)malloc(sizeof(list)); //listeye eklenmesi için bir family oluşturulur.

    printf("Please enter the family name: "); //family name in tutlmasının sebebi aynı isimde bir txt dosyasının oluşturulacak olmasıdır.
    scanf("%19s", name);
    new_family->family = (tree*)malloc(sizeof(tree));
    strcpy(new_family->family->family_name, name);
    new_family->family->root_father = NULL; //family nin rootları ve next i null yapılır.
    new_family->family->root_mother = NULL;
    new_family->next = NULL;
    sprintf(filename, "%s.txt", name); //family name ile aynı isimde txt dosyası açılır.
    f = fopen(filename, "w");
    fclose(f);
    if (iter == NULL){  //oluşturulan family listeye eklenir.
        liste = new_family;
        return liste;
    }
    while (iter->next != NULL)
        iter = iter->next;
    iter->next = new_family;
    return liste;
}

list *Add_roots(list *liste)
{
    list *iter = liste;
    while(iter->next != NULL) //listenin sonuna gidilir yani iter oluşturulan family i gösterir.
        iter = iter->next;
    if(iter->family->root_father != NULL) //eğer family nin rootları önceden oluşturulmuşsa return yapılır.
    {
        printf("This family has roots!!\n");
        return liste;
    }
    node *grandfather = (node*)malloc(sizeof(node));
    node *grandmother = (node*)malloc(sizeof(node)); //root lar için hafızada yer oluşturulur.
    printf("Enter the name of the grandfather: ");
    scanf("%19s",grandfather->name);
    printf("Enter grandfather's age: ");    //rootların ismi ve yaşı kullanıcıdan alınır.
    scanf("%d",&grandfather->age);
    grandfather->childs = (node**)malloc(sizeof(node*)); //rootların çocukları için bir node luk yer ayırlır ve null e eşitlenir.
    grandfather->childs[0] = NULL; 
    grandfather->father = NULL;
    grandfather->mother = NULL;
    printf("Enter the name of grandmother: ");
    scanf("%19s",grandmother->name);
    printf("Enter grandmother's age: ");
    scanf("%d",&grandmother->age);
    grandmother->childs = (node**)malloc(sizeof(node*));
    grandmother->childs[0] = NULL;
    grandmother->father = NULL; //rootların father ve mother ları null yapılır
    grandmother->mother = NULL;
    grandfather->spouse = grandmother;
    grandmother->spouse = grandfather;  //root ların spouse ları birbirini gösterir.
    
    iter->family->root_father = grandfather;
    iter->family->root_mother = grandmother;    //liste güncellenir
    printf("The roots are added to the tree succesfully\n");
    return liste;
}

void write_file(FILE *f, node* root)    //family txt ye bastırılır.
{
    for(int i = 0; root->childs[i] != NULL; i++)
        write_file(f,root->childs[i]);
    fprintf(f,"%s,",root->name);
    if(root->spouse != NULL)
    {
        fprintf(f,"%s",root->spouse->name);
        if(root->spouse->father != NULL || root->father != NULL)
            fprintf(f,",");
    }
}

void Save_Family_Tree(list *liste) //family txt ye kaydedilir(write file fonksiyonu burda kullanılır.)
{
    list *iter = liste;
    node *root;
    FILE *f;
    char filename[25];

    while(iter->next != NULL)
        iter = iter->next;
    if(iter->family->root_father == NULL)
    {
        printf("Family is not started yet!!\n");
        return;
    }
    root = iter->family->root_father;
    sprintf(filename,"%s.txt",iter->family->family_name);
    f = fopen(filename,"w");
    write_file(f,root);
    fclose(f);
    printf("Family tree is saved to the corresponding file succesfully\n");
}