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

ComplexNumber c1, c2;

OperationChoice Printoptions(void);
void getComplexnum(void);

int main() {
    char sign; // To store the '+' or '-' sign
    char i; // To store the 'i' character
    int choice;

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
                getComplexnum();
                //call addition routine
                break;
            
            case subtraction:
                printf("s\n");
                getComplexnum();
                //call subtraction routine
                break;
            
            case multiplication:
                printf("m\n");
                getComplexnum();

                //call multiplication routine
                break;
            
            case division:
                printf("d\n");
                getComplexnum();
                //call division routine
                break;
            
            case quit:
                printf("ex\n");
                exit(EXIT_FAILURE);
            
            case ERR:
                printf("er\n");
                continue;
        }
    }while(1);

    return 0;

}

OperationChoice Printoptions(void)
{
    printf("****Operations List****\n");
    printf("1- ADDITION\n 2- SUBTRACTION\n 3- MULTIPLICATION\n 4- DIVISION\n 0- EXIT\n");
}

void getComplexnum(void)
{   
    char i, sign;

    printf("Enter first complex number: ");
    if(scanf("%lf %c %lf %c", &c1.real, &sign, &c1.imaginary, &i) != 4) {
        fprintf(stderr, "Wrong format\n");
    }

    if(sign == '-')
        c1.imaginary = -c1.imaginary;

    printf("Enter second complex number: ");
   if(scanf("%lf %c %lf %c", &c2.real, &sign, &c2.imaginary, &i) != 4) {
        fprintf(stderr, "Wrong format\n");
    }

    if(sign == '-')
        c2.imaginary = -c2.imaginary;

}