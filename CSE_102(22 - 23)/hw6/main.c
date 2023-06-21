#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"
#include "query_products.h"
#include "query_stock.h"
#include "stock_control_report.h"

char part1() //ana menüyü yazdırıp seçilen option ı döndürür.
{
    char c;

    printf("\nWelcome operator, please select an option to continue:\n");
    while (1)
    {
        printf("1- File Operations\n2- Query products\n3- Check stock status\n4- Stock control by brand\n5- Export report\n");
        scanf(" %c", &c);
        if (c >= '1' && c <= '5')
        {
            break;
        }
        printf("\nPlease select a valid option!!\n");
    }
    return c;
}

void part2(int *pID, int *sID, int *feature_count)
{
    char c;
    int feature_count_sID = 4; //stock file ın feature sayısı değişmeyeceği için onu kendimiz atarız.
    while (1)
    {
        printf("Please choose an option:\n");
        while (1)
        {
            printf(" 1- Add a new product\n 2- Delete a product\n 3- Update a product\n 4- Add feature to products\n");
            printf(" 5- Add a new stock entry\n 6- Delete a stock entry\n 7- Update a stock entry\n 8- Back to main menu\n");
            scanf(" %c", &c);
            if (c >= '1' && c <= '8') // olmayan bir option seçilmesini önleriz.
            {
                break;
            }
            printf("Please select a valid option!!\n");
        }
        switch (c)
        {
        case '1':
            Add_product(pID, feature_count);
            break;
        case '2':
            Delete_Item(pID, "product.txt");
            break;
        case '3':
            Update_Item(feature_count, pID, "product.txt");
            break;
        case '4':
            Add_feature(feature_count);
            break;
        case '5':
            Add_stock(sID, pID);
            break;
        case '6':
            Delete_Item(sID, "stock.txt");
            break;
        case '7':
            Update_Item(&feature_count_sID, sID, "stock.txt");
            break;
        default:
            return;
            break;
        }
    }
}

void part3(int feature_cont, int pID)
{
    char c;

    while (1)
    {
        while (1)
        {
            printf("Please choose an option\n");
            printf("1. List all products\n2. Filter products by brand, type, price, or a user-defined feature\n3. Back to main menu\n");
            scanf(" %c", &c);
            if (c >= '1' && c <= '3')
            {
                break;
            }
            printf("Please select a valid option!!\n");
        }
        switch (c)
        {
        case '1':
            List_all_products(pID);
            break;
        case '2':
            Filter_products(feature_cont, pID);
            break;
        default:
            return;
            break;
        }
    }
}

void part4(int pID, int sID)
{
    char c;

    while (1)
    {
        while (1)
        {
            printf("Please select an option:\n");
            printf("1. Query stock by pID and branch\n2. Query stock by branch\n3. Query out of stock products by branch\n4. Back to main menu\n");
            scanf(" %c", &c);
            if (c >= '1' && c <= '4')
            {
                break;
            }
            printf("Please choose a valid option!!\n");
        }
        switch (c)
        {
        case '1':
            option1(sID,pID);
            break;
        case '2':
            option2_and_3(sID,pID,2);
            break;
        case '3':
            option2_and_3(sID,pID,3);
            break;
        default:
            return;
            break;
        }
    }
}

int main()
{
    FILE *product = fopen("product.txt", "a+");
    FILE *stock = fopen("stock.txt", "a+");
    char c = ',', ID_counter; //ID_counter, başlangıçta dosyalarda mevcut pID ve sID sayısını bulmak icin, 'c' de dosyadan okuma yapmak için
    int pID = 0, sID = 0, feature_count = 0, arr_tail = 0, arr_head = 0; // tail ve head 2D arrayde başı ve sonu tutmak için.
    float stock_control_arr[20][10]; // part5 teki array.

    for(int i = 0; i< 20; i++) //arrayin tüm elemanlarını düzgün işlem yapabilmek için -1 atarız.
    {
        for(int j = 0; j < 10; j++)
        {
            stock_control_arr[i][j] = -1;
        }
    }

    if (fgetc(product) != EOF)
    {
        rewind(product); //dosyayı her ihtamele karşı başa sararız.
        while (c != '\n' && c != EOF)
        {
            c = fgetc(product);
            if (c == ',' || c == '\n' || c == EOF)
            {
                feature_count++;  //dosyanın başlangıçtaki feature sayısını alırız.
            }
        }
        while (!feof(product))
        {
            ID_counter = fgetc(product);
            if (ID_counter == '\n' || ID_counter == EOF)
            {
                pID++; //başlangıçta girilen product sayısını tutarız.
            }
        }
    }
    if (fgetc(stock) != EOF)
    {
        rewind(stock);
        while (fgetc(stock) != '\n' && fgetc(stock) != EOF); //burda amaç girilen stock sayısını bulmak olduğu için featureların yazdığı satırı atlarız.
        while (!feof(stock))
        {
            ID_counter = fgetc(stock);
            if (ID_counter == '\n' || ID_counter == EOF)
            {
                sID++; //başlangıçta girilen stock sayısını tutarız.
            }
        }
    }

    fclose(product);
    fclose(stock);
    while (1)
    {
        c = part1(); //ana menüyü açarız ve orda seçtiğimiz optionı 'c' ye atayıp ona göre işlem yaparız.
        switch (c)
        {
        case '1':
            part2(&pID, &sID, &feature_count);
            break;
        case '2':
            part3(feature_count, pID);
            break;
        case '3':
            part4(pID,sID);
            break;
        case '4':
            Stock_Control(stock_control_arr, &arr_head, &arr_tail);
            break;
        default:
            Export(stock_control_arr,arr_tail);
            return 0;
            break;
        }
    }
}