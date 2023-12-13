#include "stack.h"
#include "linked.h"
#include <string.h>
#include <stdlib.h>

//defining a function to pop a node from the stack
struct studentStack* pop(struct studentStack *studentStack, struct Node *popValue)
{
    *popValue = *studentStack->top;
    int new_size = studentStack->size - 1;
    studentStack = studentStack->next;
    studentStack->size = new_size;
    return studentStack;
}

//defining a function to push a node to the stack
struct studentStack* push(struct studentStack *studentStack, struct Node *newNode)
{
    struct studentStack *temp = malloc(sizeof(struct studentStack));
    temp->top = newNode;
    temp->next = studentStack;
    temp->size = studentStack->size + 1;
    return temp;
}