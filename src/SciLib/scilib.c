/* The routines in this library manages the scientific computations for this calculator */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scilib.h"

#define MAX_TOKEN_LEN 512
#define OPERATOR 0
#define ANYTHING_ELSE 1
#define _END '?'    /* Marks the end of buffer array */

/**
 * enumerations of the defferent types
 * 
*/
typedef enum {
    operator,
    operand,
    lbrace,
    function,
    end,
}type;

typedef enum {
    _sin = 130,
    _cos,
    _tan,
    _arcsin,
    _arccos,
    _arctan,
    _sqrt,
    _cbrt,
    _log,
    _exp,
    _abs,
    _roundup,
    _rounddwn,
    _min,
    _max,
    _sum,
    _mean,
    _var,
    _avg,
    _median,
}functios_id;

/**
 * difine a structure that stores the
 * input. the structures has two fields. One 
 * that shows stores the input, and a flag for
 * the type of input.
*/
struct buffer {
    int token;
    int type_flag;
}tokenbuffer[MAX_TOKEN_LEN];

struct buffer *getexpr(FILE *stream)
{
    int type_to_be_read = ANYTHING_ELSE;
    int read, i;

    while(read != EOF && read != '=') {
        if(type_to_be_read == ANYTHING_ELSE) {
            if(scanf("%d ", &read) == 1) {
                tokenbuffer[i].token = read;
                tokenbuffer[i++].type_flag = operand;
                type_to_be_read = OPERATOR;
            }
            
            /* if first thing read isn't a digit */
            else {
                while(isspace(read = getchar()) || read == '\t')
                    ;
                /* check if it's a fuctions */
                if(isalpha(read)) {
                    /* probably a function */
                }

                else {      /* if not then must be a left brace */
                    tokenbuffer[i++].token = read;
                    tokenbuffer[i++].type_flag = lbrace;
                } 
            }
        }

        else if(type_to_be_read == OPERATOR) {
            while(isspace(read = getchar()) || read == '\t')
                ;
            
            tokenbuffer[i].token = read;
            tokenbuffer[i++].type_flag = operator;
            type_to_be_read = ANYTHING_ELSE;
        }
    }

    tokenbuffer[--i].token = _END;
    tokenbuffer[i].type_flag = end;
    return tokenbuffer;
}

