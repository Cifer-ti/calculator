/* Stack management routines */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../SciLib/scilib.h"
#include "stack.h"

struct stack {
    Buffer content[__MAX_TOKEN_LEN__];
    int top;
};

int stackinit(Stack s)
{
    s = malloc(sizeof(struct stack));

    if(s == NULL) {
        fprintf(stderr, "Error: Stack could not be allcoated\n");
        return -1;
    }
    
    s->top = 0;
    return 0;
}

void stakcpush(Stack s, Buffer token)
{
    /* add check for stack overflow later*/
    s->content[s->top++] = token;
}

Buffer stackpop(Stack s)
{   
    /* add check for stack underflow later */
    return s->content[s->top--];
}

Buffer stacktop(Stack s)
{
    return s->content[s->top];
}

bool isstackfull(Stack s)
{
    if(s->top >= __MAX_TOKEN_LEN__)
        return true;

    return false;
}
bool isStackempty(Stack s)
{
    if(s->top < 0)
        return true;
        
    return false;
}