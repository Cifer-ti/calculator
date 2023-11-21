#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double real;
    double imaginary;
} ComplexNumber;

typedef enum {
    quit,
    addition,
    subtraction,
    multiplication,
    division,
    ERR,
}OperationChoice;

OperationChoice Printoptions(void);
void getComplexnum(ComplexNumber *z1, ComplexNumber *z2);
void complexAddition(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexSubtraction(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexMultiplication(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);
void complexDivision(ComplexNumber z1, ComplexNumber z2, ComplexNumber *ans);

int main() {
    char sign; // To store the '+' or '-' sign
    char i; // To store the 'i' character
    int choice;
    ComplexNumber c1, c2, ans;

    printf("\n*** Simple complex number calculator ***\n\n");
    printf("*** Numbers should be entered in format 'a + bi'. ***\n"
            "# If a complex number lacks a part specify by replacing it with zero #\n\n");
        
    Printoptions();
    do {

        printf("what do you want to do: ");
        scanf("%d", &choice);

        switch(choice) {
            case addition:
                printf("a\n");
                getComplexnum(&c1, &c2);
                complexAddition(c1, c2, &ans);
                //call addition routine
                break;
            
            case subtraction:
                printf("s\n");
                getComplexnum(&c1, &c2);
                complexSubtraction(c1, c2, &ans);
                //call subtraction routine
                break;
            
            case multiplication:
                printf("m\n");
                getComplexnum(&c1, &c2);
                complexMultiplication(c1, c2, &ans);
                //call multiplication routine
                break;
            
            case division:
                printf("d\n");
                getComplexnum(&c1, &c2);
                complexDivision(c1, c2, &ans);
                //call division routine
                break;
            
            case quit:
                printf("ex\n");
                exit(EXIT_FAILURE);
            
            case ERR:
                printf("er\n");
                continue;
        }
        printf("Answer = %.2lf + %.2lfi\n", ans.real, ans.imaginary);
    }while(1);

    return 0;

}

OperationChoice Printoptions(void)
{
    printf("****Operations List****\n");
    printf("1- ADDITION\n 2- SUBTRACTION\n 3- MULTIPLICATION\n 4- DIVISION\n 0- EXIT\n");
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