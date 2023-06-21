#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct n
{
    char name[10];
    char color[10];
    float price;
    int serial_num;
    int quantitiy;
} furn;

char Menu()
{
    char c;

    printf("*******************\n");
    printf("Welcome to databaswe of furniture shop");
    printf("\n1. See all furniture\n2. Add a new furniture\n3. Remove furniture\n4. Search furniture\n5. Exit\n\n>");
label:
    scanf(" %c", &c);
    if (c < '1' || c > '5')
    {
        printf("Invalid option!!\n");
        goto label;
    }
    return c;
}

void Show_All(const furn arr[], int j)
{
    for (int i = 0; i < j; i++)
    {
        printf("Name: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity: %d\n\n", arr[i].name, arr[i].color, arr[i].price, arr[i].serial_num, arr[i].quantitiy);
    }
}

void Add(int *j, furn arr[])
{
    FILE *f = fopen("furniture_database.txt", "a+");
    furn new_furn;
    char *buffer = (char *)malloc(sizeof(char) * 100);

    printf("Enter the name of the furniture: ");
    scanf("%9s", new_furn.name);
    printf("Enter the color: ");
    scanf("%9s", new_furn.color);
    printf("Enter The price: ");
    scanf("%f", &new_furn.price);
    printf("Enter serial_number: ");
    scanf("%d", &new_furn.serial_num);
    printf("Enter Quantity: ");
    scanf("%d", &new_furn.quantitiy);

    while (fgets(buffer, 100, f) != NULL)
        ;
    fprintf(f, "\n%s,%s,%.2f,%d,%d", new_furn.name, new_furn.color, new_furn.price, new_furn.serial_num, new_furn.quantitiy);
    fclose(f);
    free(buffer);
    arr[*j] = new_furn;
    *j += 1;
    printf("\nFollowing furniture added to the table\n\n");
    printf("Name: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity: %d\n\n", new_furn.name, new_furn.color, new_furn.price, new_furn.serial_num, new_furn.quantitiy);
}

void Delete(furn arr[], int *j)
{
    FILE *temp = fopen("temp.txt", "w");
    int i = 0, x;

    if (*j == 0)
    {
        printf("No element to delete!!\n");
        return;
    }
label:
    printf("Enter the index of the product you want to remove: ");
    scanf("%d", &x);
    if (x < 0 || x >= *j)
    {
        printf("Invalid Index!!\n");
        goto label;
    }
    printf("\nThe following furniture is removed from the database\n\n");
    printf("Name: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity: %d\n\n", arr[x].name, arr[x].color, arr[x].price, arr[x].serial_num, arr[x].quantitiy);
    for (int a = x; a < *j - 1; a++)
    {
        arr[a] = arr[a + 1];
    }
    *j -= 1;
    fprintf(temp, "Name,Color,Price,Serial_Number,Quantity");
    while (i < *j)
    {
        fprintf(temp, "\n%s,%s,%.2f,%d,%d", arr[i].name, arr[i].color, arr[i].price, arr[i].serial_num, arr[i].quantitiy);
        i++;
    }
    fclose(temp);
    rename("temp.txt", "furniture_database.txt");
}

void Search_Name(const furn arr[], int j, int curr_index, char *name)
{
    if (curr_index == j)
        return;
    else if (strcmp(arr[curr_index].name, name) == 0)
    {
        printf("\nName: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity: %d\n\n", arr[curr_index].name, arr[curr_index].color, arr[curr_index].price, arr[curr_index].serial_num, arr[curr_index].quantitiy);
    }
    Search_Name(arr, j, ++curr_index,name);
}

void Search_Color(const furn arr[], int j, int curr_index, char *color)
{
    if (curr_index == j)
        return;
    else if (strcmp(arr[curr_index].color, color) == 0)
    {
        printf("\nName: %s\nColor: %s\nPrice: %.2f\nSerial Number: %d\nQuantity: %d\n\n", arr[curr_index].name, arr[curr_index].color, arr[curr_index].price, arr[curr_index].serial_num, arr[curr_index].quantitiy);
    }
    Search_Color(arr, j, ++curr_index,color);
}

int main()
{
    char c, search;
    char *token, temp[10], buffer[100];
    int serial_num, quantitiy, j = 0;
    furn furniture[10];
    FILE *f = fopen("furniture_database.txt", "r");

    fgets(buffer, 100, f);
    while (fgets(buffer, 100, f) != NULL)
    {
        token = buffer;
        sscanf(token, "%[^,]", temp);
        strcpy(furniture[j].name, temp);
        while (*token != ',')
            token++;
        token++;
        sscanf(token, "%[^,]", temp);
        strcpy(furniture[j].color, temp);
        while (*token != ',')
            token++;
        token++;
        sscanf(token, "%[^,]", temp);
        furniture[j].price = atof(temp);
        while (*token != ',')
            token++;
        token++;
        sscanf(token, "%[^,]", temp);
        furniture[j].serial_num = atoi(temp);
        while (*token != ',')
            token++;
        token++;
        sscanf(token, "%s", temp);
        furniture[j].quantitiy = atoi(temp);
        j++;
    }
    do
    {
        c = Menu();
        switch (c)
        {
        case '1':
            Show_All(furniture, j);
            break;
        case '2':
            Add(&j, furniture);
            break;
        case '3':
            Delete(furniture, &j);
            break;
        case '4':
        label:
            printf("Select a property to make search\n\n1-Name\n2-Color\n\n>");
            scanf(" %c", &search);
            if (search != '1' && search != '2')
            {
                printf("Invalid option!!\n");
                goto label;
            }
            if (search == '1')
            {
                int i;
                char *name = (char *)malloc(sizeof(char) * 10);
                
                label2:
                i = 0;
                printf("Enter the product name: ");
                scanf("%s", name);
                while (i != j && strcmp(name, furniture[i++].name) != 0);
                if (i == j)
                {
                    printf("Name couldnt be found!!\n");
                    goto label2;
                }
                Search_Name(furniture, j, 0,name);
                free(name);
            }
            else if(search == '2')
            {
                int i;
                char *color = (char*)malloc(sizeof(char) * 10);

                label3:
                i = 0;
                printf("Enter the color of the product: ");
                scanf("%s",color);
                while(i != j && strcmp(color, furniture[i++].color) != 0);
                if (i == j)
                {
                    printf("Color couldnt be found!!\n");
                    goto label3;
                }
                Search_Color(furniture, j, 0, color);
                free(color);
            }
            break;
        default:
            break;
        }
    } while (c != '5');
}