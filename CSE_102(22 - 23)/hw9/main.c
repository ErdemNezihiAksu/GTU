#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define OBSTACLE 'o'
#define BAIT 'b'
#define EMPTY 'e'

typedef struct
{
    int row;
    int col;
}point;

typedef struct
{
    char type;
    int value;
}block;

block*** init_board()
{
    int bait, obstacle, height, row, col;
    block ***board = (block***)malloc(10 * sizeof(block**));
    for(int i = 0; i < 10; i++)
    {
        board[i] = (block**)malloc(10 * sizeof(block*));
        for(int j = 0; j < 10; j++)
        {
            board[i][j] = (block*)malloc(sizeof(block));
            board[i][j][0].type = EMPTY;
            board[i][j][0].value = 0;
        }
    }
    bait = (rand() % 99) + 1;
    row = bait / 10;
    col = bait % 10;
    board[row][col][0].type = BAIT;
    label:

    obstacle = rand() % 99 + 1;
    if(obstacle == bait)
        goto label;
    row = obstacle / 10;
    col = obstacle % 10;
    board[row][col][0].type = OBSTACLE;
    height = rand() % 9 + 1;
    board[row][col][0].value = height;
    block *p = realloc(board[row][col],height * sizeof(block));
    if(p != NULL)
        board[row][col] = p;

    return board;
}

void draw_board(block*** board, point* snake, int snake_length)
{
    for(int i = -1; i<11 ; i++)
    {
        for(int j = -1; j<11; j++)
        {
            if(i == -1 || i == 10)
                printf("-");
            else
            {
                if(j == -1 || j == 10)
                    printf("|");
                else
                {
                    int flag = 0;
                    for(int k = 0; k < snake_length; k++)
                    {
                        if(snake[k].row == i && snake[k].col == j && k == 0){
                            printf("O");
                            flag = 1;
                            break;
                        }
                        if(snake[k].row == i && snake[k].col == j){
                            printf("X");
                            flag = 1;
                            break;
                        }
                    }
                    if(flag == 1)
                        continue;
                    if(board[i][j][0].type == EMPTY)
                        printf(" ");
                    else if(board[i][j][0].type == BAIT)
                        printf(".");
                    else
                        printf("%d",board[i][j][0].value);
                }
            }
        }
        printf("\n");
    }
}

int check_status(block*** board, point* snake, int snake_length)
{
    for(int i = 3; i < snake_length; i++)
    {
        if(snake[0].row == snake[i].row && snake[0].col == snake[i].col)
            return 1;
    }
    if(snake[0].row < 0 || snake[0].row > 9 || snake[0].col < 0 || snake[0].col > 9)
        return 1;
    if(board[snake[0].row][snake[0].col][0].value > snake_length)
        return 1;
    if(snake_length == 100)
        return 1;
    return 0;
}

point move(point *snake, int snake_length, int *move_count)
{
    char dir;
    int head_row, head_col;
    point prev_head;

    label:
    printf("Enter direction: ");
    scanf("%c",&dir);
    if(dir != 'w' && dir != 'a' && dir != 's' && dir != 'd')
    {
        printf("INVALID DIRECTION!!\n");
        goto label;
    }
    while(getchar() != '\n');

    if(dir == 'w')
    {
        head_col = snake[0].col;
        head_row = snake[0].row - 1;
    }
    else if(dir == 'a')
    {
        head_col = snake[0].col - 1;
        head_row = snake[0].row;
    }
    else if(dir == 's')
    {
        head_col = snake[0].col;
        head_row = snake[0].row + 1;
    }
    else
    {
        head_col = snake[0].col + 1;
        head_row = snake[0].row;
    }
    if(head_col == snake[1].col && head_row == snake[1].row)
    {
        printf("SNAKE CAN NOT GO THROUGH IT'S BODY");
        goto label;
    }
   
    prev_head.row = snake[0].row;
    prev_head.col = snake[0].col;
    snake[0].row = head_row;
    snake[0].col = head_col;
    (*move_count)++;
    return prev_head;
}

void update(block*** board, point** snake, int* snake_length, int move_count, point prev_head)
{
    int tail_row, tail_col, bait, obst[3], height, row, col;

    tail_col = (*snake)[*snake_length-1].col;
    tail_row = (*snake)[*snake_length-1].row;
    for(int i = *snake_length - 1; i > 0; i--)
    {
        if(i == 1)
        {
            (*snake)[1].row = prev_head.row;
            (*snake)[1].col = prev_head.col;
        }
        else
        {
            (*snake)[i].row = (*snake)[i-1].row;
            (*snake)[i].col = (*snake)[i-1].col;
        }
    }
    
    if(board[(*snake)[0].row][(*snake)[0].col][0].type == BAIT)
    {   
        point *new_snake = (point*)malloc((*snake_length + 1)*sizeof(point));
        for(int i = 0; i <*snake_length; i++)
        {
            new_snake[i].row = (*snake)[i].row;
            new_snake[i].col = (*snake)[i].col;
        }
        free(*snake);
        (*snake) = new_snake;
        if(*snake_length == 1)
        {
            (*snake)[*snake_length].row = prev_head.row;
            (*snake)[*snake_length].col = prev_head.col;
        }
        else
        {
            (*snake)[*snake_length].row = tail_row;
            (*snake)[*snake_length].col = tail_col;
        }
        (*snake_length)++;

        label:
        bait = rand() % 99 + 1;
        row = bait / 10;
        col = bait % 10;
        for(int i = 0; i< *snake_length; i++)
        {
            if((row == (*snake)[i].row && col == (*snake)[i].col))
                goto label;
        }
        if(board[row][col][0].type = OBSTACLE)
        {
            board[row][col] = realloc(board[row][col],sizeof(block));
            board[row][col][0].value = 0;
        }
        board[row][col][0].type = BAIT;
        board[(*snake)[0].row][(*snake)[0].col][0].type = EMPTY;
    }
    else if(board[(*snake)[0].row][(*snake)[0].col][0].type == OBSTACLE)
    {
        board[(*snake)[0].row][(*snake)[0].col] = realloc(board[(*snake)[0].row][(*snake)[0].col],sizeof(block));
        board[(*snake)[0].row][(*snake)[0].col][0].value = 0;
        board[(*snake)[0].row][(*snake)[0].col][0].type = EMPTY;
    }


    if(board[(*snake)[0].row][(*snake)[0].col][0].type == BAIT || move_count % 5 == 0)
    {
        for(int i = 0; i < 10; i++)
        {
            for(int j = 0; j < 10; j++)
            {
                if(board[i][j][0].type == OBSTACLE)
                {
                    board[i][j] = realloc(board[i][j], sizeof(block));
                    board[i][j][0].type = EMPTY;
                    board[i][j][0].value = 0;
                }
            }
        }
        
        int  count = rand() % 3 + 1;
        for(int i = 0; i < count; i++)
        {
            label1:
            obst[i] = rand() % 99 + 1;
            row = obst[i] / 10;
            col = obst[i] % 10;
            if(board[row][col][0].type == BAIT)
                goto label1;
            for(int i = 0; i< *snake_length; i++)
            {
                if((row == (*snake)[i].row && col == (*snake)[i].col))
                    goto label1;
            }
            height = rand() % 9 + 1;
            if(board[row][col][0].type == OBSTACLE)
            {
                if(board[row][col][0].value + height > 9){
                    board[row][col] = realloc(board[row][col], 9 * sizeof(block));
                    board[row][col][0].value = 9;
                }
                else{
                    board[row][col] = realloc(board[row][col], (board[row][col][0].value + height) * sizeof(block));
                    board[row][col][0].value += height;
                } 
            }
            else
            {
                if(height != 1)
                    board[row][col] = realloc(board[row][col], height * sizeof(block));
                board[row][col][0].value = height;
                board[row][col][0].type = OBSTACLE;
            }
        }
    }
}

void play(block*** board)
{
    point prev_head;
    point *snake = (point*)malloc(sizeof(point));
    int snake_length = 1, move_count = 0;
    snake[0].row = 0;
    snake[0].col = 0;
    while(1)
    {
        draw_board(board,snake,snake_length);
        prev_head = move(snake, snake_length, &move_count);
        if(check_status(board, snake, snake_length) == 1)
            break;
        update(board,&snake,&snake_length,move_count, prev_head);
    }
    printf("\nTHE GAME IS OVER, THANK YOU FOR PLAYING\n");
}

int main()
{   
    block*** board;

    srand(time(NULL));
    board = init_board();
    play(board);
}