//create a header file which contains the structure of the stack and the function prototypes

#ifndef STACK_H
#define STACK_H

//defining student stack
extern struct studentStack
{
    struct Node *top;
    struct studentStack *next;
    int size;
}studentStack;

struct studentStack* pop(struct studentStack *studentStack, struct Node *popValue);
struct studentStack* push(struct studentStack *studentStack, struct Node *newNode);

#endif