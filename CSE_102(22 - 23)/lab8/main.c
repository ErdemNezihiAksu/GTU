#include <stdio.h>
#include <stdlib.h>

typedef struct n
{
    double matriks[3][3];
    double determinant;
} matrix;

void print_matrix(matrix initial_matrix)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("%.4lf ", initial_matrix.matriks[i][j]);
        }
        printf("\n");
    }
}

void determinant_of_matrix(matrix *initial_matrix)
{
    double a = initial_matrix->matriks[0][0], b = initial_matrix->matriks[0][1], c = initial_matrix->matriks[0][2];
    double a_calculate = a * (initial_matrix->matriks[1][1] * initial_matrix->matriks[2][2] - initial_matrix->matriks[1][2] * initial_matrix->matriks[2][1]);
    double b_calculate = b * (initial_matrix->matriks[1][0] * initial_matrix->matriks[2][2] - initial_matrix->matriks[1][2] * initial_matrix->matriks[2][0]);
    double c_calulate = c * (initial_matrix->matriks[1][0] * initial_matrix->matriks[2][1] - initial_matrix->matriks[1][1] * initial_matrix->matriks[2][0]);
    double determinant = a_calculate - b_calculate + c_calulate;
    initial_matrix->determinant = determinant;
}

void inverse_matrix(matrix *initial_matrix, matrix *inverted_matrix)
{
    determinant_of_matrix(initial_matrix);
    if (initial_matrix->determinant == 0)
    {
        printf("NO INVERSE !!\n");
        exit(0);
    }
   
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3 ; j++)
        {
            int a = (i+1) % 3;
            int b = (i+2) % 3;
            int c = (j+1) % 3;
            int d = (j+2) % 3;
            inverted_matrix->matriks[j][i] = (initial_matrix->matriks[a][c]*initial_matrix->matriks[b][d] - initial_matrix->matriks[a][d] * initial_matrix->matriks[b][c]) / initial_matrix->determinant;
        }
    }
}
int main()
{
    matrix inverted_matriks;

    matrix matriks = {
        .matriks={
            {1, 2, 3},
            {2,4,6},
            {3,6,9}
        }
    };
    print_matrix(matriks);
    inverse_matrix(&matriks, &inverted_matriks);
    printf("\n\n");
    print_matrix(inverted_matriks);
}