#include <stdio.h>
#include <math.h>

#define pi 3.14

void part1()
{
    int length, width, height, radius;
    double area, volume;

    printf("Enter the edge length for cube: ");
    scanf("%d", &length);
    area = 6*length*length;
    volume = length*length*length;
    printf("Surface area: %.2lf, Volume: %.2lf\n", area, volume);
    printf("Enter the side length for rectengular prism: ");
    scanf("%d", &length);
    printf("Enter side width: ");
    scanf("%d", &width);
    printf("Enter side height: ");
    scanf("%d", &height);
    area = 2*(length*width + length*height + width*height);
    volume = length*width*height;
    printf("Surface area: %.2lf, Volume: %.2lf\n", area, volume);
    printf("Enter rhe radius for sphere: ");
    scanf("%d", &radius);
    area = 4*pi*radius*radius;
    volume = (4*pi*radius*radius*radius)/3;
    printf("Surface area: %.2lf, Volume: %.2lf\n", area, volume);
    printf("Enter radius for cone: ");
    scanf("%d", &radius);
    printf("Enter height: ");
    scanf("%d", &height);
    area = pi*radius*(sqrt(radius*radius + height*height) + radius);
    volume = (pi*radius*radius*height)/3;
    printf("Surface area: %.2lf, Volume: %.2lf\n", area, volume);
}

void part2()
{
    float weight,height,BMI;
    printf("Enter your weight(kg): ");
    scanf(" %f",&weight);
    printf("Enter your height(m): ");
    scanf(" %f",&height);
    BMI = weight / (height*height);
    
    printf("BMI: %.1lf ",BMI);
    if(BMI < 18.5)
    printf("underweight.\n");
    else if(BMI >= 18.5 && BMI < 25 )
    printf("avarage weight.\n");
    else if(BMI >= 25 && BMI <= 30)
    printf("overweight.\n");
    else
    printf("obese.\n");
}

int main()
{
    printf("---Geometry--\n");
    part1();
    printf("---BMI---\n");
    part2();
}  