#include <stdio.h>
#include <math.h>

typedef struct n
{
    double x3;
    double x2;
    double x;
    double d;
} third_order_polynomial;

typedef struct x
{
    double x7, x6, x5, x4, x3, x2, x, d;
    double value;
    char c;
} polynomial;

polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b)
{
    polynomial p3, intg;
    double value_a, value_b, value;

    p3.x6 = p1.x3 * p2.x3;
    p3.x5 = p1.x3 * p2.x2 + p1.x2 * p2.x3;
    p3.x4 = p1.x3 * p2.x + p1.x2 * p2.x2 + p1.x * p2.x3;
    p3.x3 = p1.x3 * p2.d + p1.x2 * p2.x + p1.x * p2.x2 + p1.d * p2.x3;
    p3.x2 = p1.x2 * p2.d + p1.x * p2.x + p1.d * p2.x2;
    p3.x = p1.x * p2.d + p1.d * p2.x;
    p3.d = p1.d * p2.d;

    intg.x7 = p3.x6 / 7;
    intg.x6 = p3.x5 / 6;
    intg.x5 = p3.x4 / 5;
    intg.x4 = p3.x3 / 4;
    intg.x3 = p3.x2 / 3;
    intg.x2 = p3.x / 2;
    intg.x = p3.d;
    intg.c = 'c';

    value_a = intg.x7 * pow(a, 7) + intg.x6 * pow(a, 6) + intg.x5 * pow(a, 5) + intg.x4 * pow(a, 4) + intg.x3 * pow(a, 3) + intg.x2 * pow(a, 2) + intg.x * a;
    value_b = intg.x7 * pow(b, 7) + intg.x6 * pow(b, 6) + intg.x5 * pow(b, 5) + intg.x4 * pow(b, 4) + intg.x3 * pow(b, 3) + intg.x2 * pow(b, 2) + intg.x * b;
    value = value_b - value_a;
    intg.value = value;
    return intg;
}

int main()
{
    third_order_polynomial p1, p2;
    polynomial p3;
    int a, b;

    printf("for p1\n");
    printf("Enter ax3: ");
    scanf("%lf", &p1.x3);
    printf("Enter bx2: ");
    scanf("%lf", &p1.x2);
    printf("Enter cx: ");
    scanf("%lf", &p1.x);
    printf("Enter d: ");
    scanf("%lf", &p1.d);

    printf("for p2\n");
    printf("Enter ax3: ");
    scanf("%lf", &p2.x3);
    printf("Enter bx2: ");
    scanf("%lf", &p2.x2);
    printf("Enter cx: ");
    scanf("%lf", &p2.x);
    printf("Enter d: ");
    scanf("%lf", &p2.d);

    printf("enter first interval value: ");
    scanf("%d",&a);
    printf("enter second interval value: ");
    scanf("%d",&b);

    p3 = get_integral(p1,p2,a,b);
    printf("coefficients of integrated polynomial are : %.3lfX^7 +  %.3lfX^6 +  %.3lfx^5 +  %.3lfx^4 + %.3lfx^3 + %.3lfx^2 + %.3lfx + %c",p3.x7,p3.x6,p3.x5,p3.x4,p3.x3,p3.x2,p3.x,p3.c);
    printf("\nValeus of integral between a-b is: %.3lf\n\n",p3.value);
}