/* The routines in this library manages the scientific computations for this calculator */
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scilib.h"
#include "../stack/stack.h"

#define PI 3.14159265
#define OPERATOR 0
#define ANYTHING_ELSE 1
#define _END '?'    /* Marks the end of buffer array */
#define __MAX_FUNC_LEN__ 15

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
    _asin,
    _acos,
    _atan,
    _sqrt,
    _cbrt,
    _log,
    _loge,
    _exp,
    _roundup,
    _rounddwn,
    _min,
    _max,
    _sum,
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


struct buffer tokenbuffer[__MAX_TOKEN_LEN__];
struct buffer postfixbuffer[__MAX_TOKEN_LEN__];
Stack postfixStack;

int postind = 0;

static void storeinbuffer(int token, int flag, int *index)
{
    tokenbuffer[*index].token = token;
    tokenbuffer[*index].type_flag = flag;
    *index += 1;
}

static int checkfunction(int *ch, int *index)
{
    char str[__MAX_FUNC_LEN__];
    int i = 0;

    str[i++] = *ch;

    while((*ch = getchar()) != '(' && !isspace(*ch)) {
        if(i >= (__MAX_FUNC_LEN__ ))
            return NOT_FOUND;

        str[i++] = *ch;
    }

    if(isspace(*ch))
        return false;
    
    str[i] = '\0';

    if(strncmp(str, "floor", 5) == 0) {
        storeinbuffer(_rounddwn, function, index);
        return FOUND;
    }
    if(strncmp(str, "ceil", 4) == 0) {
        storeinbuffer(_roundup, function, index);
        return FOUND;
    }
    if(strncmp(str, "sin", 3) == 0) {
        storeinbuffer(_sin, function, index);
        return FOUND;
    }
    if(strncmp(str, "cos", 3) == 0) {
        storeinbuffer(_cos, function, index);
        return FOUND;
    }
    if(strncmp(str, "tan", 3) == 0) {
        storeinbuffer(_tan, function, index);
        return FOUND;
    }   
    if(strncmp(str, "asin", 6) == 0) {
        storeinbuffer(_asin, function, index);
        return FOUND;
    }   
    if(strncmp(str, "acos", 6) == 0) {
        storeinbuffer(_acos, function, index);
        return FOUND;
    }    
    if(strncmp(str, "atan", 6) == 0) {
        storeinbuffer(_atan, function, index);
        return FOUND;
    }   
    if(strncmp(str, "sqrt", 4) == 0) {
        storeinbuffer(_sqrt, function, index);
        return FOUND;
    }   
    if(strncmp(str, "cbrt", 4) == 0) {
        storeinbuffer(_cbrt, function, index);
        return FOUND;
    }   
    if(strncmp(str, "log", 3) == 0) {
        storeinbuffer(_log, function, index);
        return FOUND;
    }  
    if(strncmp(str, "loge", 4) == 0) {
        storeinbuffer(_loge, function, index);
        return FOUND;
    }   
    if(strncmp(str, "min", 3) == 0) {
        storeinbuffer(_min, function, index);
        return FOUND;
    }   
    if(strncmp(str, "max", 3) == 0) {
        storeinbuffer(_max, function, index);
        return FOUND;
    }   
    if(strncmp(str, "avrg", 3) == 0) {
        storeinbuffer(_avrg, function, index);
        return FOUND;
    }   
    if(strncmp(str, "median", 6) == 0) {
        storeinbuffer(_median, function, index);
        return FOUND;
    }   
    if(strncmp(str, "var", 3) == 0) {
        storeinbuffer(_var, function, index);
        return FOUND;
    }
    if(strncmp(str, "exp", 3) == 0) {
        storeinbuffer(_exp, function, index);
        return FOUND;
    }

    if(strncmp(str, "roundup", 8) == 0) {
        storeinbuffer(_roundup, function, index);
        return FOUND;
    }
    if(strncmp(str, "rounddwn", 8) == 0) {
        storeinbuffer(_rounddwn, function, index);
        return FOUND;
    } 
    _abs,
    fprintf(stderr, "Error: Function '%s' not found.\n", str);
    return NOT_FOUND;
}

int getexpr(FILE *stream)
{

    int type_to_be_read = ANYTHING_ELSE;
    int read, i = 0;
    double digit_read;

    while(read != EOF && read != '=') {
        if(type_to_be_read == ANYTHING_ELSE) {
            if(scanf("%lf ", &digit_read) == 1) {
               tokenbuffer[i].digitToken = digit_read;
               tokenbuffer[i++].type_flag = operand;
                type_to_be_read = OPERATOR;
            }
            
            /* if first thing read isn't a digit */
            else {
                while(isspace(read = getchar()) || read == '\t')
                    ;
                /* check if it's a fuction */
                if(isalpha(read)) {
                    if(checkfunction(&read, &i) != FOUND)
                        return READ_ERR;
                    /* When the checkfuction returns FOUND, the read most have already read
                    the next token which is the lbrace probaby */
                    storeinbuffer(read, lbrace, &i);
                    
                }

                else {      /* if not then must be a left brace */
                    storeinbuffer(read, lbrace, &i);
                } 
            }
        }

        else if(type_to_be_read == OPERATOR) {
            while(isspace(read = getchar()) || read == '\t')
                ;
            if(read == ',') {
                type_to_be_read = ANYTHING_ELSE;
                continue;
            }
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
    return i;
}



static int icp(int optn)
{
    switch(optn) {
        case '(':
            return 4;
            break;

        case '+':
        case '-':
            return 1;
            break;

        case '*':
        case '/':
        case '%':
            return 2;
            break;

        case '^':
            return 4;
            break;

        default:
            return -1;
            break;
    }
}

static int isp(int optr)
{
    switch(optr) {
        case '(':
            return 0;
            break;

        case '+':
        case '-':
            return 1;
            break;

        case '*':
        case '/':
        case '%':
            return 2;
            break;

        case '^':
            return 3;
            break;

        default:
            return -1;
            break;
    }
}


void postfixConvert(void)
{
    int i = 0, j = 0;
    struct buffer temp;
    struct buffer p;

    while(tokenbuffer[i].token != _END) {
        p = tokenbuffer[i++];
        switch(p.type_flag) {
            case operator:
                while(!isStackempty(postfixStack) && (isp(stacktop(postfixStack).token) >= icp(p.token)
                      || stacktop(postfixStack).type_flag == function))
                    postfixbuffer[j++] = stackpop(postfixStack);
                stackpush(postfixStack, p);
                break;
            
            case rbrace:
                while((!isStackempty(postfixStack)) && (temp = stackpop(postfixStack)).type_flag != lbrace)
                    postfixbuffer[j++] = temp;
                
                //while((!isStackempty(postfixStack)) && (temp = stackpop(postfixStack)).type_flag != lbrace)
                    //postfixbuffer[j++] = temp;
                break;
            
            case function:
            case lbrace:
                stackpush(postfixStack, p);
                break;
            
            default:
                postfixbuffer[j++] = p;
                break;
        }
    }

    while(!isStackempty(postfixStack))
        postfixbuffer[j++] = stackpop(postfixStack);
    

    postfixbuffer[j].token = _END;
    postfixbuffer[j].type_flag = end;
}

void evaluatefuctions(struct buffer b) {
    struct buffer temp1;
    struct buffer temp2;
    struct buffer tempans;
    double radian;

    switch(b.token) {
        case _sin:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = sin(radian);
            stackpush(postfixStack, tempans);
            break;
        
        case _cos:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = cos(radian);
            stackpush(postfixStack, tempans);
            break;
        
        case _tan:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = tan(radian);
            stackpush(postfixStack, tempans);
            break;

        case _asin:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = asin(radian);
            stackpush(postfixStack, tempans);
            break;
        
        case _acos:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = acos(radian);
            stackpush(postfixStack, tempans);
            break;
        
        case _atan:
            radian = (stackpop(postfixStack).digitToken) * PI / 180.0;
            tempans.digitToken = atan(radian);
            stackpush(postfixStack, tempans);
            break;
        
        case _sqrt:
            tempans.digitToken = sqrt(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;

        case _cbrt:
            tempans.digitToken = cbrt(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _log:
            tempans.digitToken = log10(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _loge:
            tempans.digitToken = log(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _exp:
            tempans.digitToken = exp(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _roundup:
            tempans.digitToken = ceil(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _rounddwn:
            tempans.digitToken = floor(stackpop(postfixStack).digitToken);
            stackpush(postfixStack, tempans);
            break;
        
        case _min:
            temp1.digitToken = stackpop(postfixStack).digitToken;
            temp2.digitToken = stackpop(postfixStack).digitToken;

            tempans.digitToken = temp1.digitToken < temp2.digitToken ? temp1.digitToken : temp2.digitToken;
            stackpush(postfixStack, tempans);
            break;

        case _max:
            temp1.digitToken = stackpop(postfixStack).digitToken;
            temp2.digitToken = stackpop(postfixStack).digitToken;

            tempans.digitToken = temp1.digitToken > temp2.digitToken ? temp1.digitToken : temp2.digitToken;
            stackpush(postfixStack, tempans);
            break;

        case _avrg:
            temp1.digitToken = stackpop(postfixStack).digitToken;
            temp2.digitToken = stackpop(postfixStack).digitToken;
            tempans.digitToken = (temp1.digitToken + temp2.digitToken) / 2;
            stackpush(postfixStack, tempans);
            break;
    }
}

double evaluate(void)
{
    struct buffer temp;
    struct buffer tempans;
    struct buffer p;

    while(1) {
        p = postfixbuffer[postind++];

        if(p.type_flag == end)
            break;
        switch(p.type_flag) {
            case operator:
                switch(p.token) {
                    case '+':
                        temp = stackpop(postfixStack);
                        tempans.digitToken = stackpop(postfixStack).digitToken + temp.digitToken;
                        stackpush(postfixStack, tempans);
                        break;
                    
                    case '-':
                        temp = stackpop(postfixStack);
                        tempans.digitToken = stackpop(postfixStack).digitToken - temp.digitToken;
                        stackpush(postfixStack, tempans);
                        break;
                    
                    case '/':
                        temp = stackpop(postfixStack);

                        if(temp.digitToken == 0) {
                            fprintf(stderr, "Math Error: Division by zero\n");
                            exit(EXIT_FAILURE);
                        }

                        tempans.digitToken = stackpop(postfixStack).digitToken / temp.digitToken;
                        stackpush(postfixStack, tempans);
                        break;stackpop(postfixStack).digitToken;
                    
                    case '*':
                        temp = stackpop(postfixStack);
                        tempans.digitToken = stackpop(postfixStack).digitToken * temp.digitToken;
                        stackpush(postfixStack, tempans);
                        break;
                    
                    case '^':
                        temp = stackpop(postfixStack);
                        tempans.digitToken = pow(stackpop(postfixStack).digitToken, temp.digitToken);
                        stackpush(postfixStack, tempans);
                        break;
                    
                    case '%':
                        temp = stackpop(postfixStack);
                        tempans.digitToken = (int)stackpop(postfixStack).digitToken % (int)temp.digitToken;
                        stackpush(postfixStack, tempans);
                        break;
                } 
                break;

            case function:
                evaluatefuctions(p);
                break;
            
            default:
                stackpush(postfixStack, p);
                break;
        }
    }

        return (stackpop(postfixStack).digitToken);
    
}


int main(void)
{   
    double ans;

    postfixStack = stackinit(__MAX_TOKEN_LEN__);

    printf("Enter expresions: ");
    if(getexpr(stdin) == READ_ERR) {
        printf("Error in read, Program aborted\n");
        exit(EXIT_FAILURE);
    }
    
    postfixConvert();

    ans = evaluate();

    printf("Answer = %lf\n", ans);
    
    return 0;
}
