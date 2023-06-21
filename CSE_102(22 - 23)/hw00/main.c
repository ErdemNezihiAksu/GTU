#include <stdio.h>
#include "util.h"


int main() {

    /* A fractional number: 13/7 */
    int num1 = 13, den1 = 7;
    /* A second fractional number: 13/11 */
    int num2 = 30, den2 = 11;
    /* An unitilized fractional number */
    int num3, den3;

    printf("First number: ");
    fraction_print(num1, den1);
    printf("\n");

    printf("Second number: ");
    fraction_print(num2, den2);
    printf("\n");

    printf("Addition: ");
    fraction_add(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Subtraction: ");
    fraction_sub(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Multiplication: ");
    fraction_mul(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(num1, den1, num2, den2, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    int n4,n5,d4,d5;

    printf("\nEnter the numerator of your first fractional number: ");
    scanf("%d",&n4);
    printf("Enter the denominator of your first fractional number: ");
    scanf("%d",&d4);
    printf("\nEnter the numerator of your second fractional number: ");
    scanf("%d",&n5);
    printf("Enter the denominator of your second fractional number: ");
    scanf("%d",&d5);

    printf("\nMultiplication: ");
    fraction_mul(n4, d4, n5, d5, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");

    printf("Division: ");
    fraction_div(n4, d4, n5, d5, &num3, &den3);
    fraction_print(num3, den3);
    printf("\n");
    return(0);
}
