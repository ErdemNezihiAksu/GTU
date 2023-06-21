#include <stdio.h>
#include <stdlib.h>

int* part1(int n)
{
    int *arr = (int*)malloc(sizeof(int)* n);

    printf("Enter the elements of the array: ");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    return arr;
}

int main()
{
    int n, min;
    int *arr;

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    arr = part1(n);
    min = arr[0];
    for(int i = 1; i < n; i++)
    {
        if(arr[i] < min)
            min  = arr[i];
    }
    printf("Min of the array elements: %d\n", min);
    free(arr);
}