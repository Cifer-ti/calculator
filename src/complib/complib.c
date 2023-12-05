#include <stdio.h>
#include <stdlib.h>
#include "complib.h"

typedef struct {
    double real;
    double imaginary;
} ComplexNumber;

typedef enum {
    Exit,
    addition,
    subtraction,
    multiplication,
    division,
    Clear,
    optionBoard,
    quit,
}OperationChoice;

OperationChoice Printoptions(void);
void getComplexnum(ComplexNumber *z1, ComplexNumber *z2);
void complexAddition(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexSubtraction(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexMultiplication(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexDivision(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);

int compxmain(void) {
    char sign; // To store the '+' or '-' sign
    char i; // To store the 'i' character
    int choice;
    ComplexNumber c1, c2, ans;

    printf("\n*** Simple complex number calculator ***\n\n");
    printf("*** Numbers should be entered in format 'a + bi'. ***\n"
            "# If a complex number lacks a part specify by replacing it with zero #\n\n");
        
    Printoptions();
    do {

        printf("what do you want to do ('6' to show operation board): ");
        if(scanf("%d", &choice) != 1) {
            fprintf(stderr, "\nError: Code format not supported! Try '6' to see operation code board\n\n");
            while(getchar() != '\n')    /* consume bad code */
                ;
            continue;
        }

        switch(choice) {
            case addition:
                getComplexnum(&c1, &c2);
                complexAddition(c1, c2, &ans);
                printf("Answer = %.2lf + %.2lfi\n", ans.real, ans.imaginary);
                break;
            
            case subtraction:
                getComplexnum(&c1, &c2);
                complexSubtraction(c1, c2, &ans);
                printf("Answer = %.2lf + %.2lfi\n", ans.real, ans.imaginary);
                break;
            
            case multiplication:
                getComplexnum(&c1, &c2);
                complexMultiplication(c1, c2, &ans);
                printf("Answer = %.2lf + %.2lfi\n", ans.real, ans.imaginary);
                break;
            
            case division:
                getComplexnum(&c1, &c2);
                complexDivision(c1, c2, &ans);
                printf("Answer = %.2lf + %.2lfi\n", ans.real, ans.imaginary);
                break;
            
            case Exit:
                exit(EXIT_SUCCESS);
            
            case Clear:
                system("clear");
                continue;
                break;
            
            case optionBoard:
                Printoptions();
                continue;
                break;
            
            case quit:
                return l_quit;
            
            default:
                fprintf(stderr, "\n# Operation code %d not recognised #\n", choice);
                fprintf(stderr, "Try code '6' to check operation board\n\n");
                continue;
                break;
        }

    } while(1);

    return 0;

}

OperationChoice Printoptions(void)
{
    printf("**** Operations code List ****\n\n");
    printf(" \t0- EXIT\n \t1- ADDITION\n \t2- SUBTRACTION\n \t3- MULTIPLICATION\n \t4- DIVISION\n \t5- clear\n"
            "\t6- Show option board\n \t7- quit\n\n");
}

void getComplexnum(ComplexNumber *z1, ComplexNumber *z2)
{   
    char i, sign;

    printf("Enter first complex number: ");
    if(scanf("%lf %c %lf %c", &z1->real, &sign, &z1->imaginary, &i) != 4) {
        fprintf(stderr, "Wrong format\n");
    }

    if(sign == '-')
        z1->imaginary = -z1->imaginary;

    printf("Enter second complex number: ");
   if(scanf("%lf %c %lf %c", &z2->real, &sign, &z2->imaginary, &i) != 4) {
        fprintf(stderr, "Wrong format\n");
    }

    if(sign == '-')
        z2->imaginary = -z2->imaginary;

}

void complexAddition(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans)
{
    ans->real = z1.real + z2.real;
    ans->imaginary = z1.imaginary + z2.imaginary;
}

void complexSubtraction(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans)
{
    ans->real = z1.real - z2.real;
    ans->imaginary = z1.imaginary - z2.imaginary;
}

void complexMultiplication(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans)
{
    ans->real = (z1.real * z2.real) - (z1.imaginary * z2.imaginary);
    ans->imaginary = (z1.real * z2.imaginary) + (z1.imaginary * z2.real);
}

void complexDivision(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans)
{
    int divisor = (z2.real * z2.real) - (z2.imaginary * z2.imaginary);

    if(divisor == 0) {
        fprintf(stderr, "Divisor resultsl to zero\n");
        exit(EXIT_FAILURE);
    }
    ans->real = ((z1.real * z2.real) - (z1.imaginary * z2.imaginary)) / divisor;
    ans->imaginary = ((z1.real * z2.imaginary) + (z1.imaginary * z2.real)) / divisor;
}