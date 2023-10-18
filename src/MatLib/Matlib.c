#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseMatrix(char* input, int matrix[2][2]) {
    char* token = strtok(input, ",;");
    int row = 0;
    int col = 0;

    while (token != NULL) {
        matrix[row][col] = atoi(token);
        col++;

        if (col == 2) {
            col = 0;
            row++;
        }

        token = strtok(NULL, ",;");
    }
}

void matrixAddition(int matrix1[2][2], int matrix2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
}

int main() {
    char input[100];
    int matrix1[2][2], matrix2[2][2], result[2][2];

    printf("Enter matrix1 plus matrix2: ");
    fgets(input, sizeof(input), stdin);

    char* equalsSign = strchr(input, '=');
    if (equalsSign == NULL) {
        printf("Invalid input format!\n");
        return 1;
    }

    *equalsSign = '\0';

    char* matrix1String = strtok(input, "+");
    char* matrix2String = equalsSign + 1;

    parseMatrix(matrix1String, matrix1);
    parseMatrix(matrix2String, matrix2);

    matrixAddition(matrix1, matrix2, result);

    printf("Result of matrix addition:\n");
    printf("%d, %d\n%d, %d\n", result[0][0], result[0][1], result[1][0], result[1][1]);

    return 0;
}