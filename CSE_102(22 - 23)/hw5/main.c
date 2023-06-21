#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void up_case(char *c)  //bu fonksiyonla küçük harfleri büyük harfe çeviririz.
{
    if(*c >= 97 && *c <= 122)
    *c -= 32;
}

void part1()
{
    FILE *f;
    char p[10]; //kullanıcının girdiği dosya ismini tutmak için bir dizi oluştururuz
    char c;     //dosyadaki karakterleri tutacağımız bir değişken oluştururuz. 
    int arr[26]={0}; //alfabedeki harflerden kaçar tane olduğunu tutmak için harf sayısı kadarlık bir dizi oluştururuz.
    
    while(1)
    {
        printf("Enter the file name: ");
        scanf(" %s",p);
        f = fopen(p,"r");
        if(f != NULL) //eğer dosyayı başarılı bir şekilde açabilirse döngüden çıkar.
        {
            break;
        }
        printf("File does not exist!\n");
    }
   
    while(feof(f) == 0)
    {
        c = fgetc(f);
        if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))//eğer okunan karakter bir harf ise "if" in içine girer
        {
            up_case(&c); //harf i büyük harfe çeviririz.
            arr[c-65]++; //okuduğumuz harfin dizide kendisine tekamul eden indexteki sayısını bir arttırırız.
        }                // (A, ascii de 65 e denk geliyor, eğer dosyada a veya A okursa c=65 olur c-65= 0 olur, bu sayede alfabenin ilk harfi dizinin ilk indexine denk gelir.)
    }
    fclose(f);
    for(int i = 0; i<26; i++)
    {
        printf("%c: %d\n",i+65,arr[i]); //i+65 sayesinde a dan z ye tüm harfleri büyük harf olarak yazdırırız.
    }
    
}

////////////////////////////////////////////  PART 2    /////////////////////////////////////////////////

typedef enum{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
}Color;

Color colorfunction(Color color1, Color color2)
{
    float vectors[5][3]={{1,0,0},{0,1,0},{0,0,1},{0.5,0.5,0},{0.5,0.4,0.2}}; //bütün renklerin vector değerlerini renklerin enum daki sırasına göre bir 2d array da tutarız.
    float mixed_vector[3]; //yeni oluşan rengi vektör halinde tutmak için oluştururuz.
    Color mixed_color; // en son öklid uzaklığına göre rengin hangi renge tekamul ettiğini tutması için bir değişken oluştururuz.
    float distance = 2; //öklid uzunluğunu hesaplarken kullanmak için bir değişken oluştururuz ve alttaki for döngüsüne i = 0 da girebilmek için uzunluğa büyük bir değer atarız.

    for(int i = 0; i<3; i++)
    {
        mixed_vector[i] = (vectors[color1][i] + vectors[color2][i]) / 2; //mixed_color ın vektör değerlerini hesaplarız.
    }
    for(int i = 0; i < 5; i++)
    {
        float x = sqrt(pow(mixed_vector[0]-vectors[i][0],2.0) + pow(mixed_vector[1]-vectors[i][1],2.0) + pow(mixed_vector[2]-vectors[i][2],2.0));
        // x değerine mixed_vector un sırayla diğer renklere olan öklid uzaklığını atarız.
        if(x <= distance) // eğer x değeri bulunan en küçük uzaklıktan daha küçük veya eşitse if e girer.
        {    
            distance = x; //distancı güncelleriz.
            mixed_color = i; //mixed_color ı uzaklığın en küçük bulunduğu renge eşitleriz.
        }
    }
    return mixed_color;
}
void colorMixer(Color color1, Color color2, Color (*f)(Color,Color))
{
    Color newColor; //karıştırılan rengi tutması için oluştururuz.

    newColor = (*f)(color1,color2); //renklerin karışmış halini almak için fonskiyon pointerının işaret ettiği fonskiyonu çağırırız.
    printf("Mixed Color: ");
    switch (newColor)
    {
    case RED:
        printf("RED [1,0,0]\n");
        break;
    case GREEN:
        printf("GREEN [0,1,0]\n");
        break;
    case BLUE:
        printf("BLUE [0,0,1]\n");
        break;
    case YELLOW:
        printf("YELLOW [0.5,0.5,0]\n");
        break;
    case ORANGE:
        printf("ORANGE [0.5,0.4,0.2]\n");
        break;
    default:
        break;
    }
}
void part2()
{
    char c1,c2; //kullanıcıdan alınan renkleri tutmak için oluştururuz.
    Color color1,color2; // kullanıcıdan aldığımız renkleri color tipinde tutmak için oluştururuz.
    Color (*f)(Color,Color) = &colorfunction; //colorMixer fonksiyonuna göndermek için, renkleri karıştıran bir fonksiyonu işaret eden bir fonksiyon pointerı oluştururuz.

    printf("Enter color1 (r,g,b,y,o): ");
    scanf(" %c", &c1);
    printf("Enter color2 (r,g,b,y,o): ");
    scanf(" %c", &c2);
    switch (c1)  //switch case ile kullanıcıdan alınan renkleri color tipindeki değişkenlere yerleştiririz.
    {
    case 'r':
        color1 = RED;
        break;
    case 'g':
        color1 = GREEN;
        break;
    case 'b':
        color1 = BLUE;
        break;
    case 'y':
        color1 = YELLOW;
        break;
    case 'o':
        color1 = ORANGE;
    default:
        break;
    }
    switch (c2)
    {
    case 'r':
        color2 = RED;
        break;
    case 'g':
        color2 = GREEN;
        break;
    case 'b':
        color2 = BLUE;
        break;
    case 'y':
        color2 = YELLOW;
        break;
    case 'o':
        color2 = ORANGE;
    default:
        break;
    }
    colorMixer(color1,color2,f); //renkleri karıştırmak için kullanıcıdan alınan renkleri ve fonksiyon pointer ını colorMixer a yollarız.
}

////////////////////////////////////////////  PART 3    /////////////////////////////////////////////////

void switch_player(char *current_player) //oyun sırasını güncellemek için bir fonksiyon oluştururuz.
{
    if(*current_player == 'X')
    {
        *current_player = 'O';
    }
    else
    {
        *current_player = 'X';
    }
}

void print_table(char table[3][3]) // her hamleden sonra oyunun yeni halini ekrana basmak için bir fonksiyon oluştururuz.
{
    for(int i = 0; i< 3; i++) //ilk for döngüsü satırları
    {
        for(int j = 0; j < 3; j++) //ikinci for sütunları bastırır.
        {
            printf("%c ",table[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int winner_check(char table[3][3], int counter) //her hamle yapıldığında oyunun bitip bitmediğini kontrol eden bir fonksiyon oluştururuz.
{
    for(int i = 0; i < 3; i++)
    {
        if(table[i][0] != '_' && table[i][0] == table[i][1] && table[i][1] == table[i][2]) //bir satırda üç tane x veya o var mı diye kontrol eder, eğer varsa biri kazanmış demektir, 1 döndürür.
        {
            return 1;
        }
        if(table[0][i] != '_' && table[0][i] == table[1][i] && table[1][i] == table[2][i]) //üstteki if kontrolünü sütunlar için yapar.
        {
            return 1;
        }
    }
    if(table[0][0] != '_' && table[0][0] == table[1][1] && table[1][1] == table[2][2]) //sol çarprazdan başlayarak bir oyuncu oyunu çarpraz kazanmış mı diye bakar.
    {
        return 1;
    }
    if(table[0][2] != '_' && table[0][2] == table[1][1] && table[1][1] == table[2][0]) //aynısına sağ çarpraz için bakar.
    {
        return 1;
    }
    if(counter == 9) //eğer toplamda 9 hamle yapıldıysa xox table dolmuş demektir
    {
        return 2;
    }
    return 0;
}

void part3()
{
    int row, col, counter = 0, winner;
    char table[3][3] = {{'_','_','_'},{'_','_','_'},{'_','_','_'}}; //xox table ını 2d array olarak tutarız.
    char another_game, current_player = 'X'; //ilk oyuncuyu x olarak atarız.

    while(1) // bu while oyunun sürekli devam etmesini sağlar
    {
        while(1) //bu while oyuncunun karakterini table da dolu yere mi yoksa boş yere mi koymaya çalıştığını kontrol eder. 
        {
            while(1) //bu while oyuncunun doğru row ve col değerleri giriğ girmediğinin kontrolünü yapar.
            {
                if(current_player == 'X')
                {
                    printf("Player 1 (X), ");
                }
                else
                {
                    printf("Player 2 (O), ");
                }
                printf("enter your move (row, col): ");
                scanf("%d %d", &row, &col);
                if(row >= 0 && row <= 2 && col >= 0 && col <= 2) //eğer oyuncu table sınırları içerisinde bir row ve col girmişse ilk while dan çıkılır.
                {
                    break;
                }
                printf("Invalid row and col!!\n");
            }
            if(table[row][col] == '_') // eper oyuncu table da boş olan bir yerin kordinatını girdiyse ikinci while dan çıkılır.
            {
                break;
            }
            printf("These cordinates are taken!!\n");            
        }
        table[row][col] = current_player; //kontorller yapıldıktan sonra table da girilen kordinatlara oyuncunun karakteri konur.
        counter++; //yapılan hamle sayısı arttılır.
        print_table(table); //table ekrana basılır.
        winner = winner_check(table,counter); //oyun bitti mi diye kontorl edilir
        if(winner != 0) //eğer oyun bittiyse if e girilir.
        {
            switch (winner)
            {
            case 1: // 1 değeri birinin kazandığı anlamına gelir
                if(current_player == 'X')
                {
                    printf("Player 1 (x) ");
                }
                else
                {
                    printf("Player 2 (O) ");
                }
                printf("wins!\n");
                break;
            case 2: //2 değeri berabere bitti anlamına gelir.
                printf("It's a tie!\n");
                break;
            default:
                break;
            }
            while(1) //oyuncu soruya Y veya N den farklı bir cevap verdi mi diye kontrol edilir.
            {
                printf("Do you want to play again? (Y/N): ");
                scanf(" %c",&another_game);
                if(another_game == 'Y' || another_game == 'N')
                {
                    break;
                }
                printf("Please type Y or N!!\n");
            }
            if(another_game == 'N') // eğer N girilirse ilk while dan çıkılır ve oyun biter.
            {
                break;
            }
            else // eğer Y girilirse tüm değişkenler ve table baştaki haline döndürülür.
            {
                current_player = 'O'; //current_player 'O' yapılır çünkü while ın sonunda oyun devam ediyorsa oyuncuyu değiştiren fonksiyon çağırılır.
                winner = 0;
                counter = 0;
                for(int i = 0; i < 3; i++)
                {
                    for(int j = 0; j < 3; j++)
                    {
                        table[i][j] = '_';
                    }
                }
            }
        }
        switch_player(&current_player);
    }
}

int main()
{
    part1();
    printf("\n----COLOR MİXER----\n");
    part2();
    printf("\n----XOX GAME----\n");
    part3();
}
