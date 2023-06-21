#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

void Part1();
void Part2(int c_x,int c_y,int d_x,int d_y,int room_size);
int Part3(int c_x,int c_y,int d_x,int d_y);
void Part4();
void draw_room(int c_x, int c_y, int d_x, int d_y, int room_size);

void draw_room(int c_x, int c_y, int d_x, int d_y, int room_size)
{
     for(int y = room_size; y >= -1; y--)	//odanın kordinatları y ekseni için 0 dan room_size-1 e kadardır.(room_size 5 ise 0 dan 4 e kadar), y== 5 ve y == -1 de ise "---" işareti var.
    {
        for(int x = 0; x <= room_size*2; x++)	// odanın x kordinatı ise roomsize*2 kadar çünkü roomsize kadar boşluk, roomsize+1 kadar da | işareti olucak.(5 sizelı bir oda için 0 dan 10 a kadar)
        {
            if(y == room_size || y == -1)	//odanın tavan ve tabanına "-" işareti ile duvar yaparız
            printf("-");
            else
            {
                if(x % 2 == 0)			//x ekseninde çift sayılar oda geçitleri, tek sayılarda karakterin bulunacağı kordinatlardır.
                printf("|");
                else if(x == d_x && y == d_y)
                printf("D");
                else if(x == c_x && y == c_y)
                printf("C");
                else
                printf(" ");
            }
        }
        printf("\n");
    }
}

void Part1()
{
    int room_size, c_x, c_y, d_x, d_y;

    while(1)
    {
        printf("Please enter the room size(betwween 5 and 10): ");
        scanf("%d", &room_size);

        if(room_size < 5 || room_size > 10)
        printf("Room size can not be smaller than 5 or greater than 10!\n");
        else
        break;
    }
    srand(time(NULL));
    while(1)
    {
        c_x = rand()%(room_size*2);	// burdaki döngüde x kordinatı tek sayı olana kadar random sayı üretiyoruz çünkü x ekseninde çift olan kordinatlarda '|' olucak.
        if(c_x % 2 == 1)
        break;
    }
    c_y = rand()%room_size;
    while(1)
    {
        d_x = rand()%(room_size*2);
        if((d_x % 2 == 1) && (d_x != c_x)) // oyun başlarken D ve C aynı yerde olmasın diye ekstra bir koşul ekledim.
        break;
    }
    d_y = rand()%room_size;
   
    draw_room(c_x,c_y,d_x,d_y,room_size);
    Part2(c_x,c_y,d_x,d_y,room_size);	//odayı ilk başta yarattıktan sonra oyun başlar.
}

void Part2(int c_x,int c_y,int d_x,int d_y,int room_size)
{
    int moves_made = 0;
    char direction;

    while (1)
    {
        label:
        printf("Enter the direction: ");
        scanf(" %c", &direction);
        while(getc(stdin) != '\n'); //çapraz hareketi önlemek için kalan bufferı temizliyoruz.

        switch (direction)
        {
        case UP:
            c_y += 1;
            break;
        case DOWN:
            c_y -= 1;
            break;
        case RIGHT:
            c_x += 2;
            break;
        case LEFT:
            c_x -= 2;
            break;
        default:
            printf("Invalid direction!!\n");
            goto label;
            break;
        }
        if(c_x <= 0 || c_x >= room_size*2 || c_y <= -1 || c_y >= room_size) // eğer karakter duvardan geçmeye çalışırsa burdaki if e girer.
        {
            printf("The character can not pass throught the walls !!\n");
            switch (direction)	//karakterin kordinatları eskiye döndürülür.
            {
            case UP:
                c_y -= 1;
                break;
            case DOWN:
                c_y += 1;
                break;
            case RIGHT:
                c_x -= 2;
                break;
            case LEFT:
                c_x += 2;
                break;
            }
            goto label; // kullanıcıdan yeniden yön girmesi istenir.
        }
        if(Part3(c_x,c_y,d_x,d_y) == 1)	//eğer girilen yönden sonra oyun bittiyse döngü kırılır.
        {
            moves_made++;
            break;
        }
        draw_room(c_x, c_y, d_x, d_y, room_size);  // eğer oyun devam ediyorsa karakterin yeni kordinatlarıyla oda yeniden çizilir.
        moves_made++;
    }
    printf("The game is over. Thanks for playing <3\nMoves made: %d\n\n", moves_made);
    Part4(); //oyun bittikten sonra menü kısmına döndürülür.
}

int Part3(int c_x,int c_y,int d_x,int d_y)
{
    if(c_x == d_x && c_y == d_y)
    return 1;
    return 0;
}

void Part4()
{
    char selection;

    printf("\nWelcome to the 2D puzzle game!\n");
    printf("1. New game\n2. Help\n3. Exit\n");
    scanf(" %c", &selection);

    switch (selection)
    {
    case '1':
        Part1();
        break;
    case '2':
        printf("The character is able to move one space in any of the four cardinal directions: up,\n down, left, and right. The following keys: 'a' for left, 'd' for right, 'w' for up,\n and 's' for down.\n ");
        Part4();
        break;
    case '3':
        printf("Thank you for playing, Good byeee <3\n");
        exit(0);
        break;
    default:
        printf("Please select a valid option!\n");
        Part4();
        break;
    }
}

int main()
{
    Part4();
}
