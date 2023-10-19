#include <stdio.h>
#include <string.h>

#define MAX_TOKEN_LEN 512

int main(void)
{   
    char input[MAX_TOKEN_LEN];
    char operator[MAX_TOKEN_LEN / 2];
    char *p = '\0';
    int i = 0;

    printf("Enter matrix expression: ");
    fgets(input, sizeof(input), stdin);

    /*****************
     * remove the new line character
     *****************
     *
     *
     * 
     */
    input[strcspn(input, "\n")] = '\0';
    printf("yeah\n");

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
    p = strpbrk(input, "+-=");
    operator[i++] = *p;
    printf("no\n");
    printf("strpbk: %c\n", *p);
    while(1) {
        p = strpbrk(p + 1, "+-="); 
        if( p == NULL)
            break;
        printf("strpbk: %c\n", *p);  
        operator[i++] = *p;
    }
    return 1;

   /* use strtok function to start tokenizing the string */
   

} 