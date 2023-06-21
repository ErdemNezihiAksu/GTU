#ifndef LIBRARY_OPERATIONS_H
#define LIBRARY_OPERAATIONS_H
#define MAX_STR_LENGTH 30
typedef struct n
{
    char ISBN[5];
    char title[MAX_STR_LENGTH];
    char author[MAX_STR_LENGTH];
    int public_year;
    char status[10];
    struct n* next;
}Book;
typedef struct m
{
    char name[MAX_STR_LENGTH];
    char ID[5];
    char borrowed[6][MAX_STR_LENGTH];
    struct m* next;
}Student;
void Student_borrowed_books(Student *students);
void Add_Book(Book **books);
void Delete_Book(Book **books);
void Update_Book(Book *books);
void Filter_and_Sort(Book *books);
void Reverse_book(Book **book);
void Search_Book(Book *books);
void Borrow_Book(Book *books, Student *students);
void Return_Book(Book* books, Student *students);
#endif