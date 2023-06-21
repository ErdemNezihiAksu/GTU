#include <stdio.h>
#include <stdlib.h>
#include "query_stock.h"
#include "file_operations.h"

void filter(int sID, int selected_pID, int option, char branch[])
{

    char stock_entries[100];
    char p[20];
    char *token;
    int flag1, flag2, flag3 = 0, flag4 = 0, j, current_stock, x = 1;
    FILE *f = fopen("stock.txt", "r");

    fgets(stock_entries, sizeof(stock_entries), f); //ilk satır okunur.
    while (x <= sID) //bütün satırlar okunana kadar döngü döner.
    {
        j = 0;
        flag1 = 0;
        flag2 = 0;

        fgets(stock_entries, sizeof(stock_entries), f); //bir sonraki satır okunur ve stock_entries dizisine konur.
        token = stock_entries; //token pointer ı o diziyi gösterir.
        while (*token != ',') //sID nin olduğu kısım boyunca token ilerletilir.
        {
            token++;
        }
        token++;
        sscanf(token, "%d", &j); //token, pID nin olduğu kısma gelir ve pID okunur.
        if (j == selected_pID) //eğer okunan pID seçilen pID ile eşitse 1. flag = 1 yapılır.
        {
            flag1 = 1;
        }
        while (*token != ',') //token branch in yazdığı kısma getirilir.
        {
            token++;
        }
        token++;
        sscanf(token, "%[^,]", p);//branch okunup p ye konulur.
        if (strcmp(p, branch) == 0) //eğer okunan branch seçilen branch e eşit ise 2. flag = 1 yapılır.
        {
            flag2 = 1;
        }
        if (flag1 == 1 && flag2 == 1 && option == 1) //eğer aranan pID ve branch bulunup 1. option seçildiyse koşula girer.
        {
            flag3 = 1; //seçilen parametrelerin bulunduğunu belirtmek için 3. flag  = 1 yapılır.
            while (*token != ',')
            {
                token++; // token pointerını current_stock değerinin başına getirir.
            }
            token++;
            sscanf(token, "%d", &current_stock); // stock değeri okunur ve terminale yazılır.
            printf("Current stock: %d\n", current_stock);
            break; // eğer 1. option seçildiyse döngünün daha fazla devam etmesine gerek yoktur ve kırılır.
        }
        else if (flag2 == 1 && option == 2) //eğer seçilen branch bulunduysa ve 2. option seçildiyse koşula girer.
        {
            flag3 = 1; //seçilen paramerenin bulunduğunu belirtmek için 3. flag = 1 olur.
            while (*token != ',')
            {
                token++; //token pointer ı current stock değerinin başına getirirlir.
            }
            token++;
            sscanf(token, "%d", &current_stock); //stock değeri okunur ve terminale yazılır.
            printf("pID: %d, current stock: %d\n", j, current_stock);
        }
        else if (flag2 == 1 && option == 3) //eğer seçilen branch bulunduysa ve 3. option seçildiyse koşula girer.
        {
            flag3 = 1; //seçilen paramerenin bulunduğunu belirtmek için 3. flag = 1 olur.
            while (*token != ',')
            {
                token++;
            }
            token++;
            sscanf(token, "%d", &current_stock);
            if (current_stock == 0)
            {
                flag4 = 1; //eğer stock u 0 olan bir değer bulundysa , onu belirtmek için 4. flag = 1 yapılır.
                printf("out of stock pID: %d\n", j);
            }
        }
        x++;
    }
    if (flag3 == 0)
    {
        printf("Branch or pID is not found!!\n");
    }
    else if (option == 3 && flag4 == 0)
    {
        printf("No out of stock product is found!!\n");
    }
    fclose(f);
}

void option1(int sID, int pID)
{
    if (sID == 0)
    {
        printf("No stock entry found!!\n");
        return;
    }
    int selected_pID;
    char branch[20];
    int flag1, flag2;

    while (1) //bu döngü parametreler doğru yazılana kadar döner.
    {
        flag1 = 0;
        flag2 = 0;
        for (int i = 0; i < 20; i++)
        {
            branch[i] = '\0';
        }
        printf("Please enter the pID and the branch of the stock seperated by comma: ");
        if (scanf("%d,%[^'\n']", &selected_pID, branch) == 2) // eğer pID ve branch doğru formatta yazılmışsa flag1 = 1 olur.
        {
            flag1 = 1;
        }
        else //eğer yazılmamışlarsa hata mesajı veririz ve buffer ı  temizleriz.
        {
            printf("Invalid entries!!\n");
            scanf("%[^'\n']", branch); // buffer ı temizleriz.
        }
        if (flag1 == 1)
        {
            break;
        }
    }
    filter(sID, selected_pID, 1, branch); //seçilen parametrelere göre filtreleme yapar.
}

void option2_and_3(int sID, int pID,int option)
{
    if (sID == 0)
    {
        printf("No stock entry!!\n");
        return;
    }
    char branch[20];

    getchar();
    printf("Please enter the branch: ");
    scanf("%[^'\n']", branch);
    filter(sID,0,option,branch);
}
