#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
     struct Student
    {
    char name[30];
    };
    char temp[30];
    struct Student students[50];
    /*printf("Enter the name of the students, when you are done press CTRL_D\n");*/
    int x=0;
    while(scanf("%s",students[x].name) != EOF)
    {
        x++;
    }
    for(int i=0; i<x-1; i++)
    {
        for(int j=i+1;j<x;j++)
        {
            if(strcmp(students[i].name,students[j].name)>0)
            {
                strcpy(temp,students[i].name);
                strcpy(students[i].name,students[j].name);
                strcpy(students[j].name,temp);
            }
        }
    }
    for(int d=0; d<x; d++)
    {
        printf("%s\n",students[d].name);
    }

    return 0;
}
