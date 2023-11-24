#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "complib/complib.h"
#include "matxlib/matxlib.h"
#include "scilib/scilib.h"

typedef enum {
    quit,
    scientific,
    matrix,
    complex,
    clear,
    print,
    help,
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

    printf("argc: %d\n", argc);
    /* determine if user is in interactive or commandline mode */
    if(argc == 1)
        choiceOfMode = interactive;
    else
        choiceOfMode = commandline;

    printf("%d\n", choiceOfMode);
    if(choiceOfMode == interactive) {
        PrintMainBoard();
        do {
            printf("What do you want to do(choose from the above operation codes): ");
            scanf("%d", &choice);

            switch(choice) {
                case 0:
                    printf("quit\n");
                    return 0;
                case 1:
                    choice = scientific;
                    printf("scientific lib\n");
                    break;
                
                case 2:
                    printf("Matrixlib\n");
                    choice = matrix;
                    break;

                case 3:
                    printf("complex lib\n");
                    choice = complex;
                    break;

                case 4:
                    printf("clear\n");
                    break;

                case 5:
                    printf("print\n");
                    break;
            }
        } while(1);
    }

    else if(choiceOfMode == commandline) {
        int opt;

        struct option commandlineOptions[] = {
            {"sci", no_argument, NULL, 's'},
            {"matx", no_argument, NULL, 'm'},
            {"compx", no_argument, NULL, 'c'},
            {"help", no_argument, NULL, 'h'},
            {NULL, 0, NULL, 0},
        };

        while((opt = getopt_long(argc, argv, "smch", commandlineOptions, NULL)) != -1) {
            switch(opt) {
                case 's':
                case 'S':
                    printf("sic\n");
                    choice = scientific;
                    break;

                case 'm':
                    printf("moat\n");
                    choice = matrix;
                    break;
                
                case 'c':
                    printf("com\n");
                    choice = complex;
                    break;

                case 'h':
                case 'H':
                    printf("help\n");
                    choice = help;
                    break;

                case '?':
                    fprintf(stderr, "Try 'ls --help' for more information.\n");
                    break;
            }
        }
    }
}

void PrintMainBoard(void)
{
    printf("**** Command line calculator ****\n\n");
    printf(" \t0- quit\n \t1- Scientific calculator\n \t2- Matrix calculator\n \t3- Complex number Calculator\n"
            "\t4- Clear screen\n \t5- Print Opeation code dashboard\n\n");
}