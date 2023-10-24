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

error_check check_matxdim(char *str, int row, int col, char op)
{
     char *s = str;

     int tcol, trow;

    switch(op) {
        case '+':
        case '-':
            while(*str != ';') {
                if(*str == ',') 
                    tcol++;
                str++;
            }
            tcol += 1;

            if(tcol != col) {
                fprintf(stderr, "Error: Non matching columng\n");
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


void matxinit(int row, int col, int matx[row][col])
{
    int i, j;

    if(check_matxdim)
    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            matx[i][j] = 0;
    }

}

void addmatx(int row, int col, int matx[row][col], int res[row][col])
{
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            res[i][j] += matx[i][j];
    }    
}

void submatx(int row, int col, int matx[row][col], int res[row][col])
{
    int i, j;

    for(i = 0; i < row; i++) {
        for(j = 0; j < col; j++)
            res[i][j] -= matx[i][j];
    }    
}

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
    char *p = '\0';
    int i = 0, j = 0;
    int col, row, ind = 0;
    operation op;

    //printf("Enter matrix dimensions(mxn): ");
    //scanf("%dx%d", &row, &col);
    //getchar();

    printf("Enter matrix expression: ");
    fgets(input, sizeof(input), stdin);

    find_matxdim(input, &row, &col);
    printf("rowxcol: %dx%d", row, col);

    int matx[row][col];
    int result[row][col];

    matxinit(row, col, result);

    op = checkoperation(input);

    /**
     *  since operators seperate differnt matrixes
     * replace it with '\0' so they can be as seperate strigs
     */

   switch(op) {
        case normal:
            p = strpbrk(input, "+-*=");
            operator[i++] = *p;
            *p = '\0';

            while(1) {
                p = strpbrk(p + 1, "+-=*"); 
                if( p == NULL)
                    break;
  
                operator[i++] = *p;
                *p = '\0';
            }
            operator[i] = '\0';

            p = parseMatrix(input, col, row, matx);
            addmatx(row, col, matx, result);

            while(*p != '\n') {
                if(p + 1 != NULL) {
                    if(check_matxdim(p, row, col, operator[ind]) == OK) {
                        p = parseMatrix(p, col, row, matx);
                        eval(row, col, matx, result, operator[ind++]);
                    }
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
