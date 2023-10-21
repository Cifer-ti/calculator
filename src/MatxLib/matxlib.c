#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 512
#define NOT_FOUND 404

typedef enum {
    normal,
    determinant,
    transpose,
    inverse,
}operation;

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
    char input[MAX_TOKEN_LEN];
    char operator[MAX_TOKEN_LEN / 2];
    char *p = '\0';
    int i = 0, j = 0;
    int col, row, ind = 0;
    operation r;

    printf("Enter matrix dimensions(mxn): ");
    scanf("%dx%d", &row, &col);
    getchar();

    int matx[row][col];
    int rest[row][col];

    for(i = 0; i < row; i++) {
        for(int j = 0; j < col; j++)
            rest[i][j] = 0;
    }
    i = 0;

    printf("Enter matrix expression: ");
    fgets(input, sizeof(input), stdin);

    r = checkoperation(input);

    /**
     *  since operators seperate differnt matrixes
     * replace it with '\0' so they can be as seperate strigs
    */

   switch(r) {
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
            addmatx(row, col, matx, rest);


            while(*p != '\n') {
                if(p + 1 != NULL) {
                    p = parseMatrix(p, col, row, matx);
                    eval(row, col, matx, rest, operator[ind++]);
                }
            }
            break;
        
        case determinant:
            p = parseMatrix(p, col, row, matx);
            /* call determinant function */
            break;
        case transpose:
            p = parseMatrix(p, col, row, matx);
            /* call transpose function */
            break;
        



   }
    
    return 1;
} 
