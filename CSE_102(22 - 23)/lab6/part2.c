#include <stdio.h>

int main()
{
    int row, how_many_team= 0;
    int age[10];
    char team[10], selected_team;
    char job[10];
    float salary[100];
    float total_salary = 0, av_salary;

    FILE *f = fopen("a.txt","r");
    if(f == NULL)
    {
        printf("Error opening  file!!");
        return 1;
    }

    fscanf(f,"%d",&row);

    for(int i = 0; i < row; i++)
    fscanf(f, "%d %c %f %c", &age[i], &job[i], &salary[i], &team[i]);

    printf("Please select a team: ");
    scanf(" %c", &selected_team);

    for (int i = 0; i < row; i++)
    {
        if(team[i] == selected_team)
        {
            how_many_team++;
            total_salary += salary[i];
        }
    }
    
    if(how_many_team != 0)
    {
        av_salary = total_salary / how_many_team;
        printf("The average salary of fans of team %c is %.2f\n", selected_team, av_salary);
    }
    else
    printf("There are no fans of team %c in the database!\n", selected_team);
}