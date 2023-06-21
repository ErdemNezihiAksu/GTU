#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"

void get_features(FILE *f, char feature[]) // Fıle pointerı dosyanın başını gösterirken bu fonksiyonu çağırız ve featur ları, her çağrıldığında bir tane olmak üzere array in içine koyarız
{
    int i = 0;
    char c = fgetc(f);
    while (c != ',' && c != '\n' && c != EOF)
    {
        feature[i++] = c;
        c = fgetc(f);
    }
    feature[i] = '\0';
}

int strcmp(const char *str1, const char *str2) // iki stringi karşılaştırır, stringler aynıysa 0 döndürür.
{
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2)
    {
        str1++;
        str2++;
    }
    return (*str1 == *str2) ? 0 : ((*str1 < *str2) ? -1 : 1);
}

int ft_strlen(const char *str) // bir stringin uzunluğunu bulur.
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

void write_on_temp(FILE *f, FILE *temp) // bir dosyadaki bir satırı geçici olan temp dosyasına yazar.
{
    char c;
    c = fgetc(f);
    while (c != '\n' && c != EOF)
    {
        fputc(c, temp);
        c = fgetc(f);
    }
}
void Add_product(int *pID, int *feature_count)
{
    char type, name[20], brand[20], p[20];
    float price;
    int flag = 0, result1;
    FILE *product = fopen("product.txt", "a+");

    if (fgetc(product) == EOF) // eğer dosya boşşa default featurları yazar.
    {
        fprintf(product, "pID,Type,Name,Brand,Price");
        *feature_count = 5; // feature count ı default olarak 5 yapar.
    }
label:
    printf("Please enter the features of the new product seperated by space: ");
    if (result1 = scanf(" %c %s %s %f", &type, name, brand, &price) != 4)
    {
        printf("Invalid parameter(s) found!!\n");
        getchar();
        goto label;
    }
    if (ft_strlen(name) > 8 || ft_strlen(brand) > 5)
    {
        printf("The name or the brand is too long!!\n");
        goto label;
    }
    (*pID)++;
    fprintf(product, "\n%d,%c,%s,%s,%.2f", *pID, type, name, brand, price);
    for (int i = 5; i < *feature_count; i++)
    {
        scanf("%s", p);
        fprintf(product, ",%s", p);
    }
    fclose(product);
}

void Add_feature(int *feature_count)
{
    char new_feature[20];
    FILE *product = fopen("product.txt", "r");
    int result;

    do
    {
        printf("Enter the name of the new feature: ");
        result = scanf("%s", new_feature);
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // string okunduktan sonra bufferda bir şey kaldıysa temizler.
    } while (result != 1); // yanlış bir değer girilmesi önlenir.

    FILE *temp = fopen("temp.txt", "w"); // dosyanın yeniden yazılması için geçici bir dosya oluşturulur.
    write_on_temp(product, temp);        // product file daki featurların olduğu satır temp e yazılır.
    fprintf(temp, ",%s", new_feature);   // ve featurlara yeni feature eklenir.
    while (!feof(product))               // product file ın sonuna kadar okuyup yazma işlemi devam eder.
    {
        fputc('\n', temp);            // yeni feature eklendikten sonra yeni satıra geçmek için '\n' eklenir.
        write_on_temp(product, temp); // her satır teker teker yazılır.
        fprintf(temp, ",None");       // satırların sonuna yeni feature için None yazılır.
    }
    *feature_count += 1; // feature sayısını tutan değişken bir arttırılır.
    fclose(product);
    fclose(temp);
    remove("product.txt");
    rename("temp.txt", "product.txt"); // dosyalar kapatılıp ilk product file silininp temp yeni product file yapılır.
}

void Add_stock(int *sID, const int *pID)
{
    int slct_pID;
    char branch[16], current_stock[20];
    FILE *stock = fopen("stock.txt", "a+");

    if (fgetc(stock) == EOF) //eğer stock dosyası boşsa featurları kendimiz yazarız.
    {
        fprintf(stock, "sID,pID,branch,current_stock");
    }
    while (1) // bu while branch in 15 karakterden uzun olup olmadığını kontrol eder
    {
        while (1) // bu while selected pID nin var olup olmadığını kontrol eder.
        {
            printf("Please enter pID, branch and current stock of the product seperated by space: ");
            scanf("%d %s %s", &slct_pID, branch, current_stock);
            if (slct_pID > 0 && slct_pID <= *pID)
            {
                break;
            }
            printf("Invalid pID!!\n");
        }
        if (ft_strlen(branch) > 15)
        {
            printf("the name of branch is too long!!\n");
        }
        else
            break;
    }
    *sID += 1; //stock eklendilten sonra sID 1 arttırılır.
    fprintf(stock, "\n%d,%d,%s,%s", *sID, slct_pID, branch, current_stock);
    fclose(stock);
}

void Delete_Item(int *ID, const char s[]) //burdaki s[] file ın ismidir.
{
    if (*ID == 0) //seçilen dosya boşşa eğer hata verir.
    {
        printf("No element to delete!\n");
        return;
    }
    int delete_ID, i = 1, j = 1;
    char c;
    FILE *f = fopen(s, "r"); //seçilen file read konumunda açılır.

    if (strcmp(s, "product.txt") == 0)
    {
        printf("Please enter the pID of the product you want to delete: ");
    }
    else
    {
        printf("Please enter the sID of the stock you want to delete: ");
    }
    while (1) //bu while silinecek ID nin var olup olmadığını kontrol eder
    {
        scanf("%d", &delete_ID);
        if (!(delete_ID <= 0 || delete_ID > *ID))
        {
            break;
        }
        if (strcmp(s, "product.txt") == 0)
        {
            printf("Please ınput a valid pID number: ");
        }
        else
        {
            printf("Please ınput a valid sID number:  ");
        }
    }
    FILE *temp = fopen("temp.txt", "w"); //silinecek ID belirlendikten sonra verileri geçici bir dosyaya yazmak için temp açılır.
    write_on_temp(f, temp); //dosyanın ilk satırı(featurların olduğu) temp e yazılır.
    while (i <= *ID) //seçilen dosyayı ID = 1 den son ID nin olduğu satıra kadar okur
    {
        if (i == delete_ID) //eğer dosyayı okurken silinecek satıra gelirse o satır bitene kadar okumaya devam eder(satırı temp e yazmaz).
        {
            c = fgetc(f);
            while (c != '\n' && c != EOF)
                c = fgetc(f);
        }
        else //diğer satırları silinen satırdan sonraki ID leri 1 düşürerek temp e yazarız.
        {
            while (fgetc(f) != ','); //ID nin olduğu kısmı atlarız.
            fprintf(temp, "\n%d,", j); //satır başına yeni ID(silinenden sonrakilerin 1 eksiğini) yi yazarız.
            write_on_temp(f, temp); //satırın kaldığı yerden aynen temp e yazarız.
            j++; // tempe yazacağımız ID numarasını 1 arttırırız.
        }
        i++; //okuduğumuz dosyanın bir alt satırına geçeriz.
    }
    fclose(f);
    fclose(temp);
    remove(s);
    rename("temp.txt", s);
    *ID -= 1; //toplam ID sayısını 1 azaltırız.
}

void Update_Item(const int *feature_count, const int *ID, const char s[]) //s[] file ismini temsil eder.
{
    if (*ID == 0)
    {
        printf("No item to update!!\n");
        return;
    }
    char p[20], selected_feature[20], new_value[20], c;
    int selected_ID, count, i = 1, result;
    FILE *f = fopen(s, "r"); //update edeceğimz dosyayı read konumunda açarız.

    while (1)  // bu döngü bütün error checkler geçilene kadar devam eder.
    {
        int error_check1 = 0, error_check2 = 0, error_check3 = 0, error_check4 = 0;
        if (strcmp(s, "product.txt") == 0)
        {
            printf("Please type pID number, ");
        }
        else
        {
            printf("Please type sID number, ");
        }
        printf("the feature and the new value seperated by space: ");
        scanf("%d %s %s", &selected_ID, selected_feature, new_value);

        if (selected_ID <= 0 || selected_ID > *ID) //eğer seçilen ID mevcut değilse hata verir.
        {
            if (strcmp(s, "product.txt") == 0)
            {
                printf("Invalid pID!!\n");
            }
            else
            {
                printf("Invalid sID!!\n");
            }
        }
        else //değilse ilk error check geçilir.
        {
            error_check1 = 1;
        }
        int j = 1, flag = 0;
        while (j <= *feature_count) //dosyanın ilk satırındaki her bir featurı okumak için döngü açılır.
        {
            get_features(f, p); //okunan feature p[] ye atanır.
            if (strcmp(p, selected_feature) == 0) // eğer seçilen feature okunan feature ise flag =  1 yapılır.
            {
                flag = 1;
                break;
            }
            j++;
        }
        rewind(f); //featurlar okunduktan sonra file pointer ı dosyanın başına geri gönderilir.
        if (flag != 1)  // eğer flag 1 olmadıysa yazılan feature mevcut değil demektir.
        {
            printf("Feature does not exist!!\n");
        }
        else //eğer flag 1 olduysa 2. error check geçilir.
        {
            error_check2 = 1;
        }
        if ((strcmp(selected_feature, "pID") == 0 && strcmp(s, "product.txt") == 0))
        {
            printf("pID can not be changed!!\n");
        }
        else if ((strcmp(selected_feature, "sID") == 0 && strcmp(s, "stock.txt") == 0))
        {
            printf("sID can not be changed!!\n");
        }
        else // eğer seçilen feature pID veya sID değilse 3. error check geçilir.
        {
            error_check3 = 1;
        }
        if ((strcmp(selected_feature, "Name") == 0 && ft_strlen(new_value) > 8) || (strcmp(selected_feature, "Brand") == 0 && ft_strlen(new_value) > 5) || (strcmp(selected_feature, "branch") == 0 && ft_strlen(new_value) > 15))
        {
            printf("The new value for that feature is too long!!\n");
        }
        else // eğer seçilen featurların karakter sayılar izin verilenden fazla değilse 4. error check geçilir.
        {
            error_check4 = 1;
        }
        if (error_check1 == 1 && error_check2 == 1 && error_check3 == 1 && error_check4 == 1)
        {
            break; // tüm check ler geçilirse döngü kırılır
        }
    }
    count = 1; // count değişkeni dosyada update edilecek featurın kaçınca sırada olduğunu tutar.
    while (count < *feature_count)
    {
        get_features(f, p); // dosyadan featurlar teker teker okunur.
        if (strcmp(p, selected_feature) == 0) //seçilen feature bulunduğunda döngü kırırlır ve onun kaçıncı sırada olduğu count değişkeninde tutulur.
        {
            break;
        }
        count++;
    }
    FILE *temp = fopen("temp.txt", "w"); //geçici dosya açılır.
    rewind(f); //seçilen dosya yeniden başa sarınır.
    write_on_temp(f, temp); //ilk satır yazdırılır.
    while (i <= *ID) //dosya sonuna kadar okuma işlemi yapılır.
    {
        fputc('\n', temp); //ilk ten sonraki her satırın başına '\n' konur.
        if (i == selected_ID)  //update edeceğimiz ID bulunursa if e girer.
        {
            for (int j = 1; j < count; j++) //değiştireceğimiz feature ın sırasına gelene kadar diğer özellikler aynen yazılır.
            {
                while (fputc(fgetc(f), temp) != ',');
            }
            fprintf(temp, "%s", new_value); //değiştirecğimiz feature ın yeni değeri yazılır.
            c = fgetc(f);
            while (c != ',' && c != EOF && c != '\n') //okunan dosyada değiştirilen feature ı geçilene kadar okumaya devam edilir.
            {
                c = fgetc(f);
            }
            if (c != EOF && c != '\n') //sonraki feature gelinince onları da aynen tempe yazar.
            {
                fputc(c, temp);
                write_on_temp(f, temp);
            }
        }
        else //diğer satırları aynen temp e yazarız.
        {
            write_on_temp(f, temp);
        }
        i++;
    }
    fclose(f);
    fclose(temp);
    remove(s);
    rename("temp.txt", s); //eski dosyayı silip temp i yeniden adlandırırız.
}