#include <stdio.h>


int main()
{
    int n,temp;

    while(1)
    {
        int i = 0;
        printf("Please enter a number(3,4 or 5): ");
        scanf("%d",&n);
        temp = n;
        while(temp > 0)
        {
            temp /= 10;
            i++;
        }
        if(i >= 3 && i <=5)
        break;
        printf("Be careful with digit count!!\n");
    }
    while(n > 0)
    {
        printf("%d",n%10);
        n /= 10;
    }
   


}