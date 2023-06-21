#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H
#include <stdio.h>

void Add_product(int*,int*);
void Add_feature(int*);
void Add_stock(int*,const int*);
void Delete_Item(int*,const char[]);
void Update_Item(const int *,const int *,const char[]);
void get_features(FILE *,char[]);
int strcmp(const char *, const char *);
#endif