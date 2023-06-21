#include <stdio.h>
#include <stdlib.h>

void write_file()
{   
    char shape = '0';
    int size;
    FILE *f;
    f = fopen("shape.txt","w");
    fclose(f);

    while(shape != 'e')
    {
        f = fopen("shape.txt","a");
        label1:
        printf("Enter your shape(s or t): ");
        scanf(" %c", &shape);
        if(shape == 'e')
        {
            fclose(f);
            break;
        }
        if(shape != 's' && shape != 't')
        {
            printf("Invalid shape!!\n");
            goto label1;
        }
        label2:
        printf("Enter the size between 3 and 10: ");
        scanf("%d", &size);
        if(size < 3 || size > 10)
        {
            printf("Invalid size!!\n");
            goto label2;
        }
        fprintf(f,"%c,%d\n",shape,size);
        fclose(f);
    }
}

void draw_square(int size)
{
    for(int i = 0; i< size; i++)
    {
        for(int j = 0; j< size; j++)
        {
            if(i == 0 || i == size-1)
            {
                printf("*");
            }
            else
            {
                if(j == 0 || j == size-1)
                printf("*");
                else
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void draw_triangle(int size)
{
    int count = 1;
    for(int i = 0; i<size; i++)
    {
        for(int k = 0; k<size-i; k++)
        printf(" ");
        for(int j=0; j<count; j++)
        {
            if(j == 0 || j == count-1 || i == size-1)
            printf("*");
            else
            printf(" ");
        }
        printf("\n");
        count += 2;
    }
    printf("\n");
}

int main()
{
    char selection,shape;
    int size,flag= 0;
    FILE *f;

    do
    {
        printf("Welcome to Shape Reader! Please make your choice to continue \n");
        printf("1-) Generate a shape file\n2-) Read and draw a shape file\n3-) Terminate the program\n");
    
        scanf(" %c", &selection);
        if(selection == '1')
        {
            write_file();
            flag = 1;
        }
        else if(selection == '2')
        {
            if(flag == 1)
            {
                f = fopen("shape.txt","r");
                while(feof(f) == 0)
                {
                    fscanf(f,"%c,%d\n",&shape,&size);
                    if(shape == 's')
                    draw_square(size);
                    else
                    draw_triangle(size);
                }
            }
        }

    } 
    while (selection != '3');
}