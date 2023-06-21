#include <stdio.h>

int part1(int arr[])
{
    int n,i=0;
    while(1)
    {
        scanf("%d", &n);
        if(n == -100)
        break;
        arr[i] = n;
        i++;
    }
return i;
}

void label(char arr2[], int arr[],int j)
{
    int i = 0;
    while(i < j)
    {
        if(arr[i] % 2 == 0)
        arr2[i] = 'e';
        else
        arr2[i] = 'o';
        i++;
    }
    
}

void print(char arr2[], int arr[], int j)
{
    int i = 0;
    while(i < j)
    {
        printf("%d %c\n",arr[i],arr2[i]);
        i++;
    }
}

int main()
{
    int arr[10];
    char arr2[10];
    int i  = part1(arr);
    label(arr2,arr,i);
    print(arr2,arr,i);

}