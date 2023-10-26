#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __MAX_TOKEN_LEN__ 512

typedef enum {
    normal,
    determinant,
    transpose,
    inverse,
}operation;

typedef enum {
    NOT_FOUND = 404,
    BAD_DIM = -3,
    ERR = -1,
    OK = 10,
}error_check;

/**
 * check_matxdim: Checks the matrix dimension, with respect
 *                to a refrence matrix if it is compatible for 
 *                a particular operation.
 * 
 * *str- The string holding the matrix.
 * row- The row of the refrence matrix.
 * col- The col of the refrence matrix.
 * op- The operation to be performed whith the matrix.
 * 
 * Return: returns BAD_DIM if the dimension isn't appropriate
 *          for operation, ERR if the operation isn't valid or
 *          OK if it all goes well.
*/
error_check check_matxdim(char *str, int row, int col, char op)
{
     char *s = str;

     int tcol = 0, trow = 0;

    switch(op) {
        case '+':
        case '-':
            while(*str != ';') {
                if(*str == ',') 
                    tcol++;
                str++;
            }
            tcol++;

            if(tcol != col) {
                fprintf(stderr, "Error: Non matching column\n");
                return BAD_DIM;
            }

            while(*s != '\0') {
                if(*s == ';')
                    trow++;
                s++;
            }

            if(trow != row) {
                fprintf(stderr, "Error: Non matching column\n");
                return BAD_DIM;
            }

            break;
        
        case '*':
             while(*s != '\0') {
                if(*s == ';')
                    trow++;
                s++;
            }

            if(trow != col) {
                fprintf(stderr, "Error: Mismatch for multimpication\n");
                return BAD_DIM;
            }
        
        default:
            return ERR;
    }

    return OK;
}


/**
 * mnatxinit: Initializes al elements of amatrix 
 *            to zero.
 * 
 * matx- The matrix.
 * row- The number of rows of the matrix
 * col- The number of columns of the matrix.
*/
void matxinit(int row, int col, int matx[row][col])
{
    int i, j;

    if(check_matxdim)
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            matx[i][j] = 0;
    }

}

/**
 * addmatx: Adds up two matrixes and stores the result
 *          in one of them.
 * 
 * matx- the first matrix
 * res- The other matrix, which will also hold the result of 
 *      computation.
 * row- The row of the matrices.
 * col- The column of the matrices.
*/
void addmatx(int row, int col, int matx[row][col], int res[row][col])
{
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            res[i][j] += matx[i][j];
    }    
}

/**
 * addmatx: Subtracts two matrixes and stores the result
 *          in one of them.
 * 
 * matx- the first matrix
 * res- The other matrix, which will also hold the result of 
 *      computation.
 * row- The row of the matrices.
 * col- The column of the matrices.
*/
void submatx(int row, int col, int matx[row][col], int res[row][col])
{
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            res[i][j] -= matx[i][j];
    }    
}

/**
 * eval: Checks the operation to be performed, and calls the 
 *       appropriate function to do it.
 * 
 * matx- The first matrix.
 * res- The other matrix, which will also store the result.
 * row- The row of the matrices.
 * col- The col of the matrices.
*/
void eval(int row, int col, int matx[row][col], int res[row][col], char op)
{
    switch(op) {
        case '+':
            addmatx(row, col, matx, res);
            break;
        case '-':
            submatx(row, col, matx, res);
            break;
        case '*':
            /*multiply*/
            break;
        default:
            return;
    }
}

/**
 * parseMatrix: Extracts the matrix from a string, and 
 *              converts it into integer storing it into the matrix.
 * 
 * str- String containing the matrix.
 * col- The column of the matrix.
 * row- The row of the matrix.
 * matrix- The matrix that would hold the converted matrix.
 * 
 * Return: returns a pointer to the next string in the input string.
*/
char *parseMatrix(char* str, int col, int row, int matrix[row][col])
{
    char *s = str;
    while(*s != '\0')
        s++;

    char *token = strtok(str, ",;");
    int i = 0, j = 0;

    while(token != NULL) {
        matrix[i][j] = atoi(token);
        j++;

        if (j == col) {
            j = 0;
            i++;
        }

        token = strtok(NULL, ",;");
    }
    return s + 1;
}

/**
 * find_matxdim: Finds the dimension of a matrix, and stores
 *              the value into it's other two arguements.
 * 
 * str- The string containing the matrix.
 * row- will contain the row of the matrix.
 * col- Will contain the column of the matrix.
*/
void find_matxdim(char *str, int *row, int *col)
{
    char *s = str;

    *row = 0;
    *col = 0;

    while(*str != ';') {
        if(*str == ',') 
            *col += 1;
        str++;
    }

    *col += 1;

    while(*s != '\0') {
        if(*s == ';')
            *row += 1;
        s++;
    }

}

/**
 * checkoperation: Determines the operation to be 
 *                 performed on a matrix, by reading it form the
 *                 input string.
 * 
 * *in: Pointer to the input string.
*/
operation checkoperation(char *in)
{
    char str[5];
    int i = 0;

    if(*in == '|')
        return determinant;
    
    if(isalpha(*in)) {
        str[i++] = *in++;
        while(*in != '(' && *in != '\n') {
            str[i++] = *in++;
        }
        str[i] = '\0';
    }
    else
        return normal;

    printf("op: %s\n", str);
    exit(EXIT_SUCCESS);

    if(strncmp(str, "trps", 4) == 0)
        return transpose;
    
    if(strncmp(str, "invs", 4) == 0)
        return inverse;
    
    return NOT_FOUND;


}

int main(void)
{   
    char input[__MAX_TOKEN_LEN__];
    char operator[__MAX_TOKEN_LEN__ / 2];
    char *p = '\0', *st = '\0';
    int i = 0, j = 0;
    int col, row, ind = 0;
    operation op;

    //printf("Enter matrix dimensions(mxn): ");
    //scanf("%dx%d", &row, &col);
    //getchar();

    printf("Enter matrix expression: ");
    fgets(input, sizeof(input), stdin);

    op = checkoperation(input);

    st = input;

    if((p = strpbrk(input, "+-*=")) != NULL) {
            operator[i++] = *p;
            *p = '\0';
    }   

    find_matxdim(input, &row, &col);
    //printf("rowxcol: %dx%d", row, col);

   // return 0;

    int matx[row][col];
    int result[row][col];

    matxinit(row, col, result);

    //printf("%d\n", op);

    //return 0;

    /**
     *  since operators seperate differnt matrixes
     * replace it with '\0' so they can be as seperate strigs
     */

   switch(op) {
        case normal:

            while(1) {
                p = strpbrk(p + 1, "+-*="); 
                if( p == NULL)
                    break;
                if(*p != '=')
                    operator[i++] = *p;
                *p = '\0';
            }
            operator[i] = '\0';

            p = parseMatrix(input, col, row, matx);
            addmatx(row, col, matx, result);

            while(*p != '\n') {
                if(p + 1 != NULL) {
                    if(ind < i && check_matxdim(p, row, col, operator[ind]) != OK) 
                        break;
                    p = parseMatrix(p, col, row, matx);
                    eval(row, col, matx, result, operator[ind++]);
                }
            }
            break;
        
        case determinant:
            p = input;
            if(check_matxdim(p, row, col, operator[ind]) == OK) {
                p = parseMatrix(p, col, row, matx);
                /* call determinant function */
            }
            break;

        case transpose:
            p = input;
            if(check_matxdim(p, row, col, operator[ind]) == OK) {
                p = parseMatrix(p, col, row, matx);
                /* call transpose function */
            }
            break;

   }   
    return 1;
} 
