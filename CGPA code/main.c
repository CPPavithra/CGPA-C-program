#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

# if defined(_MSC_VER)
# ifndef _CRT_SECURE_NO_DEPRECATE
# define _CRT_SECURE_NO_DEPRECATE (1)
# endif
# pragma warning(disable : 4996)
# endif
#define _CRT_SECURE_NO_WARNINGS 
int n;

struct student
{
    int rollno;
    char name[20];
    float maths;
    float eng;
    float eee;
    float physics;
    float pps;
    float cgpa;
};
struct student s[20];
void ScreenColor()
{
    system("color 6");
    /*  0 = Black
        1 = Blue
        2 = Green
        3 = Aqua
        4 = Red
        5 = Purple
        6 = Yellow
        7 = White
        8 = Gray
        9 = Light Blue
        A = Light Green
        B = Light Aqua
        C = Light Red
        D = Light Purple
        E = Light Yellow
        F = Bright White*/
}

void details(void)
{
    //FUNCTION TO GET STUDENT DETAILS 

    FILE* ptr;
    ptr = fopen("student.dat", "w");

    printf("Enter the number of students\n");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        printf("Enter %d student details-\n", i + 1);
        printf("Roll no: ");
        scanf("%d", &s[i].rollno);
        printf("Name: ");
        scanf("%s", &s[i].name);
        printf("Maths Marks: ");
        scanf("%f", &s[i].maths);
        printf("English Marks: ");
        scanf("%f", &s[i].eng);
        printf("EEE Marks: ");
        scanf("%f", &s[i].eee);
        printf("Physics Marks: ");
        scanf("%f", &s[i].physics);
        printf("PPS Marks: ");
        scanf("%f", &s[i].pps);
        printf("\n");
        printf("\n");

    }
    for (int i = 0; i < n; i++)
    {
        s[i].cgpa = (3 * s[i].maths + 2 * s[i].eng + 4 * s[i].eee + 5 * s[i].physics + 6 * s[i].pps) / 20;
        printf("%f\n", s[i].cgpa);
    }

    //WRITE TO STUDENT.DAT FILE
    for (int i = 0; i < n; i++)
    {
        fprintf(ptr, "%d %s %f %f %f %f %f %f\n", s[i].rollno, s[i].name, s[i].eng, s[i].eee, s[i].maths, s[i].physics, s[i].pps, s[i].cgpa);
    }

}
//FUNCTION TO SEARCH FOR CGPA
void cgpa(void)
{
    int a;
    FILE* ptr;
    ptr = fopen("student.dat", "r");
    int rollno1;
    char name1[20];
    float maths1;
    float eng1;
    float eee1;
    float physics1;
    float pps1;
    float cgpa1;
    printf("\n");
    printf("\n");
    printf("Enter the CGPA above which to search for the student:\n");
    scanf("%d", &a);
    printf("\n");
    printf("The students with the CGPA are:\n");
    printf("\n");
    while (fscanf(ptr, "%d %s %f %f %f %f %f %f", &rollno1, name1, &eng1, &eee1, &maths1, &physics1, &pps1, &cgpa1) != EOF)
    {

        if (cgpa1 >= a)
        {
            printf("%d - %s - %f\n", rollno1, name1, cgpa1);
        }
    }
    fclose(ptr);

}
void gotoxy(int column, int line);
COORD coord = { 0, 0 };

void gotoxy(int x, int y) {
    coord.X = x; coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void studentlist(char filename[])
{
    int a;
    FILE* ptr;
    ptr = fopen(filename, "r");

    int rollno1;
    char name1[20];
    float maths1;
    float eng1;
    float eee1;
    float physics1;
    float pps1;
    float cgpa1;

    gotoxy(27, 25);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 CGPA System \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

    gotoxy(15, 26);
    printf("======================================================================");

    gotoxy(1, 27);
    printf("ROLL NO\t     NAME\t    ENGLISH\t    EEE\t         MATHS\t\t   PHYSICS\t     PPS\t      CGPA\n"); //TABLE TITLES !

    gotoxy(15, 28);
    printf("======================================================================");

    gotoxy(1, 30);
    while (fscanf(ptr, "%d %s %f %f %f %f %f %f", &rollno1, name1, &eng1, &eee1, &maths1, &physics1, &pps1, &cgpa1) != EOF)
    {
        printf("%-10d\t %-12s\t %8f\t %8.2f\t %8f\t %8f\t %8f\t %8f\n", rollno1, name1, eng1, eee1, maths1, physics1, pps1, cgpa1);
    }
}
//FUNCTION TO ARRANGE THE CGPA LIST
void arrange(void)
{
    struct student temp;
    FILE* fp;
    int i = 0, size, j;
    char ch = "";

    fp = fopen("student.dat", "r");
    if (fp == NULL)
    {
        printf("\n Cannot open the file \n");
        exit(0);
    }
    while (ch != EOF)
    {
        fscanf(fp, "%d %s %f %f %f %f %f %f", &s[i].rollno, &s[i].name, &s[i].eng, &s[i].eee, &s[i].maths, &s[i].physics, &s[i].pps, &s[i].cgpa);
        ch = fgetc(fp);
        i++;
    }
    size = i - 1;
    for (i = 1; i < size; ++i)
        for (j = 0; j < size - i; j++)
            if (s[j + 1].cgpa > s[j].cgpa)
            {
                temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }

    fp = fopen("sorted.dat", "w");
    for (i = 0; i < size; i++)
        fprintf(fp, "%d %s %f %f %f %f %f %f\n", s[i].rollno, s[i].name, s[i].eng, s[i].eee, s[i].maths, s[i].physics, s[i].pps, s[i].cgpa);
    printf("\n The file is sorted successfully: \n \n");
    fclose(fp);
    printf("\t\t\t\t\t\tTHE SORTED FILE IS\t\t\t\t\t\t\t\t\t\t\n");
    studentlist("sorted.dat");
}
//FUNCTION TO EXTRACT THE CGPA
void extract(void)
{
    FILE* ptr;
    ptr = fopen("student.dat", "r");
    char sname[10];
    int rollno1;
    char name1[20];
    float maths1;
    float eng1;
    float eee1;
    float physics1;
    float pps1;
    float cgpa1;
    int found = 0;

    printf("\n");
    printf("Enter the name to be searched - ");
    scanf("%s", &sname);
    printf("\n");
    while (fscanf(ptr, "%d %s %f %f %f %f %f %f", &rollno1, name1, &eng1, &eee1, &maths1, &physics1, &pps1, &cgpa1) != EOF)
    {
        if (strcmp(sname, name1) == 0)
        {
            printf("The cgpa of the student %s is %f\n", sname, cgpa1);
            printf("\n");
            printf("The marks are as follows:\n");
            printf("English: %f\n", eng1);
            printf("EEE: %f\n", eee1);
            printf("Maths: %f\n", maths1);
            printf("Physics: %f\n", physics1);
            printf("PPS: %f\n", pps1);
            found = 1;
        }
    }
    if (found == 0) printf("No student found\n");
}
void exit(void)
{
    char exitSurity;
    printf("Program Terminating. Are you sure? (Y/N):");
    scanf("%c", &exitSurity);
    if (exitSurity == 'y' || exitSurity == 'Y')
    {
        return 0;
    }
    else if (exitSurity == 'n' || exitSurity == 'N')
    {
        system("cls");
            main();
    }
    else
    {
        printf("Invalid Entry");
    }
}
void menu(void)
{
    int choice;
    system("cls");
    printf("\n\n\t\t\tCGPA System");
    printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    printf("\n\n\t\t1.Enter Student's Details\n\t\t2.Display all students\n\t\t3.Arrange in Order \n\t\t4.Extract Student CGPA\n\t\t5.Search for CGPA with condition\n\t\t6.Exit\n\n\n\n\n\t\t Enter your choice:");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: details();
        break;
    case 2: studentlist("student.dat");
        break;
    case 3: arrange();
        break;
    case 4: extract();
        break;
    case 5: cgpa();
        break;
    case 6: exit();
        break;
    default:
        printf("Error, enter a different choice");
    }



}



int main()
{
    ScreenColor();
    menu();
}
