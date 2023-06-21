#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper_funcs.h"

void print_students(Student *students) // students list i students file a basar.
{
    Student *iter = students;
    FILE *f;
    f = fopen("students.txt", "w");
    if (f == NULL)
    {
        printf("Student File could not be open!!\n");
        return;
    }
    fprintf(f, "Name,ID,Borrowed_books");
    iter = students;
    while (iter != NULL)
    {
        fprintf(f, "\n%s,%s", iter->name, iter->ID);
        if (iter->borrowed[0][0] == '-')
            fprintf(f, ",None");
        for (int i = 0; iter->borrowed[i][0] != '-'; i++)
            fprintf(f, ",%s", iter->borrowed[i]);
        iter = iter->next;
    }
    fclose(f);
}

void print_books(Book *books) //books list i books file a yazdırır.
{
    Book *iter = books;
    FILE *f;
    f = fopen("books.txt", "w");
    if (f == NULL)
    {
        printf("Book File could not be open!!\n");
        return;
    }
    fprintf(f, "ISBN,title,author,year,status");
    iter = books;
    while (iter != NULL)
    {
        fprintf(f, "\n%s,%s,%s,%d,%s", iter->ISBN, iter->title, iter->author, iter->public_year, iter->status);
        iter = iter->next;
    }
    fclose(f);
}

Book *allocate_memory_for_book(Book *iter) //filter book, search book gibi geçici liste oluşturan fonskiyonlarda kullanılır. Yeni kitap için hafıza oluşturulur.
{
    Book *temp = (Book*)malloc(sizeof(Book));
    strcpy(temp->author, iter->author);
    strcpy(temp->title, iter->title);
    strcpy(temp->ISBN, iter->ISBN);
    strcpy(temp->status, iter->status);
    temp->public_year = iter->public_year;
    return temp;
}