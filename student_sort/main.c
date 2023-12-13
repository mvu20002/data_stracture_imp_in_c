//include standart libs
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//incude special libs from lib folder
#include "stack.h"
#include "linked.h"


//defining a function to read nth line of the file.
struct Node* readTxtFile(struct Node *head, int n)
{
    FILE *fp;
    char str[100];
    fp = fopen("input.txt","r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    for(int i=0;i<n;i++)
    {
        fgets(str,100,fp);
    }
    //splid the string into tokens and insert into the linked list
    //first token is the id of the student
    //second token is the name of the student
    //third token is the year of the student
    char *token = strtok(str,";");
    struct Node *temp = head;
    while(token != NULL)
    {
        temp->next = createNode(token);
        temp = temp->next;
        token = strtok(NULL,";");
    }
    fclose(fp);
    return head;
}

//defining a function to get number of lines in the file
int getNumberOfLines()
{
    FILE *fp;
    char str[100];
    int count = 0;
    fp = fopen("input.txt","r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    while(fgets(str,100,fp) != NULL)
    {
        count++;
    }
    fclose(fp);
    return count;
}

//get id of the student as integer
int getId(struct Node *head)
{
    struct Node *temp = head->next;
    return atoi(temp->data);
}

//get faculty code of the student from the id
int getFacultyCode(int id)
{
    return (id / 1000000) % 1000;
}

//get name of the student as string
char* getName(struct Node *head)
{
    struct Node *temp = head->next;;
    temp = temp->next;
    return temp->data;
}

//get year of the student as integer
int getYear(struct Node *head)
{
    //temp
    struct Node *temp = head->next;
    temp = temp->next;
    temp = temp->next;
    return atoi(temp->data);
}

//defining a function to compare two records by year
int compareByYear(struct Node *record1, struct Node *record2)
{
    int year1 = getYear(record1);
    int year2 = getYear(record2);
    if(year1 <= year2)
    {
        return 1;
    }
    else if(year1 > year2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

//defining a function to compare two records by year
int compareByFacultyCode(struct Node *record1, struct Node *record2)
{
    int facultyCode1 = getFacultyCode(getId(record1));
    int facultyCode2 = getFacultyCode(getId(record2));
    if(facultyCode1 <= facultyCode2)
    {
        return 1;
    }
    else if(facultyCode1 > facultyCode2)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

struct studentStack* sortByYear(struct studentStack *studentStack)
{
    struct studentStack *co_stack = malloc(sizeof(struct studentStack));
    co_stack->top = NULL;
    co_stack->next = NULL;
    co_stack->size = 0;
    while(studentStack->size != 0)
    {
        struct Node *temp = malloc(sizeof(struct Node));
        studentStack = pop(studentStack,temp);

        while(co_stack->size != 0 && compareByYear(temp,co_stack->top) == -1)
        {

            struct Node *temp1 = malloc(sizeof(struct Node));
            co_stack = pop(co_stack,temp1);
            studentStack = push(studentStack,temp1);

        }

        co_stack = push(co_stack,temp);
    }
    return co_stack;
}


struct studentStack* sortByFacultyCode(struct studentStack *studentStack)
{
    struct studentStack *co_stack = malloc(sizeof(struct studentStack));
    co_stack->top = NULL;
    co_stack->next = NULL;
    co_stack->size = 0;
    while(studentStack->size != 0)
    {
        struct Node *temp = malloc(sizeof(struct Node));
        studentStack = pop(studentStack,temp);

        while(co_stack->size != 0 && compareByFacultyCode(temp,co_stack->top) == -1)
        {

            struct Node *temp1 = malloc(sizeof(struct Node));
            co_stack = pop(co_stack,temp1);
            studentStack = push(studentStack,temp1);

        }

        co_stack = push(co_stack,temp);
    }
    return co_stack;
}

int main()
{
    int numberOfStudents = getNumberOfLines(); //get number of lines in the file

    struct studentStack *studentStack;
    studentStack = malloc(sizeof(struct studentStack));
    studentStack->top = NULL;
    studentStack->next = NULL;
    studentStack->size = 0;

    struct studentStack *studentStack1;
    studentStack1 = malloc(sizeof(struct studentStack));
    studentStack1->top = NULL;
    studentStack1->next = NULL;
    studentStack1->size = 0;


    //read the file and store the records in the stack of students
    //each node of the linked list contains a field of the record of the student
    for(int i=0;i<numberOfStudents;i++)
    {   
        struct Node *record;
        record = malloc(sizeof(struct Node));
        record = readTxtFile(record,i+1);
        studentStack = push(studentStack,record);
        studentStack1 = push(studentStack1,record);
    }
    

    //open the output file
    FILE *fp;
    fp = fopen("output.txt","w");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }


    studentStack = sortByYear(studentStack); //this stack is sorted now by year

    //print the sorted records to the output file
    while(studentStack->size != 0)
    {
        struct Node *current_student = malloc(sizeof(struct Node));
        studentStack = pop(studentStack,current_student);
        fprintf(fp,"%s;%d\n",getName(current_student),getYear(current_student));
    }


    studentStack1 = sortByFacultyCode(studentStack1); //this stack is sorted now by faculty code
    while(studentStack1->size != 0)
    {
        struct Node *current_student = malloc(sizeof(struct Node));
        studentStack1 = pop(studentStack1,current_student);
        fprintf(fp,"%09d\n",getId(current_student));
    }  

    fclose(fp); //close the output file
    return 0;
}