#include <stdio.h>
#include <stdlib.h>

int* part1(int n)
{
    int *arr = (int*)malloc(sizeof(int)* n);

    printf("Enter %d integers: ",n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    return arr;
}

int main()
{
    int n;
    int *arr, *arr2;

    printf("Enter the size of the array: ");
    scanf("%d", &n);
    arr = part1(n);
    arr2 = (int*)calloc(n,sizeof(int));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            arr2[i] += arr[j];
        }
    }
    printf("Firs array: ");
    for(int i = 0; i < n; i++)
        printf("%d ",arr[i]);
    printf("\nSecond array(cumilative sum): ");
     for(int i = 0; i < n; i++)
        printf("%d ",arr2[i]);
    free(arr);
    free(arr2);
}