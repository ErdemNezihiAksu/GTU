#include <stdio.h>
#include "util.h"

void fraction_print(int numerator, int denominator) {
    printf("%d//%d", numerator, denominator);
}  /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 + n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1*d2 - n2*d1;
    *d3 = d1*d2;
    fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * n2;
    *d3 = d1 * d2;
    fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    *n3 = n1 * d2;
    *d3 = d1 * n2;
    fraction_simplify(n3, d3);
} /* end fraction_div */

/* Simplify the given fraction such that they are divided by their GCD */
void fraction_simplify(int * n, int * d) {
    int GCD = 1;
    int i = 2;
    int a = *n;
    int b = *d;
    if(a != 0)
    {
        if(a < 0)
        a *= -1;
        while(a != 1 || b != 1)
        {
            if(a % i == 0 && b % i == 0)
            GCD *= i;
            if(a % i == 0)
            a /= i;
            if(b % i == 0)
            b /= i;
            else if(a % i != 0 && b % i != 0)
            i++;
        }
    *n /= GCD;
    *d /= GCD;
    }
}
