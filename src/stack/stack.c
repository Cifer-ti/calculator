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

int stackinit(Stack s,int size)
{
    s = malloc(sizeof(struct stack));

    if(s == NULL) {
        fprintf(stderr, "Error: Stack could not be allcoated\n");
        return -1;
    }
    
    s->content = malloc(sizeof(Buffer) * size);

    if(s->content == NULL) {
        fprintf(stderr, "Error: Stack could not be allocated\n");
        free(s);
        return -1;
    }

    s->size = size;
    s->top = 0;
    return 0;
}

void stackpush(Stack s, struct buffer token)
{
    if(isstackfull(s)) {
        fprintf(stderr, "Overflow occured in stack. \ncore dumped\n");
        exit(EXIT_FAILURE);
    }
    s->content[s->top++] = token;
}

struct buffer stackpop(Stack s)
{   
    if(isStackempty(s)) {
        fprintf(stderr, "Underflow occured in stack. \ncore dumped\n");
        exit(EXIT_FAILURE);
    }
    return s->content[s->top--];
}

Buffer stacktop(Stack s)
{
    return s->content[s->top];
}

bool isstackfull(Stack s)
{
   return s->top >= s->size
}
bool isStackempty(Stack s)
{
    return s->top < 0;
}