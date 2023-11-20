/* This is the library that takes care of complex numbers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int real;
    int imaginary;
} ComplexNumber;

int main() {
    char complexString[100]; // Assuming a maximum input length of 100 characters
    char* token;
    char* delimiter = " +-";
    char operation[100];
    char* p;
    int i = 0, j = 0;
    
    printf("Enter the complex string: ");
    fgets(complexString, sizeof(complexString), stdin);

    complexString[strcspn(complexString, "\n")] = '\0';
    
    int maxComplexNumbers = 10; // Maximum number of complex numbers to handle
    ComplexNumber complexNumbers[maxComplexNumbers];
    int numComplexNumbers = 0;

    p = strpbrk(complexString, "+-");
    while(p != NULL) {
        if(i % 2 != 0)
            operation[j++] = *p;
        p = strpbrk(p + 1, "+-");
        i++;
    }
    
    operation[j] = '\0';

    printf("Opetors: %s\n", operation);
    // Extract complex numbers from the input string
    token = strtok(complexString, delimiter);
    while (token != NULL) {
        complexNumbers[numComplexNumbers].real = atoi(token);
        token = strtok(NULL, " + -");
        
        if (token != NULL && token[strlen(token) - 1] == 'i') {
            if(strlen(token) == 1) {
                complexNumbers[numComplexNumbers].imaginary = 1;
                numComplexNumbers++;
            }
            else {
                token[strlen(token) - 1] = '\0'; // Remove the 'i' character
                complexNumbers[numComplexNumbers].imaginary = atoi(token);
                numComplexNumbers++;
            }
        }
        
        token = strtok(NULL, delimiter);
    }
    
    // Print the extracted complex numbers
    for (int i = 0; i < numComplexNumbers; i++) {
        printf("Complex Number %d: %d + %di\n", i+1, complexNumbers[i].real, complexNumbers[i].imaginary);
    }
    
    return 0;
}