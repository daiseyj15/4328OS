#include <stdio.h>
#include <stdlib.h>


int main()
{

    struct Student
    {
    char name[30];
    float gpa;
    };

    struct Student students[50];
    /*printf("Enter the name of the students and their gpa, when you are done press CTRL_D\n");*/
    int x=0;
    int y=0;
    while(scanf("%s%f",students[x].name,&(students[x].gpa)) != EOF)
    {
    x++;
    }
    while(y<=x)
    {
        if(students[y].gpa > 3.0)
        {
            printf("%s\n",students[y].name);
        }
        y++;
    }




    return 0;
}
