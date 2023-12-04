#include <getopt.h>
#include <argp.h>
#include <stdio.h>
#include <stdlib.h>
#include "complib/complib.h"
#include "matxlib/matxlib.h"
#include "scilib/scilib.h"

int choice = 0;

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

    printf("argc: %d\n", argc);
    /* determine if user is in interactive or commandline mode */
    if(argc == 1)
        choiceOfMode = interactive;
    else
        choiceOfMode = commandline;

    printf("%d\n", choiceOfMode);
    if(choiceOfMode == interactive) {
        PrintMainBoard();
        dashboard();
    }

    else if(choiceOfMode == commandline) {

        static struct argp_option options[] = {
            {"sci", 's', 0, 0, "perform normal operaions"},
            {"matx", 'm', 0, 0, "Perform matrix operations"},
            {"compx", 'c', 0, 0, "Perform operations on complex numbers"},
            {0}
        };

        struct argp argp = {options, parse_opt};

        argp_parse(&argp, argc, argv, 0, 0, 0);
    }

    switch(choice) {
        case scientific:
            scimain();
            break;
        case matrix:
            matxmain();
            break;
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
            printf("What do you want to do(choose from the operation codes): ");

            if(scanf("%d", &code) != 1) { /* consume bad command */
                while(getchar() != '\n')
                    ;
                continue;
            }


            switch(code) {
                case 0:
                    printf("quit\n");
                    exit(EXIT_SUCCESS);
                case 1:
                    choice = scientific;
                    printf("scientific lib\n");
                    return;
                
                case 2:
                    printf("Matrixlib\n");
                    choice = matrix;
                    return;

                case 3:
                    printf("complex lib\n");
                    choice = complex;
                    return;

                case 4:
                    printf("clear\n");
                    return;

                case 5:
                    printf("print\n");
                    return;
            }
        } while(1);
}