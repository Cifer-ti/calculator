/* The routines in this library manages the scientific computations for this calculator */
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scilib.h"

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
    rbrace,
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
    _avrg,
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
};

struct buffer tokenbuffer[__MAX_TOKEN_LEN__];

int getexpr(FILE *stream)
{

    int type_to_be_read = ANYTHING_ELSE;
    int read, i = 0;

    while(read != EOF && read != '=') {
        if(type_to_be_read == ANYTHING_ELSE) {
            if(scanf("%d ", &read) == 1) {
               storeinbuffer(read, operand, &i);
                type_to_be_read = OPERATOR;
            }
            
            /* if first thing read isn't a digit */
            else {
                while(isspace(read = getchar()) || read == '\t')
                    ;
                /* check if it's a fuctions */
                if(isalpha(read)) {
                    if(fsa(&read, &i) != FOUND)
                        return READ_ERR;
                }

                else {      /* if not then must be a left brace */
                    storeinbuffer(read, lbrace, &i);
                } 
            }
        }

        else if(type_to_be_read == OPERATOR) {
            while(isspace(read = getchar()) || read == '\t')
                ;
            if(read == ')')
                storeinbuffer(read, rbrace, &i);
            else {
                storeinbuffer(read, operator, &i);
                type_to_be_read = ANYTHING_ELSE;
            }
        }
    }

    tokenbuffer[--i].token = _END;
    tokenbuffer[i].type_flag = end;
}

void storeinbuffer(int token, int flag, int *index)
{
    tokenbuffer[*index].token = token;
    tokenbuffer[*index].type_flag = flag;
    *index += 1;
}

int fsa(int *ch, int *index)
{
    char *str;
    int i = 0;

    str[i] = *ch;

    while((*ch = getchar()) != '(' && !isspace(*ch))
        str[++i] = *ch;

    if(isspace(*ch))
        return false;
    
    str[++i] = '\0';

    printf("%s\n", str);
    if(strncmp(str, "abs", 3) == 0) {
        storeinbuffer(_abs, function, index);
        return FOUND;
    }
    else if(strncmp(str, "floor", 5) == 0) {
        storeinbuffer(_rounddwn, function, index);
        return FOUND;
    }
    else if(strncmp(str, "ceil", 4) == 0) {
        storeinbuffer(_roundup, function, index);
        return FOUND;
    }
    else if(strncmp(str, "sin", 3) == 0) {
        storeinbuffer(_sin, function, index);
        return FOUND;
    }
    else if(strncmp(str, "cos", 3) == 0) {
        storeinbuffer(_cos, function, index);
        return FOUND;
    }
    else if(strncmp(str, "tan", 3) == 0) {
        storeinbuffer(_tan, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "arcsin", 6) == 0) {
        storeinbuffer(_arcsin, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "arccos", 6) == 0) {
        storeinbuffer(_arccos, function, index);
        return FOUND;
    }    
    else if(strncmp(str, "arctan", 6) == 0) {
        storeinbuffer(_arctan, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "sqrt", 4) == 0) {
        storeinbuffer(_sqrt, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "cbrt", 4) == 0) {
        storeinbuffer(_cbrt, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "log", 3) == 0) {
        storeinbuffer(_log, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "min", 3) == 0) {
        storeinbuffer(_min, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "max", 3) == 0) {
        storeinbuffer(_max, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "sum", 3) == 0) {
        storeinbuffer(_sum, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "avrg", 3) == 0) {
        storeinbuffer(_avrg, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "mean", 4) == 0) {
        storeinbuffer(_mean, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "median", 6) == 0) {
        storeinbuffer(_median, function, index);
        return FOUND;
    }   
    else if(strncmp(str, "var", 3) == 0) {
        storeinbuffer(_var, function, index);
        return FOUND;
    }
    else if(strncmp(str, "exp", 3) == 0) {
        storeinbuffer(_exp, function, index);
        return FOUND;
    }   
    else
        return NOT_FOUND;
}

int main(void)
{
    printf("Enter expresions: ");
    if(getexpr(stdin) == READ_ERR)
        printf("Error in read Aborted");
    
    return 0;
}
