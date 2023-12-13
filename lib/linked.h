//create a header file which contains the structure of the linked list and the function prototypes

#ifndef LINKED_H
#define LINKED_H

//defining a node structure
extern struct Node
{
    char data[100];
    struct Node *next;
}Node;


struct Node* createNode(char data[100]);
int getLength(struct Node *head);

#endif
