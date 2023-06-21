#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_funcs.h"

char Menu()
{
    char c;

label:
    printf("Choose an option\n1. Add book\n2. Delete book\n3. Update book\n4. Filter and Sort\n5. Reverse book\n6. Search book\n7. Borrow book\n8. Return book\n9. Student's borrowed books\n0. Exit\n> ");
    scanf(" %c", &c);
    if (c < '0' || c > '9')
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return c;
}

int main()
{
    Book *books = NULL, *iter1;
    Student *students = NULL, *iter2;
    FILE *f;
    char *buffer = (char *)malloc(sizeof(char) * 100); //file daki satırları tutacağımız pointer.
    char *token = (char *)malloc(sizeof(char) * MAX_STR_LENGTH); //satırdaki verileri tutacağımız pointer.
    char c;

    f = fopen("students.txt", "r"); //students file daki verileri okumaya başlarız.
    while (fgetc(f) != '\n');       //başlıkların olduğu satırı geçeriz
    while (fgets(buffer, 100, f))
    {
        int i = 0;
        Student *temp = (Student *)malloc(sizeof(Student)); //list e eklemek için yer açarız.

        temp->next = NULL; //Listenin sonuna ekleme yaptığımız için next = NULL olur.
        token = strtok(buffer, ","); //strtok ile verileri okuruz ve temp in ilgili yerine atarız.
        strcpy(temp->name, token);
        token = strtok(NULL, ",");
        strcpy(temp->ID, token);
        token = strtok(NULL, ",");
        strcpy(temp->borrowed[i], token);
        if (strcmp(temp->borrowed[i], "None\n") == 0 || (strcmp(temp->borrowed[i], "None\0") == 0))
            temp->borrowed[i][0] = '-'; // '_' karakeri dizini son indexini belirlemek için sentinal value dur. Eğer Hiç ödünç kitap yoksa 0. indexi '-' olur.
        else
        {
            temp->borrowed[++i][0] = '-';
            token = strtok(NULL, ",");
            while (token != NULL) //Eğer ödünç kitap varsa onları da strtok ile okuyup diziyi '-' ile sonlandırırız.
            {
                strcpy(temp->borrowed[i], token);
                token = strtok(NULL, ",");
                temp->borrowed[++i][0] = '-';
            }
            temp->borrowed[i - 1][strlen(temp->borrowed[i - 1]) - 1] = '\0'; // bu satırın amacı strtok satırın sonundaki kelimeyi okurken '\n' karakterinide okuyor. o karakteri '\0' ile değiştiririz.
        }
        if (students == NULL) //bu if else de temp i students list e ekleriz.
        {
            students = temp;
            iter2 = students;
        }
        else
        {
            iter2->next = temp;
            iter2 = iter2->next;
        }
        temp = NULL;
    }
    fclose(f);
    f = fopen("books.txt", "r");
    fgets(buffer, 100, f);
    while (fgets(buffer, 100, f)) //aynı okuma işlemlerini books için de yaparız.
    {
        Book *temp = (Book *)malloc(sizeof(Book));
        sscanf(buffer, "%4[^,],%29[^,],%29[^,],%d,%s", temp->ISBN, temp->title, temp->author, &(temp->public_year), temp->status);
        if (books == NULL)
        {
            books = temp;
            iter1 = books;
        }
        else
        {
            iter1->next = temp;
            iter1 = iter1->next;
        }
        temp->next = NULL;
        temp = NULL;
    }
    fclose(f);
    free(buffer);

    while (1)
    {
        c = Menu();
        switch (c)
        {
        case '1':
            Add_Book(&books);
            break;
        case '2':
            Delete_Book(&books);
            break;
        case '3':
            Update_Book(books);
            break;
        case '4':
            Filter_and_Sort(books);
            break;
        case '5':
            Reverse_book(&books);
            break;
        case '6':
            Search_Book(books);
            break;
        case '7':
            Borrow_Book(books, students);
            break;
        case '8':
            Return_Book(books, students);
            break;
        case '9':
            Student_borrowed_books(students);
            break;
        default:
            return 0;
        }
    }
}