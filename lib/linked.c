#include "linked.h"
#include <string.h>
#include <stdlib.h>

//defining a function to create a new node
struct Node* createNode(char data[100])
{
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data,data);
    newNode->next = NULL;
    return newNode;
}

//defining a function to get length of the linked list
int getLength(struct Node *head)
{
    int count = 0;
    struct Node *temp = head;
    while(temp != NULL)
    {
        count++;
        temp = temp->next;
    }
    return count;
}