#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "complib/complib.h"
#include "matxlib/matxlib.h"
#include "scilib/scilib.h"

typedef enum {
    scientific,
    matrix,
    complex,
    clear,
    quit,
}Choice;

typedef enum {
    commandline,
    interactive,
}Mode;

void PrintMainBoard(void);

int main(int argc, char **argv)
{
    int choice;
    Mode choiceOfMode;

    /* determine if user is in interactive or commandline mode */
    if(argc == 0)
        choiceOfMode = interactive;
    else
        choiceOfMode = commandline;

    if(choiceOfMode == commandline) {
        PrintMainBoard();
        do {
            printf("What do you want to do(choose from the above operation codes): ");
            scanf("%d", &choice);

            switch(choice) {
                case 0:
                    printf("quit\n");
                    return 0;
                case 1:
                    printf("scientific lib\n");
                    break;
                
                case 2:
                    printf("Matrixlib\n");
                    break;

                case 3:
                    printf("complex lib\n");
                    break;

                case 4:
                    printf("clear\n");
                    break;

                case 5:
                    printf("print\n");
                    break;
            }
        }while(1);
    }
}

void PrintMainBoard(void)
{
    printf("**** Command line calculator ****\n\n");
    printf(" \t0- quit\n \t1- Scientific calculator\n \t2- Matrix calculator\n \t3- Complex number Calculator\n"
            "\t4- Clear screen\n \t5- Print Opeation code dashboard\n\n");
}