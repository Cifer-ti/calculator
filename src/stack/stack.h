#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include "../SciLib/scilib.h"

typedef struct stack *Stack;

/**
 * stackinit: Creates and initializes stack
 * 
 * s- The stack to be created;
 * size- The size to be allocated to stack.
 * 
 * Return: 0 if creation was successful else -1.
*/

Stack stackinit(int size);

/**
 * stackpush: Pushes an item into the stack.
 * 
 * s- Stack to be pushed unto.
 * token- The item to be pushed.
 * 
*/
void stackpush(Stack s, struct buffer token);

/**
 * stackpop: Pops an item from stack.
 * 
 * s- The stack to pop from.
 * 
 * Return: The item poped.
*/
struct buffer stackpop(Stack s);

/**
 * stacktop: Checks the top item of stack.
 *           Always run isstackempty() before running this.
 * 
 * s- The stack to check for top item.
 * 
 * Return: Returns the top item.
*/
struct buffer stacktop(Stack s);

/**
 * isstackfull: Checks if stack is full.
 * 
 * s- The stack to be checked.
 * 
 * Return: true if full false if not.
*/
bool isstackfull(Stack s);

/**
 * isstackempty: Checks if stack is empyty.
 * 
 * s- The stack to be checked.
 * 
 * Return: true if empyt false if not.
*/
bool isStackempty(Stack s);

void pri(Stack s);

#endif