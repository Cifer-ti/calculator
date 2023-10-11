#ifndef SCILIB_H
#define SCILIB_H

/**
 * getexpr: Reads the expression to be evaluated from a file stream,
 *          tokenizes it and stores into an array which contains the type of the token.
 * 
 * *stream- The input file  stream.
 * 
 * Return: Returns a pointer to an array of structures containing the tokens and their types.
*/
struct buffer *getexpr(FILE *stream);

#endif