#include <stdio.h>
#include "scilib.h"

int main(void)
{
    struct buffer *p;

    p = malloc(sizeof(struct buffer) * MAX_TOKEN_LEN);

    printf("Enter expresions: ");
    p = getexpr(stdin);
    
    return 0;
}