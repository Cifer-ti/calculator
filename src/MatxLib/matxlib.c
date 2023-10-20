#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 512

void parseMatrix(char* str, int col, int row, int matrix[row][col])
{
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
}

int main(void)
{   
    char input[MAX_TOKEN_LEN];
    char operator[MAX_TOKEN_LEN / 2];
    char *p = '\0';
    int i = 0, col, row;

    printf("Enter matrix dimensions(mxn): ");
    scanf("%dx%d", &row, &col);
    getchar();

    int matx[row][col];

    printf("Enter matrix expression: ");
    fgets(input, sizeof(input), stdin);

    /*****************
     * remove the new line character
     *****************
     */
    //input[strcspn(input, "\n")] = '\0';
    //printf("yeah\n");

    /***************
     * mark all operations and store them in some sort of queue
     * **************
     * p = strpbrk(input, "+-=");
     * operator[i++] = *P;
     * for(i = 0;; *p != NULL; p++) {
     *   p = strpbrk(p + 1, "+-=");   
     *   operator[i] = *p;
     * }
     */
    printf("str: %s\n", input);
    p = strpbrk(input, "+-*=");
    operator[i++] = *p;
    *p = '\0';
    printf("no\n");
    printf("strpbk: %c\n", *p);
    while(1) {
        p = strpbrk(p + 1, "+-=*"); 
        if( p == NULL)
            break;
        printf("strpbk: %c\n", *p);  
        operator[i++] = *p;
        *p = '\0';
    }
    printf("str: %s\n", input);
    p = input;
    parseMatrix(input, col, row, matx);
    for(int i = 0; i < col; i++) {
        for(int j = 0; j < row; j++)
            printf("%d ", matx[i][j]);
        printf("\n");
    }
    while(*p != '\n') {
        if(*p == '\0' && p + 1 != NULL) {
            printf("%s\n", p + 1);
            parseMatrix(p + 1, col, row, matx);
            for(int i = 0; i < col; i++) {
                for(int j = 0; j < row; j++)
                    printf("%d ", matx[i][j]);
                printf("\n");
            }
        }
        p++;
    }

    return 1;

   /* use strtok function to start tokenizing the string */
   

} 
