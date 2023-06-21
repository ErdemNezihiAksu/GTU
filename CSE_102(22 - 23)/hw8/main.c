#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct  n
{
    char board[3][3];
    int move_count;
}puzzle;

char Menu()
{
    char c;
    printf("\n\nWelcome to the 8-Puzzle Game\nPlease select an option:\n");
    label:
    printf("1. Play game as user\n2. Finish the game with PC\n3. Show the best score\n4. Exit\n\n>");
    scanf(" %c",&c);
    if(c < '1' || c > '4')
    {
        printf("INVALID OPTION!!\n");
        goto label;
    }
    return c;
}

int is_game_over(puzzle game) //board un sıralı olup olmadığını kontrol eder.
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(i == 2 && j == 2) //Eğer board sıralıysa, yani oyun bitmişse, board un son indeksi '_' olacağından kodu alttaki koşula girmeden döngüden çıkartırız.
                continue;
            if(game.board[i][j] - '0' != (i*3) + j +1) // Bu koşul board daki her bir sayının doğru yerde olup olmadığını kontrol eder. '_' karakterini etmez.
                return 0;
        }
    }
    return 1;
}

int getInvCount(char board[])//puzzle ın çözülüp çözülemeyeceğini konrol etmek için invasion count ı bulur.
{
    int inv_count = 0;

    for(int i = 0; i < 8; i++)
    {
        for(int j = i+1; j < 9; j++)
        {
            if(board[i] != '_' && board[j] != '_' && board[i] < board[j])
                inv_count++;
        }
    }
    return inv_count;
}

void Create_Board(puzzle *game)// puzzle ı(board u) oluşturur.
{
    char arr[] = {'1','2','3','4','5','6','7','_','8'};

label:
    for(int i = 8; i>0 ; i--) // yukardaki dizinin elemanlarını karıştırır.
    {
        int j = rand() % (i+1);
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    
    if(getInvCount(arr) % 2 != 0)//dizinin invasion coun tı bulup, puzzle ın çözülüp çözülemeyeceğini kontrol eder. Eğer çözülemiyorsa yeniden karıştırır.
        goto label;

    for(int i = 0; i < 3; i++) //karışmış elemanları board a yerleştirir.
    {
        for(int j = 0; j < 3; j++)
        {
            game->board[i][j] = arr[i*3 + j];
        }
    }
    if(is_game_over(*game) == 1)//eğer board, sıralı bir haldeyse yeniden elemanları karıştırır.
        goto label;
}

void print_board(puzzle game) //board ı her hamleden sonra txt ye bastırır.
{
    FILE *f = fopen("puzzle.txt","a");
    if(f == NULL)
    {
        printf("Fıle could not be open!!\n");
        return;
    }
    if(game.move_count != 0)
        fprintf(f,"\n\n");
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            fprintf(f,"%c ",game.board[i][j]);
            //printf("%c ",game.board[i][j]);
        }
        if(i != 2)
        {
            fprintf(f,"\n");
            //printf("\n");
        }
    }
    fclose(f);
}

int is_move_doable(puzzle *game, char num, char dir)//hareketin yapılıp, yapılamayacağını kontorl eder, eğer yapılabiliyorsa o hareketi yaptırır ve board u günceller.
{
    int i , j, flag = 0;
    char temp;

    for(i = 0; i < 3; i++) //Seçilen sayının indexi bulunur.
    {
        for(j = 0; j < 3; j++)
        {
            if(game->board[i][j] == num)
            {
                flag = 1;
                break;
            }
        }
        if(flag == 1)
            break;
    }

    if(dir == 'R')//Eğer sayı sağa götürülmek isteniyorsa, sayının sağındaki indexte '_' karakterinin olup olmaıdğına bakılır.
    {
        if(game->board[i][j+1] == '_') //eğer hareket yapılabiliyorsa, '_' karakteri ile sayının indexleri değişilir.
        {
            game->board[i][j+1] = num;
            game->board[i][j] = '_';
            return 1;
        }
    }
    else if(dir == 'L') //diğer bütün koşullarda ilk koşulla aynı çalışır.
    {
        if(game->board[i][j-1] == '_')
        {
            game->board[i][j-1] = num;
            game->board[i][j] = '_';
            return 1;
        }
    }
    else if(dir == 'U')
    {
        if(game->board[i-1][j] == '_')
        {
            game->board[i-1][j] = num;
            game->board[i][j] = '_';
            return 1;
        }
    }
    else if(dir == 'D')
    {
        if(game->board[i+1][j] == '_')
        {
            game->board[i+1][j] = num;
            game->board[i][j] = '_';
            return 1;
        }
    }
    return 0; //eğer hareket yapılamıyorsa 0 döndürülür.
}

void play_as_user(puzzle *game)
{
    char num, dir;
    int best_score, score;
    FILE *f, *f1, *f2;
    
    f = fopen("puzzle.txt","w");
    fclose(f);
    f1=  fopen("best_score.txt","r");
    if(f1 == NULL)
    {
        printf("Score file could not be open!!");
        return;
    }
    Create_Board(game); //puzzle ı oluşturur.
    print_board(*game); //puzzle ı txt ye basar.
    while (is_game_over(*game) == 0) // oyun bitene kadar döngü devam eder.
    {
        label:
        printf("\n\nEnter your move (number-direction, i.g, 2-R): ");
        scanf(" %c",&num);
        getchar(); //getchar ın amacı kullanıcıdan sayıyı aldıktan sonra '-' işaretini atlamak.
        scanf(" %c",&dir);
        while(getchar() != '\n');//sayı ve yön alındıktan sonra her ihtimale karşı buffer temizlenir.
        if((num < '1' || num > '8') || (dir != 'R' && dir != 'L' && dir != 'U' && dir != 'D'))
        {
            printf("INVALID PARAMETERS!!"); // parametrelerin doğru girilip girilmediğini kontrol eder.
            goto label;
        }
        if(is_move_doable(game,num,dir) == 0)//parametreler doğruysa, hamlenin yapılıp yapılamayacağı konrol edilir.
        {
            printf("THIS MOVE IS NOT DOABLE!!");
            goto label;
        }
        game->move_count++; //hamle yapıldıktan sonra move_count bir arttırlır.
        print_board(*game); //board ın güncel hali txt ye basılır.
    }
    score = 1000-10*game->move_count; //oyun bittikten sonra score hesaplanır.
    fscanf(f1,"%d", &best_score); //best_score dosyasından best score okunur.
    fclose(f1);
    printf("\nCongratulations! You finished the game\n\n");
    printf("Total moves made: %d\nYour score: %d",game->move_count, score);
    if(score > best_score) // eğer score best_score dan daha yüksek ise ekrana yeni best_score bastırılır ve best_score dosyası güncellenir.
    {
        printf("\nNew Best Score!!: %d",score);
        f2 = fopen("best_score.txt","w");
        fprintf(f,"%d",score);
        fclose(f2);
    }
    game->move_count = 0; // yapılan hamle sayısı sıfırlanır.
}

void auto_finish(puzzle *game, int i, int j)
{
    int move;
    char dir, num;

    if(game->move_count == 174000)//174000 hamleden sonr stackoverflow olduğundan dolayı bir hata mesajı bastırılır.
    {
        printf("\nToo much move made to handle, computer could not finish the game!!\n");
        game->move_count = 0; //move count her oyun bittikten sonra sıfırlanır.
        return;
    }
    if(is_game_over(*game) == 1) //eğer oyun bittyse gerekli mesajlar ekrana bastırılır.
    {
        printf("\nComputer finished the game\n\n");
        printf("Total number of computer moves: %d",game->move_count);
        game->move_count = 0; //move count her oyun sonu sıfırlanır.
        return;
    }
    label:
    move = rand()%4 +1; //1 ile 4 arası rastgele bir sayı tutulur. bunlar yönleri ifade eder. 1 -> sağ, 2->aşağı, 3->sol, 4->yukarı yı ifade eder.
    if(move == 1) //sağ tarafa hamle yapılacak ise koşula girer.
    {
        if(j == 0) //eğer sağ tarafa hamle yapılacak ise '_' karakterinin bulunduğu index matrisin j = 0 indexinde olmamalıdır. Bu durumda yeni bir yön seçilir.
            goto label;
        dir = 'R'; //direction değişkenine yön atanır.
        num = game->board[i][j-1]; //'_' karakterinin solundaki sayı num değişkenine atanır.
        j = j-1; //'_' karakterinin yeni i ve j indexleri hesaplanır. Sağ a hamle durumunda i indexi değişmez ama j indexi bir azalır.
    }            //diğer koşullarda aynı manıtkta çalışır.
    else if(move == 2) //go down
    {
        if(i == 0)
            goto label;
        dir = 'D';
        num = game->board[i-1][j];
        i = i-1;
    }
    else if(move == 3)//go left
    {
        if(j == 2)
            goto label;
        dir = 'L';
        num = game->board[i][j+1];
        j = j+1;
    }
    else //go up
    {
        if(i == 2)
            goto label;
        dir = 'U';
        num = game->board[i+1][j];
        i = i+1;
    }
    is_move_doable(game,num,dir); //seçilen sayı ve yön bu fonskiyona gönderilip hamle yapılır ve board güncellenir.
    game->move_count++;
    print_board(*game); //güncellenen board txt ye bastırılır.
    auto_finish(game,i,j); //'_' karakterinin yeni i ve j indexi ile board un güncel hali recursive fonksiyona gönderilir.
}

int main()
{
    puzzle game;
    FILE *f;
    int best_score, i ,j, flag;
    char c;

    game.move_count = 0;
    srand(time(NULL));

    do
    {
        c = Menu();
        switch (c)
        {
        case '1':
            play_as_user(&game);
            break;
        case '2':
            flag = 0;
            f = fopen("puzzle.txt","w"); //puzzle txt yi temizlemek için dosa write konumda açılıp kapatılır.
            fclose(f);
            Create_Board(&game); //yeni puzzle oluştururlur.
            print_board(game); //puzzle txt ye basılır.
            for(i = 0; i < 3; i++)
            {
                for(j = 0; j < 3; j++)
                {
                    if(game.board[i][j] == '_')  //'_' karakterinin i ve j indexleri bulunur.
                    {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 1)
                    break;
            }
            auto_finish(&game,i,j); //puzzle, ve '_' karakterinin indexleri recursive fonksiyona gönderilir.
            break;
        case '3':
            f = fopen("best_score.txt","r"); //score dosyası açılır.
            fscanf(f,"%d",&best_score); //best score okunur
            printf("\nBest score so far: %d\n", best_score); //ekrana bastırılır.
            fclose(f);
            break;
        default:
            break;
        }
    }while(c != '4');
}