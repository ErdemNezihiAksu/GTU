#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_funcs.h"

void Student_borrowed_books(Student *students)
{
    Student *iter = students;
    char ID[5];

    while(getchar()!= '\n');
    printf("Enter students ID: ");
    scanf("%4s",ID);
    while(getchar() != '\n');
    while (iter != NULL) //ID si girilen student listede bulunur.
    {
        if (strcmp(iter->ID, ID) == 0)
            break;
        iter = iter->next;
    }
    if (iter == NULL)
    {
        printf("Student does not exist!!\n");
        return;
    }
    if(iter->borrowed[0][0] == '-')//eğer student ın ödünç kitapları array inin ilk indexi sentinal value ise ödünç kitap yok demektir.
    {
        printf("Student has no borrowed book!!\n");
        return;
    }
    for (int i = 0; iter->borrowed[i][0] != '-'; i++)//student ın ödünç kitapları bastırılır.
    {
        printf("%s\n", iter->borrowed[i]);
    }
}

void Add_Book(Book **books)
{
    Book *iter, *temp = (Book *)malloc(sizeof(Book));
    int method;

label:
    while(getchar()!= '\n'); //yanluş bir input girildiğinde buffer ı temizler. Tüm fonskiyonlarda aynı işlevde kullanılmıştır.
    printf("Enter the ISBN, title, author and publication year in order seperated by comma: ");
    if (scanf("%[^,],%[^,],%[^,],%d", temp->ISBN, temp->title, temp->author, &(temp->public_year)) != 4)
    {
        printf("Invalid parameters!!\n");
        goto label;
    }
    iter = *books;
    while (iter != NULL)
    {
        if (strcmp(iter->ISBN, temp->ISBN) == 0) //girilen ISBN in kullanılıp kullanılmadığına bakılır.
            break;
        iter = iter->next;
    }
    if (iter != NULL)
    {
        printf("This ISBN number is not available!!\n");
        goto label;
    }
label2:
    while(getchar()!= '\n');
    printf("Choose the storing method: "); //method seçilir
    scanf("%d", &method);
    if (method != 0 && method != 1)
    {
        printf("Invalid method!!\n");
        goto label2;
    }
    strcpy(temp->status, "available"); //yeni eklenen kitabın statusu available yapılır.
    if (method == 0) //methos sıfır sa sona eklenir(FIFO)
    {
        iter = *books;
        while (iter->next != NULL)
            iter = iter->next;
        iter->next = temp;
        temp->next = NULL;
    }
    else        //method 1 se başa eklenir(LIFO)
    {
        temp->next = *books;
        *books = temp;
    }
    print_books(*books); //güncellenen liste file a yazdırılır.
}

void Delete_Book(Book **books)
{
    char ISBN[5];
    Book *iter;

    if(*books == NULL)
    {
        printf("No books to delete!!\n");
        return;
    }
    while(getchar()!= '\n');
    printf("Enter the ISBN number of the book you want to delete: ");
    scanf("%s", ISBN);

    iter = *books;
    if (strcmp((*books)->ISBN, ISBN) == 0) //eğer silinecek kitap liste başıysa root değiştirilir
    {
        *books = (*books)->next;
        free(iter);
    }
    else
    {
        while (iter->next != NULL)
        {
            if (strcmp(iter->next->ISBN, ISBN) == 0) //silinecek kitap listede bulunur
                break;
            iter = iter->next;
        }
        if (iter->next == NULL)
        {
            printf("Book could not be found!!\n");
            return;
        }
        Book *temp = iter->next;
        iter->next = temp->next;
        free(temp); //kitap silinir.
    }
    print_books(*books);
}

void Update_Book(Book *books)
{
    char ISBN[5], feature[15], value[MAX_STR_LENGTH];
    Book *iter;

    label:
    while(getchar()!= '\n');
    printf("Enter the ISBN number, feature(title,author,year,status) and the new value of the book seperated by comma: ");
    if(scanf("%[^,],%[^,],%29[^\n]",ISBN,feature,value) != 3)
    {
        printf("Invalid parameters!!\n");
        while(getchar() != '\n');
        goto label;
    }
    if(strcmp(feature,"ISBN") == 0 || strcmp(feature,"status") == 0) //ISBN ve status değişemez.
    {
        printf("ISBN or status can not be changed!!\n");
        while(getchar() != '\n');
        goto label;
    }
    if(strcmp(feature,"title") != 0 && strcmp(feature,"author") != 0 && strcmp(feature,"year") != 0 && strcmp(feature,"status") != 0)
    {
        printf("Feature does not exist!!\n"); //var olan bir featurun girilip girilmediğini kontrol eder.
        while(getchar() != '\n');
        goto label;
    }
    iter = books;
    while(iter != NULL)
    {
        if(strcmp(iter->ISBN,ISBN) == 0) //liste de kullanıcın girdiği kitap bulunur.
            break;
        iter = iter->next;
    }
    if(iter == NULL)
    {
        printf("ISBN number could not be found!!\n");
        goto label;
    }
    if(strcmp(feature,"title") == 0)
    {
        strcpy(iter->title,value);
    }
    else if(strcmp(feature,"author") == 0) //hangi featur değişecekse, o feature yeni value değerini alır.
    {
        strcpy(iter->author,value);
    }
    else if(strcmp(feature,"status") == 0)
    {
        strcpy(iter->status,value);
    }
    else if(strcmp(feature,"year") == 0)
    {
        iter->public_year = atoi(value);
    }
    print_books(books); //liste file a yazdırılır.
}

void Filter_and_Sort(Book *books)
{
    char filter[MAX_STR_LENGTH];
    int filter_choice, sort, flag;
    Book *iter, *iter1, *temp, *filtered = NULL;

    label:
    while(getchar()!= '\n');
    printf("Enter filter choice(0: author, 1: publication year),filter and sort choice(0: title, 1: author, 2: year) seperated by comma: ");
    if(scanf("%d,%[^,],%d",&filter_choice,filter,&sort) != 3)
    {
        printf("Invalid parameters!!\n");
        while(getchar() != '\n');
        goto label;
    }
    if(filter_choice != 0 && filter_choice != 1 && sort != 0 && sort != 1 && sort != 2) //filtre ve sort choice ların geçerli olup olmadığı kontrol edilir
    {
        printf("Invalid filter or sort choice!!\n");
        while(getchar() != '\n');
        goto label;
    }
    iter = books;
    iter1 = filtered; //filtrelenen kitapların sort lan mış hali filtered adlı liste de tutlacak
    while(iter != NULL)
    {
        flag = 0;
        if(filter_choice == 0 && strcmp(iter->author,filter) == 0)
        {
            temp = allocate_memory_for_book(iter); // filter choice a göre filtreyle uyuşan kitaplar için filtered listesine eklenmek üzere hafıza ayrılır.
            flag = 1;
        }
        else if(filter_choice == 1 && iter->public_year == atoi(filter))
        {
            temp = allocate_memory_for_book(iter);
            flag = 1;
        }
        if(flag == 1)  //eğer iter in gösterdiği kitap filtreye uyuyorsa koşula girer.
        {
            if(filtered == NULL) //filtered boşşa ilk eleman olarak temp i ekler.
            {
                filtered = temp;
                temp->next = NULL;
                temp = NULL;
            }
            else if(sort == 0)  //bu else if bloklarında sort choice a göre filtreye giren kitapları listeye yerleştirir.
            {
                iter1 = filtered;
                if(strcmp(temp->title,filtered->title) < 0) //title a göre alfabetik ekleme yapar. Eğer eklenen kitap listenin başına gelicekse root değiştirilir.
                {
                    temp->next = filtered;
                    filtered = temp;
                }
                else
                {
                    while(iter1->next != NULL && strcmp(iter1->next->title,temp->title) < 0)
                        iter1 = iter1->next;
                    temp->next = iter1->next;
                    iter1->next = temp;
                }
            }
            else if(sort == 1)
            {
                iter1 = filtered;
                if(strcmp(temp->author,filtered->author) < 0) // author a göre ekleme yapar.
                {
                    temp->next = filtered;
                    filtered = temp;
                }
                else
                {
                    while(iter1->next != NULL && strcmp(iter1->next->author,temp->author) < 0)
                        iter1 = iter1->next;
                    temp->next = iter1->next;
                    iter1->next = temp;
                }
            }
             else if(sort == 2)
            {
                iter1 = filtered;
                if(temp->public_year < filtered->public_year) //publication year a göre ekleme yapar.
                {
                    temp->next = filtered;
                    filtered = temp;
                }
                else
                {
                    while(iter1->next != NULL && iter1->next->public_year < temp->public_year)
                        iter1 = iter1->next;
                    temp->next = iter1->next;
                    iter1->next = temp;
                }
            }
        }
        iter = iter->next;
    }
    if(filtered == NULL) //eğer liste boş kaldıysa filtreye uyan kitap yok demektir.
    {
        printf("No matched books according to the filter!!\n");
        while(getchar() != '\n');
        return;
    }
    iter1 = filtered;
    while(iter1 != NULL) //filtered listesi ekrana batırılır.
    {
        printf("%s,%s,%s,%d,%s\n",iter1->ISBN,iter1->title,iter1->author,iter1->public_year,iter1->status);
        iter1 = iter1->next;
    }
}

void Reverse_book(Book **book)
{
    Book *iter, *iter1, *reversed = NULL, *temp;
    FILE *f;

    iter = *book;
    while(iter != NULL)
    {
        temp = allocate_memory_for_book(iter); //revered listesine eklenmek için temp pointerına books listesinden okunan elemanlar yerleştirilir.
        temp->next = reversed;
        reversed = temp; //her ekleme reversed listesinin başına yapılır bu sayede books listesi ters dönmüş olur.
        iter = iter->next;
    }
    *book = reversed; //sonra asıl book listesinin root u reversed listesini gösterir.

    f = fopen("books.txt","w"); //liste ekrana ve file a yazdırılır. 
    if(f == NULL)
    {
        printf("FILE could not be open!!\n");
        return;
    }
    printf("\nISBN,title,author,year,status\n");
    fprintf(f,"ISBN,title,author,year,status");
    iter = *book;
    while(iter != NULL)
    {
        printf("%s,%s,%s,%d,%s\n",iter->ISBN,iter->title,iter->author,iter->public_year,iter->status);
        fprintf(f,"\n%s,%s,%s,%d,%s",iter->ISBN,iter->title,iter->author,iter->public_year,iter->status);
        iter = iter->next;
    }
    fclose(f);
}

void Search_Book(Book *books)
{
    int choice;
    char value[MAX_STR_LENGTH];
    int flag;
    Book *iter, *iter1, *list = NULL, *temp; //list pointer ı aranan parametrelere uyan kitapları gösteren listenin root udur.

    label:
    while(getchar()!= '\n');
    printf("Enter the choice(0: ISBN, 1: author, 2: title) and value seperated by comma: ");
    if(scanf("%d,%29[^\n]",&choice,value) != 2)
    {
        printf("Invalid parameters!!\n");
        goto label;
    }
    while(getchar() != '\n');
    if(choice != 1 && choice != 2 && choice != 0)
    {
        printf("Invalid choice!!\n");
        goto label;
    }
    iter = books;
    while(iter != NULL)
    {
        flag = 0;
        if(choice == 0 && strcmp(iter->ISBN,value) == 0) //filter fonskiyonundaki gibi, choice a uyan kitap parametrelerini temp e alırız.
        {
            temp = allocate_memory_for_book(iter);
            flag = 1;
        }
        else if(choice == 1 && strcmp(iter->author,value) == 0)
        {
            temp = allocate_memory_for_book(iter);
            flag = 1;
        }
        else if(choice == 2 && strcmp(iter->title,value) == 0)
        {
            temp = allocate_memory_for_book(iter);
            flag = 1;
        }
        if(flag == 1) //eğer choice a uyan bir kitap bulunduysa koşula girer.
        {
            temp->next = NULL;
            if(list == NULL) //kitep  list e eklenir.
            {
                list = temp;
                iter1 = list;
            }
            else
            {
                iter1->next = temp;
                iter1 = iter1->next;
            }
        }
        iter = iter->next;
    }
    if(list == NULL)
    {
        printf("No book is found checking with the parameters\n");
        return;
    }
    printf("\nISBN,title,author,year,status\n");
    iter = list;
    while(iter != NULL)  //liste ekrana batırılır.
    {
        printf("%s,%s,%s,%d,%s\n",iter->ISBN,iter->title,iter->author,iter->public_year,iter->status);
        iter = iter->next;
    }
}

void Borrow_Book(Book *books, Student *students)
{
    char ISBN[5], ID[5];
    Book* iter;
    Student *iter1;

    label:
    while(getchar()!= '\n');
    printf("Enter the ISBN of the book and ID of the student seperated by comma: ");
    if(scanf("%4[^,],%4s",ISBN,ID) != 2)
    {
        printf("Invalid Parameters!\n");
        while(getchar() != '\n');
        goto label;
    }
    iter = books;
    while(iter != NULL)
    {
        if(strcmp(iter->ISBN,ISBN) == 0) //iter pointer ı hangi kitabın kiralanacağını gösterir.
            break;
        iter = iter->next;
    }
    if(iter == NULL)
    {
        printf("ISBN does not exist!!\n");
        return;
    }
    if(strcmp(iter->status,"borrowed") == 0) //kitabın çoktan kiralanıp kiralanmadığına bakılır.
    {
        printf("This book is borrowed!!\n");
        return;
    }
    iter1 = students;
    while(iter1 != NULL)
    {
        if(strcmp(iter1->ID,ID) == 0) //iter1 pointerı hangi öğrencinin kiraladaığını gösterir.
            break;
        iter1 = iter1->next;
    }
    if(iter1 == NULL)
    {
        printf("ID does not exist!!\n");
        return;
    }
    int i;
    for(i = 0; iter1->borrowed[i][0] != '-'; i++); //Öğrenci max 5 kitap alabilir.
    if(i == 5)
    {
        printf("Student can not borrow more than 5 books!!\n");
        return;
    }
    strcpy(iter1->borrowed[i], iter->title); //öğrenicinin borrowed arrayine kitap eklenir ve bir sonraki indexe sentinal value koyulur.
    iter1->borrowed[++i][0] = '-';
    strcpy(iter->status,"borrowed"); //kiralanan kitap ın status ü borrowed yapılır.

    print_students(students); //güncellenen öğrenci ve kitap listeleri dosyalara yazılır.
    print_books(books);
}

void Return_Book(Book* books, Student *students)
{
    char ISBN[5], ID[5];
    Book* iter;
    Student *iter1;
    FILE *f;

    label:
    while(getchar()!= '\n');
    printf("Enter the ISBN of the book and ID of the student seperated by comma: ");
    if(scanf("%4[^,],%4s",ISBN,ID) != 2)
    {
        printf("Invalid Parameters!\n");
        while(getchar() != '\n');
        goto label;
    }
    iter = books;
    while(iter != NULL)
    {
        if(strcmp(iter->ISBN,ISBN) == 0) //iter iade edilecek kitabı gösterir.
            break;
        iter = iter->next;
    }
    if(iter == NULL)
    {
        printf("ISBN does not exist!!\n");
        return;
    }
    if(strcmp(iter->status,"available") == 0)
    {
        printf("This book is  already available!!\n");
        return;
    }
    iter1 = students;
    while(iter1 != NULL)
    {
        if(strcmp(iter1->ID,ID) == 0) //iter1 kitabı kiralayan öğrenciyi gösterir.
            break;
        iter1 = iter1->next;
    }
    if(iter1 == NULL)
    {
        printf("ID does not exist!!\n");
        return;
    }
    int i,a;
    for(a = 0; strcmp(iter1->borrowed[a],iter->title) != 0 && iter1->borrowed[a][0] != '-'; a++); //a, kitabın borrowed arrayinde hangi indexte olduğunu belirtir.
    for(i = 0; iter1->borrowed[i][0] != '-'; i++); //i, '-' sentinal value nun hangi index te oldıuğunu belirtir.
    if(iter1->borrowed[a][0] == '-')
    {
        printf("Student does not have the book!!\n");
        return;
    }
    for(int x = a; x < i; x++) //a ve i arasındaki tüm indexler bir aşağıya kaydırlır(i deki '-' senitinal value da dahil).
        strcpy(iter1->borrowed[x],iter1->borrowed[x+1]);
    strcpy(iter->status,"available"); //kitabın status ü değiştirilir.

    print_books(books);
    print_students(students);
}