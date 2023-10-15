/* Stack management routines */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../SciLib/scilib.h"
#include "stack.h"

struct stack {
    Buffer content;
    int top;
    int size;
};

Stack stackinit(int size)
{
    Stack s;

    s = malloc(sizeof(struct stack));

    if(s == NULL) {
        fprintf(stderr, "Error: Stack could not be allcoated\n");
        exit(EXIT_FAILURE);
    }
    
    s->content = malloc(sizeof(Buffer) * size);

    if(s->content == NULL) {
        fprintf(stderr, "Error: Stack could not be allocated\n");
        free(s);
        exit(EXIT_FAILURE);
    }

    s->size = size;
    s->top = -1;

    return s;
}

void stackpush(Stack s, struct buffer token)
{
    if(isstackfull(s)) {
        fprintf(stderr, "Error: Stack underflow occured. (core dumped)\n");
        exit(EXIT_FAILURE);
    }
    s->content[++s->top] = token;
}

struct buffer stackpop(Stack s)
{   
    if(isStackempty(s)) {
        fprintf(stderr, "Error: Stack Underflow occured. (core dumped)\n");
        exit(EXIT_FAILURE);
    }
    return (s->content[s->top--]);
}

struct buffer stacktop(Stack s)
{
    return s->content[s->top];
}

bool isstackfull(Stack s)
{
   return s->top >= s->size;
}

bool isStackempty(Stack s)
{
    return (s->top < 0);
}