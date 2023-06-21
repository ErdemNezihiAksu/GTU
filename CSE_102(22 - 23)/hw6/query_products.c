#include <stdio.h>
#include <stdlib.h>
#include "query_products.h"
#include "file_operations.h"

void List_all_products(int pID)
{
    if(pID == 0) //eğer dosya boşşa hata mesajı verir.
    {
        printf("No product to list!!\n");
        return;
    }
    char s[1000]; //her bir satırın tutulması için bir dizi açılır.
    FILE *f = fopen("product.txt", "r");

    while (!feof(f))
    {
        fgets(s, sizeof(s), f); // her bir satır s[] ye aktarılır ve terminale basılır.
        printf("%s", s);
    }
    printf("\n");
    fclose(f);
}

void Filter_products(int feature_count, int pID)
{
    if(pID == 0)
    {
        printf("No product to filter!!\n");
        return;
    }
    char filters[10][20], values[10][20], buffer[100], features[20];
    float prices[2];
    char *token;
    int indexes[20], flag1 , flag2, flag3,flagPrice, filter_count, value_count, i;
    FILE *product = fopen("product.txt","r");

    while (1) //bu döngü bütün error checkler (flag lar) geçilene kadar döner. Amaç Filtreleme parametlerinin doğru girilmesini sağlamaktır.
    {
        for(int i = 0; i< 10; i++){ //filtreleri(seçilen featur ları) ve değerleri tutacağımız dizilerin tüm indexleri '\0' yapılır.
            for(int j = 0; j <20; j++){
                filters[i][j] = '\0';
                values[i][j] = '\0';
            }
        }
        for(int i = 0; i< 100; i++){ //scanf ile bir bütün olarak alacağımız stringi tutacağımız array da '\0' yapılır.
            buffer[i] = '\0';
        }
        for(int i = 0; i<20;i++){ //seçilen featur ların sıralarının tutlacağı dizinin elemanları 0 ile başlatılır.
            indexes[i] = 0;
        }
        prices[0] = 0; //eğer Price seçilirse diye min ve max değerlerinin tutlacağı arrayin indexleri 0 yapılır.
        prices[1] = 0;
        filter_count = 0;
        value_count = 0;
        i = 0;
        flag1 = 0; //error_check ler 0 ile başlatılır.
        flag2 = 0;
        flag3 = 0;
        flagPrice = 0;
        getc(stdout); // döngünün birden fazla dönmesi halinde buffer da kalan '\n' karakterini temizler.
        printf("Please enter the filter(s) and the values(s) you want to apply: ");
        scanf(" %[^'\n']", buffer);//yazılan parametler bütün bir string olarak okunup buffer a atılır.
        token = buffer; //token pointer ı buffer ı gösterir.
        while (*token != '\0') // döngü tüm parametreler okunana kadar döner.
        {
            sscanf(token, "%[^,]", filters[i]); //ilk okunan parametre bir feature olması gerektiğinden filter dizisine atılır.
            filter_count++;//okunan filter sayısı bir arttırılır.
            while (*token != ',' && *token != '\0')
            {
                token++; //token pointer ının bir sonraki parametreyi göstermesi için pointer ilerletilir.
            }
            if (*token == ',')
            {
                token++;
            }
            else if (*token == '\0') // eğer buffer ın sonuna gelindiyse döngü kırılır.
            {
                break;
            }
            if (strcmp(filters[i], "Price") == 0) //eğer seçilen filter Price ise koşula girer.
            {
                flagPrice = 1; // seçilen filtrelerde flag olduğunu belirtmek için flag = 1 yapılır.
                if(sscanf(token, "%f %f", &prices[0], &prices[1]) == 2){
                    flag1 = 1; //Price tan sonra yazılan parametre doğru ise(min ve mac value yazılmış ise) 1. flag = 1 olur.
                }
            }
            else //eğer seçilen filter price değilse token ın gösterdiği parametre bir string olarak okunur ve values dizisine atılır.
            {
                sscanf(token, "%[^,]", values[i]);
            }
            value_count++; //okunan value sayısı bir arttırılır.
            while (*token != ',' && *token != '\0') //aynı şekilde token ın bir sonraki parametreyi göstermesi için pointer ilerletilir
            {
                token++;
            }
            if (*token == ',')
            {
                token++;
            }
            i++; //dizilerin bir sonraki index ine geçilir.
        }
        if(filter_count == value_count){ //eğer filter sayısı ile value sayısı eşit ise girilen parametre sayısı doğrudur ve 2. flag geçilir.
            flag2 = 1;
        }
        for(int i = 1; i <= feature_count; i++) //bu döngünün amacı seçilen featur ların mevcut olup olmadığını kontrol etmek.
        {
            get_features(product,features); // her bir feature sırayla okunur.
            for(int j = 0; j < filter_count; j++)
            {
                if(strcmp(features,filters[j]) == 0){ //okunan feature filter dizisinin bütün indexleryile karşılaştırılır.
                    flag3++; //eğer bir eşleşme çıkarsa 3. flag 1 arttırlır. 3. flag filter_count a eşit olursa, seçilen bütün featurlar product file da mevcut demektir.
                    indexes[j] = i; //seçilen her bir feature ın sırası(pID 1., Type 2., Name 3. gibi) index dizisinin filter dizisiyle aynı index ine kaydedilir.
                }
            }
        }
        rewind(product);//okunan dosya başa sarılır.
        if((flagPrice == 0 && flag3 == filter_count && flag2 == 1) || (flagPrice == 1 && flag1 == 1 && flag3 == filter_count && flag2 == 1)){ //error checkler geçildiyse döngü kırılır.
            break;
        }
        else{
            printf("Parameters are invalid or missing!!\n");
        }
    }

    char p[20] = {0}, products[100], c;
    char *token2 ;
    int count = 0, j, x = 1, flag5 = 0;
    float price = 0;

    fgets(products,sizeof(products),product); //product file ın ilk satırı products dizisine konur ve bastırılır.
    printf("\n%s",products);
    while(x <= pID) //döngü dosyanın sonuna gelene kadar devam eder.
    {
        count = 0;
        price = 0;
        fgets(products,sizeof(products),product);//dosyanın öbür satırı products dizisine konur.
        token2 = products; //token2 pointerı products ı gösterir.
        for(int i = 1; i<=feature_count; i++) //satırdaki tüm featurlar okunana kadar döngü döner.
        {
            if(i == feature_count){ //eğer satırdaki son indexe geldisysek satır sonuna kadar, gelmediysek bir sonraki virgül e kadar olan kısım p dizisine konur.
                sscanf(token2,"%s",p);
            }
            else{
                sscanf(token2,"%[^,]",p);
            }
            for(j = 0; j<filter_count; j++)
            {
                if(i == indexes[j]){ //satırdan okunan featuren sırası, indexes dizisinin içinde mevcutsa döngüyü kırar. Bunun amacı okunan feauter ın filtelenip filtrelenmeyeceğini anlamak.
                    break;
                }
            }
            if(j != filter_count) //şayet yukardaki döngü kırıldıysa j değişkeninde filtrelencek olan featur ın sırası bulunut ve filter_count a eşit olmaz.
            {
                if(i != 5) //eğer satırdan okunan feature Price değilse(Price 5. feature dur.) koşula girer.
                {
                    if(strcmp(p,values[j]) == 0){ //eğer p de tutulan değer values ın içindeki değere eşitse bir filtreyle eşleşen değer bulunmuş demektir.
                        count++; // filtreyle eşlenen değer bulunursa count 1 arttırılır.
                    }
                }
                else // Eğer satırdan okunan feature Price ise else e girer.
                {
                    sscanf(p,"%f",&price); //p de tutlan değeri float olarak okur.
                    if(price >= prices[0] && price <= prices[1]){ // eğer değer min ve max value nun arasındaysa filtreyle eşleşen değer bulunmuştur.
                        count++; // filtreyle eşlenen değer bulunursa count 1 arttırılır.
                    }
                }
            }
            while (*token2 != ',' && *token2 != '\0') //token pointer ının bir sonraki feature ı göstermesi için pointer ilerletilir.
            {
                token2++;
            }
            if (*token2 == ',')
            {
                token2++;
            }
        }
        if(count == filter_count){ //eğer filtreyle eşleşen değer sayısı filter_count a eşitse o satırdaki product filtreye uyuyor demektir.
            flag5 = 1; //filtreye uyan bir satır bulunursa flag = 1 yapılır.
            printf("%s",products); //o satır terminale bastırılır.
        }
        x++; //product file da bir sonraki satıra geçilir.
    }
    if(flag5 == 0){ //eğer filtreye uyan bir satır yoksa hata mesajı verir.
        printf("No products matching the filters!!\n");
    }
    printf("\n");
    fclose(product);
}