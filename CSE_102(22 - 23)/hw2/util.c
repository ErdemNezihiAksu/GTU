#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void part1()
{
    int year;

    printf("----Leap year problem----\n");
    printf("Please enter a year: ");
    scanf("%d", &year);

    if((year - 2000) % 4 == 0)
    printf("%d is a leap year.\n", year);
    else
    printf("%d is not a leap year.\n", year);
}

float factorial(int n)
{
    if(n == 1)
    return 1;
    return n*factorial(n-1);
}

int digit_count(float n)
{
    int digit = 1, temp = n;		//bu fonksiyonu part 2 de scientfic notation da kullanmak için, result ın kaç rakamdan olduğunu bulmak için kullandım.
    while(temp >= 10)
    {
        temp /= 10;
        digit++;
    }
    return digit;
}
void scientific_notation_print(int m, int n, float result)	//bu fonskiyon result ı scientific notation haline çevirip ekrana bastırır.
{
    int pos_or_negativ = 1;
    if(result < 0)                      //result eğer negatif ise işlem kolaylığı açısından positive çeviririz ve flag'i -1 yaparız.
    {
        result *= -1;
        pos_or_negativ = -1;
    }
    int digit = digit_count(result);    //result ın kaç basamaklı olduğunu öğreniriz.
    float temp = result;		//result değeriyle oynayacağımız için, değeri kaybetmemek adına bir değişkene atıyoruz.
    float e;				//notation ın sonunda e harfinden sonra gelicek sayı için bu değişkeni oluşturdum.
    char *str_result= (char*)malloc(sizeof(char)*(m+30));	//scientific notation ı string olarak bastıracağım için bir dizi oluşturdum.

    if(m >= digit)
    {
        if(result > 0 && result < 1) // eger result 0 ile bir arasındaysa, basamak değerini doğru yazdırmak amacıyla result 1 e eşit veya büyük olana kadar 10 ile çarpıp bir basamak sağa kaydırıyoruz..
        {
            while(result < 1)
            result *= 10;
        }
        result *= pow(10,m-digit);	//eğer m değeri result ın basamak değerinden daha fazlaysa, resultun sonuna eşitlenene kadar 0 koyuyoruz.
    }
    else
    {
        printf("Error, 'm' value can not be smaller than digit count of the result.");
        return;
    }
    result /= pow(10,n);		//result ın basamak değeri 'm' değerine eşitlendikten sonra result ı 10 üstü 'n' e bölüyoruz ki notation için nokta doğru yere gelsin.
    if(result == 0)
    {
        e = 0;
    }
    else{
         e = log10(temp/result);		//noktayı doğru yere koyduktan sonra result ın son halini 10 üzeri kaç ile çarparsak asıl result ı elde ederizi bulmak için log işlemi uyguluyoruz.
    }
    sprintf(str_result,"%f",result);	//result ı string e çeviriyoruz.
    if(n > 6)
    {
        int i,j=0;
        while(str_result[j])
        j++;
        for(i = 0; i< n-6; i++)
        {
            str_result[j+i]='0';
        }
        str_result[j+i]='\0';
    }
    else{
        str_result[m+1] = '\0';		//result ın noktadan sonra istenilen sayıda basamakta bırakmak için belirtilen indeksine(yani noktadan sonra n tane basamak) EOF koyuyoruz.
    }

    printf("Result: ");
    if(pos_or_negativ == -1)
    {
        printf("-");
    }
    printf("%se%.0f\n",str_result,e);//resultı, e harfini ve e den sonra gelen sayıyı bir bütün olarak yazdırıyoruz.
    free(str_result);
}
void part2()
{
    char format,operation;
    int m,n;
    float operand1,operand2,result;
    
    printf("----Enhanced Calculator----\n");
    printf("Enter the format of output (S or I): ");
    scanf(" %c",&format);
    if(format != 'S' && format != 'I')
    {
        printf("Invalid format...\n");
        return ;
    }
    if(format == 'S')
    {
        label:
        printf("Enter m and n values: ");
        scanf("%d %d", &m,&n);
        if(n >= m)
        {
            printf("n can not be equal or bigger than m !!\n");
            goto label;
        }
    }
    printf("Enter the operation(+,-,/,*,%%,!,^): ");
    scanf(" %c", &operation);

    switch (operation)
    {
    case '+':
        printf("Enter the first operand: ");
        scanf("%f", &operand1);
        printf("Enter the second operand: ");
        scanf("%f", &operand2);
        result = operand1 + operand2;
        break;
    case '-':
        printf("Enter the first operand: ");
        scanf("%f", &operand1);
        printf("Enter the second operand: ");
        scanf("%f", &operand2);
        result = operand1 - operand2;
        break;
    case '/':
        printf("Enter the first operand: ");
        scanf("%f", &operand1);
        printf("Enter the second operand: ");
        scanf("%f", &operand2);
        result = operand1 / operand2;
        break;
    case '*':
        printf("Enter the first operand: ");
        scanf("%f", &operand1);
        printf("Enter the second operand: ");
        scanf("%f", &operand2);
        result = operand1 * operand2;
        break;
    case '%':
        printf("Enter the first operand: ");
        scanf("%f", &operand1);
        printf("Enter the second operand: ");
        scanf("%f", &operand2);
        result = (int)operand1 % (int)operand2;
        break;
    case '!':
        printf("Enter the operand: ");
        scanf("%f",&operand1);
        result = factorial((int)operand1);
        break;
    case '^':
        printf("Enter the base: ");
        scanf("%f",&operand1);
        printf("Enter tha power: ");
        scanf("%f",&operand2);
        result = pow(operand1,operand2);
        break;
    default:
        printf("Invalid operation !\n");
        break;
    }
    if(format == 'S')
        {
            scientific_notation_print(m,n,result);
        }
        else
        printf("Result: %f\n",result);
}

void part3()
{
    int exam1,exam2,exam3,ass1,ass2;
    float final_grade;

    printf("----Grade Calculator----\n");
    printf("Enter 3 exam grades of the student: ");
    scanf("%d %d %d", &exam1,&exam2,&exam3);
    printf("Enter 2 assignment grades of the student: ");
    scanf("%d %d", &ass1,&ass2);

    final_grade = (exam1 + exam2 + exam3)/3 * 0.6 + (ass1 + ass2)/2 * 0.4;

    if(final_grade < 60)
    printf("Final grade: %.1f failed\n", final_grade);
    else
    printf("Final grade: %.1f passed\n", final_grade);
}
