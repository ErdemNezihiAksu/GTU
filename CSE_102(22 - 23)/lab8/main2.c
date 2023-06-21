#include <stdio.h>
#include <math.h>

typedef struct n
{
    double vector[3];
}vector;

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec)
{
    double scalar_product = vec_1.vector[0]*vec_2.vector[0] + vec_1.vector[1]*vec_2.vector[1] + vec_1.vector[2]*vec_2.vector[2];
    double length_1 = sqrt(pow(vec_1.vector[0],2) + pow(vec_1.vector[1],2) + pow(vec_1.vector[2],2));
    double length_2 = sqrt(pow(vec_2.vector[0],2) + pow(vec_2.vector[1],2) + pow(vec_2.vector[2],2));

    double radians = acos(scalar_product/(length_1*length_2));
    double degree = radians * (180/M_PI);

    output_vec->vector[0] = vec_1.vector[1]*vec_2.vector[2] - vec_1.vector[2]*vec_2.vector[1];
    output_vec->vector[1] = -1*(vec_1.vector[0]*vec_2.vector[2] - vec_1.vector[2]*vec_2.vector[0]);
    output_vec->vector[2] = vec_1.vector[0]*vec_2.vector[1] - vec_1.vector[1]*vec_2.vector[0];

    return degree; 
}

int main()
{
    vector vec_1, vec_2, output_vec;
    double degree;

    vec_1.vector[0] = 1;
    vec_1.vector[1] = 2;
    vec_1.vector[2] = 3;
    vec_2.vector[0] = 3;
    vec_2.vector[1] = 2;
    vec_2.vector[2] = 1;

    degree = find_orthogonal(vec_1,vec_2,&output_vec);
    printf("degree : %lf\n",degree);
    for(int i = 0; i<3; i++)
    {
        printf("%lf\n",output_vec.vector[i]);
    }
}