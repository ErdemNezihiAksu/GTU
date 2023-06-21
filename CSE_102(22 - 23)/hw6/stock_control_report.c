#include <stdio.h>
#include <stdlib.h>
#include "stock_control_report.h"
#include "file_operations.h"

int arr_len(float arr[]) //2D arrayın herangi bir satırının eleman sayısını bulmak için kullanırız.
{
    int i = 0;
    while(arr[i] != -1)
    i++;
    return i;
}

void Stock_Control(float arr[][10], int *head, int *tail)
{
    char brand[20], buffer1[100], buffer2[20], *token;
    FILE *product = fopen("product.txt", "r");
    FILE *stock = fopen("stock.txt", "r");
    float price, pID, current_stock;
    int flag, x;

    getchar(); //buffer da kalan '\n' i temizler.
    printf("Please enter brand name: ");
    scanf("%[^'\n']", brand); //seçilen brand i okuyup brand dizisine koyarız.
    fgets(buffer1, sizeof(buffer1), product); //product ın ilk satırını okuruz.
    while (fgets(buffer1, sizeof(buffer1), product) != NULL) //dosyanın sonuna kadar okuruz.
    {
        token = buffer1; //token pointer ı okunan satırı gösterir.
        sscanf(token, "%f", &pID); //satırın pID si okunup pID değişkenine atanır.
        for (int i = 0; i < 3; i++)
        {
            while (*token != ',') //token pointer ı brand in yazdığı kısma getirilir.
            {
                token++;
            }
            token++;
        }
        sscanf(token, "%[^,]", buffer2);//bradn satırdan okunarak buffer2 ye konur.
        if (strcmp(brand, buffer2) == 0) //eğer seçilen brand okunan brand e eşit ise koşula girilir.
        {
            while (*token != ',') //token pointer ı price ın yazdığı kısma getirilir.
            {
                token++;
            }
            token++;
            sscanf(token, "%f", &price); //price okunur.
            arr[*tail][0] = pID;
            arr[*tail][1] = price; //okunan price ve pID , 2D arrayin boş olan satırının ilk 2 index ine yazılır.
            *tail += 1; // 2D array da bir sonraki satıra geçilir.
        }
    }
    if(*head == *tail) //eğer başlangıç satırı ile bitiş satırı aynı ise array boş demektir ve hata mesajı verir.
    {
        printf("Brand is not  found!!\n");
        return;
    }
    fgets(buffer1, sizeof(buffer1), stock); //stock file ın ilk satırı okunur.
    while (fgets(buffer1, sizeof(buffer1), stock) != NULL) //dosya sonuna kadar satır satır okunur.
    {
        token = buffer1; //token pointer ı bu sefer stock un okuna satırını gösterir.
        flag = 0;

        while (*token != ',')
        {
            token++; //token pointer ı pID nin yazdığı kısma getirilir.
        }
        token++;
        sscanf(token, "%f", &pID); //pID okunur.
        for (x = 0; x < *tail; x++)//2D arrayin tüm satırları okunmaya başlanır.
        {
            if (arr[x][0] == pID) //eğer okunan satırın ilk index i, pID ye eşitse aradığımız ürünü stock file da bulduk demektir ve koşula girer.
            {
                flag = 1; //bulunduğunu belirtmek için flag = 1 yapılır ve döngüden çıkılır.
                break;
            }
        }
        if (flag == 1) // eğer arana ürün stock file da bulunduysa koşula girer.
        {
            for (int i = 0; i < 2; i++)
            {
                while (*token != ',') //token pointer ı current stock un yazdığı yere getirilir.
                {
                    token++;
                }
                token++;
            }
            sscanf(token,"%f",&current_stock); //stock okunur.
            int count = arr_len(arr[x]); //2D arrayin, ürünün pID sinin olduğu satırın eleman sayısı bulunur.
            arr[x][count] = current_stock; //stock, 2D arrayin, aranan ürünün pID sinin olduğu satırın boş olan bir sonraki indexine yazılır.
        }
    }
    for(int i = *head; i < *tail; i++) //2D arrayin seçilen brand inin bulunduğu satırlar boyunca döngü döner.
    {
        if(arr[i][2] == -1) //eğer eğer brand in herhangi bir ürününün stock girişi yoksa, stock un yazması gerekn index 0 yapılır.
        {
            arr[i][2] = 0;
        }
       
    }
    
    while(*head < *tail) //2D array da aranan brand in bulunduğu satırlar ekrana bastırılır.
    {
        int len = arr_len(arr[*head]);
        printf("pID: %.0f, price: %.2f, current stocks: ",arr[*head][0],arr[*head][1]);
        for(int k = 2; k<len; k++)
        {
            printf("%.0f",arr[*head][k]);
            if(k != len - 1){
                printf(", ");
            }
        }
        printf("\n");
        (*head)++;
    }
    fclose(product);
    fclose(stock);
}

void Export(float arr[][10], int tail)
{
    if(tail == 0)
    {
        printf("No stock report chosen to export!!\n");
        return;
    }
    float min, max, median, len;
    FILE *f = fopen("report.txt","w");

    fprintf(f,"pID,min stock value,max stock value,median stock value");
    for(int i = 0; i < tail; i++)//2D arrayin tüm satırları boyunca döngü döner.
    {
        len = (int)arr_len(arr[i]); //mevcut satırın eleman sayısı bulunur.
        min = arr[i][2];
        max = arr[i][2];
        median = arr[i][2]; //min max ve median value ların hepsi ilk stock değerine atanır.
        for(int j = 3; j < len; j++) //2D arrayin mevcut satırının stock larının başladıpı indexten son index e kadar döngü döner.
        {
            if(arr[i][j] < min){
                min = arr[i][j];
            }
            else if(arr[i][j] > max){
                max = arr[i][j];
            }
            median += arr[i][j]; //min ve max değerleri bulunur ve tüm değerlerin toplamı median da tutulur.
        }
        median /= len - 2; //tüm değerlerin toplamı stock sayısına bölünüp median value bulunur.
        fprintf(f,"\n%d,%d,%d,%d",(int)arr[i][0],(int)min,(int)max,(int)median);
    }
    fclose(f);
}