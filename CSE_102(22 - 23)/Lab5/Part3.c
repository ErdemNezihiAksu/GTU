#include <stdio.h>

void put_nbr_base(int n, char *base)
{
    int nb,len= 0;
    
    if(n < 0)
    {
        printf("-");
        n *= -1;
    }
    while(base[len])
    len++;
    if(n < len)
    printf("%c",base[n]);
    else
    {
        put_nbr_base(n/len,base);
        put_nbr_base(n%len,base);
    }
}
int main()
{
    char c;
    int n;
while(1){
    while(1)
    {
        printf("\nMenu:\n");
        printf("1. Convert a number to decimal,binary,octadecimal,hexadecimal\n2. Quit\n");
        scanf(" %c",&c);
        if(c !='1' && c != '2')
        printf("Please enter a valid input!!\n");
        else
        break;
    }
    if(c == '2')
    break;
    else
    {
        printf("Enter your number: ");
        scanf("%d",&n);
        printf("Decimal: %d",n);
        printf("\nBinary: ");
        put_nbr_base(n,"01");
        printf("\nOctadecimal: ");
        put_nbr_base(n,"01234567");
        printf("\nHexadecimal: ");
        put_nbr_base(n,"0123456789ABCDEF");
    }
}
}