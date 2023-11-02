#ifndef SCILIB_H
#define SCILIB_H

#define __MAX_TOKEN_LEN__ 512
#define NOT_FOUND 404
#define FOUND 1
#define READ_ERR -99
#define OK 100

struct buffer {
    int token;
    double digitToken;
    int type_flag;
};

typedef struct buffer *Buffer;
/**
 * getexpr: Reads the expression to be evaluated from a file stream,
 *          tokenizes it and stores into an array which contains the type of the token.
 * 
 * *stream- The input file  stream.
 * 
 * Return: Returns a pointer to an array of structures containing the tokens and their types.
*/
int getexpr(FILE *stream);

/**
 * postfixconvert: Converts the input into postfix notation.
*/
void postfixConvert(void);

double evaluate(void);

#endif