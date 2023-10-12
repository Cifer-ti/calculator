#ifndef SCILIB_H
#define SCILIB_H

typedef struct buffer *Buffer;
#define __MAX_TOKEN_LEN__ 512
/**
 * getexpr: Reads the expression to be evaluated from a file stream,
 *          tokenizes it and stores into an array which contains the type of the token.
 * 
 * *stream- The input file  stream.
 * 
 * Return: Returns a pointer to an array of structures containing the tokens and their types.
*/
Buffer *getexpr(FILE *stream);
int storeinbuffer(int token, int flag, int index);
#endif