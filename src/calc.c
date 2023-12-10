#include <getopt.h>
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include "complib/complib.h"
#include "matxlib/matxlib.h"
#include "scilib/scilib.h"

int choice = -1;

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
void dashboard(void);

static int parse_opt(int key, char *arg, struct argp_state *state)
{
    (void)*arg;
    (void)*state;
    switch(key) {
        case 's':
            choice = scientific;
            break;
        
        case 'm':
            choice = matrix;
            break;

        case 'c':
            choice = complex;
            break;
    }

    return 0;
}


int main(int argc, char **argv)
{
    Mode choiceOfMode;

    /* determine if user is in interactive or commandline mode */
    if(argc == 1)
        choiceOfMode = interactive;
    else
        choiceOfMode = commandline;

    if(choiceOfMode == interactive) {
        PrintMainBoard();
        dashboard();
    }

    else if(choiceOfMode == commandline) {

        static struct argp_option options[] = {
            {0, 0, 0, 0, "Calculator Mode:", 7},
            {"sci", 's', 0, 0, "perform normal operaions"},
            {"matx", 'm', 0, 0, "Perform matrix operations"},
            {"compx", 'c', 0, 0, "Perform operations on complex numbers"},
            {0, 0, 0, 0, "Information Options:", -1},
            {0}
        };

        struct argp argp = {options, parse_opt, 0, "A command line calculator"};

        argp_parse(&argp, argc, argv, 0, 0, 0);
    }

    while(1) {
        switch(choice) {
            case scientific:
                while(scimain() != l_quit)
                    ;
                break;
            
            case matrix:
                while(matxmain() != l_quit)
                    ;
                break;

            case complex:
                while(compxmain() != l_quit)
                    ;
                break;
            
            default :
                printf("Unsupported operation\n");
                break;
        }

        dashboard();
    }
}

void PrintMainBoard(void)
{
    printf("**** Command line calculator ****\n\n");
    printf(" \t0- quit\n \t1- Scientific calculator\n \t2- Matrix calculator\n \t3- Complex number Calculator\n"
            "\t4- Clear screen\n \t5- Print Opeation code dashboard\n\n");
}

void dashboard(void)
{
    int code;

    do {
            printf("\nWhat do you want to do(choose from the operation codes. '5' to see operation codes): ");

            if(scanf("%d", &code) != 1) { /* consume bad command */
                fprintf(stderr, "Error: code format not supported\n\n");
                while(getchar() != '\n')
                    ;
                continue;
            }
            getchar();


            switch(code) {
                case 0:
                    exit(EXIT_SUCCESS);

                case 1:
                    choice = scientific;
                    return;
                
                case 2:
                    choice = matrix;
                    return;

                case 3:
                    choice = complex;
                    return;

                case 4:
                    system("clear");
                    break;

                case 5:
                    PrintMainBoard();
                    break;
                
                default :
                    printf("Unreognised Code try '5' to check list of operation codes\n");
                    break;
            }
        } while(1);
}