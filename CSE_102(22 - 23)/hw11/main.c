#include "tree.h"

int Menu()
{
    int n;
    label:
    printf("\nFamily Tree System Menu\n1. Add family\n2. Remove Family\n3. Load Family Tree\n4. Exit\n> ");
    scanf("%d",&n);
    if(n < 1 || n > 4)
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return n;
}
int subMenu1()
{
    int n;
    label:
    printf("\n1. Add Node\n2. Save Family Tree\n3. Exit\n> ");
    scanf("%d",&n);
    if(n < 1 || n > 3)
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return n;
}
int subMenu2()
{
    int n;
    label:
    printf("\nSelect an operation\n1. Add new person\n2. Remove a person\n3. Print a person's nuclear family\n4. Search Relatives of a person\n5. Return to the main menu\n> ");
    scanf("%d",&n);
    if(n < 1 || n > 5)
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return n;
}
list* subMenu3(list* liste) //bu subMenu load familys kısmında kullanılır ve seçilen family i liste de bulup onu gösteren bir pointer döndürür.
{
    if(liste == NULL)
    {
        printf("No family!!\n");
        return NULL;
    }
    int n;
    list *iter = liste;
    label:
    printf("\nListing Family Trees");
    int i;
    for(i =  1; iter !=NULL; i++,iter = iter->next)
    {
        printf("\n%d. %s.txt",i,iter->family->family_name);
    }
    printf("\n> ");
    scanf("%d",&n);
    if(n < 1 || n > i)
    {
        printf("Invalid option!!\n");
        goto label;
    }
    iter = liste;
    for(int a = 1; a < n; a++)
        iter = iter->next;
    return iter;
}

int main()
{
    list *liste = NULL, *iter;
    FILE *f;
    char filename[25], family_name[20];

    while(1)
    {
        int n = Menu();
        switch (n)
        {
        case 1:
            liste = create_new_family(liste); //yeni bir aile oluşturur, rootlarını Null yapar ve bir txt dosyası açar.
            int m = 0;
            while(m != 3)
            {
                m = subMenu1();
                switch (m)
                {
                case 1:
                    liste = Add_roots(liste); //yeni oluşturulan ailenin root larını ekler
                    break;
                case 2:
                    Save_Family_Tree(liste); //rootları eklenmiş aileyi txt dosyaaına yazar.
                    break;
                default:
                    iter = liste;
                    while(iter->next != NULL) //listenin sonunda yeni oluşturulan aile vardır.
                        iter = iter->next;
                    if(iter->family->root_father == NULL) //yeni oluşturulan aile ye root eklenmeden çıkış yapılamaz.
                    {
                        printf("\nYou can not exit before setting roots for the family!!\n");
                        m = 0;
                    }
                    break;
                }
            }
            break;
        case 2:
            if(liste == NULL)
            {
                printf("No family!!");
                break;
            }
            printf("Enter the name of the txt file of the family: ");
            scanf("%24s",filename);
            sscanf(filename,"%[^.]",family_name); //filename deki .txt kısmı çıkartılarak family name bulunur.
            liste = Remove_family_tree(liste,family_name,filename); //bulunan family name sayesinde o family ve txt dosyası silinir.
            break;
        case 3:
            iter = subMenu3(liste);  //iter pointer ı liste den seçilen aileyi gösterir ve bu aileye uygulanacak işlemlerin yapılmasını sağlar.
            if(iter == NULL)
                break;
            int a = 0;
            while(a != 5)
            {
                a = subMenu2();
                switch (a)
                {
                case 1:
                    Add_new_person(&iter); //aileye yeni kişi eklenir ve txt güncellenir
                    break;
                case 2:
                    sprintf(filename,"%s.txt",iter->family->family_name); //ailenin kaydedildiği txt nin adı file name e yazılır.
                    if(Remove_person(&iter,&liste) == 0) //seçilen kişi silinir.
                    {
                        f = fopen(filename,"w");
                        write_file(f,iter->family->root_father); //eğer silinen kişi root lardan biriyse tüm aile silineceği için txt güncelleme işlemi remove fonksiyonun dışında yapılır.
                        fclose(f);                               //eğer tüm aile silindiyse txt de silinir o yüzden txt güncelleme işlemi koşulun içinde yapılır.
                    }
                    else
                        a = 5; //eğer root silinrse family silineceği için menü den çıkılması gerekir.
                    break;
                case 3:
                    print_nuclear_family(iter);  //kişinin çekirdek ailesi ekrana bastırılır.
                    break;
                case 4:
                    Search_relatives(iter); //kişinin akrabaları aratılır.
                    break;
                default:
                    break;
                }
            }
            break;
        default:
            Deallocate_list(&liste); //programdan çıkıldığında bütün ağaçlar ve liste hafızadan silinir.
            return 0;
        }
    }
}