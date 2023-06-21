#include <stdio.h>


void Part1_menu()
{
    char c;
    printf("Tempature Conversion Menu\n");
    printf("1. Convert Celcius to Fahrenheit\n2. Convert Fahrenheit to Celcius\n3. Quit\nEnter your choice (1-3): ");
}

float convert(char c, float value)
{
    float converted;
    if(c == '1')
    {
        converted = value * 9 / 5 + 32;
    }
    else
    converted = 5*(value - 32) / 9;
    return converted;     
}
void user_ınput()
{
    char c;
    float value,converted;
    while(1)
    {
        label:
        Part1_menu();
        scanf(" %c",&c);
        if(c != '1' && c != '2' && c != '3')
        {
            printf("Please enter a valid value !!\n");
            goto label;
        }
        if(c == '3')
        break;
        else if(c == '1')
        {
            printf("Enter the tempature value to convert: ");
            scanf("%f",&value);
            converted = convert('1', value);
            printf("%.2f Celcius = %.2f Fahrenheit\n",value,converted);
        }
        else
        {
            printf("Enter the tempature value to convert: ");
            scanf("%f",&value);
            converted = convert('2', value);
            printf("%.2f Fahrenhiet = %.2f Celcius\n",value,converted);
        }
        
    }
}

int main()
{
    user_ınput();
}