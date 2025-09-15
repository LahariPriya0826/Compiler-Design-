#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main() {
    int x = 0, n, i = 0, j = 0;
    void *mypointer;
    void *address[20];
    char input[100];
    char symbols[20];
    char c;

    printf("Input the expression ending with $ sign: ");
    while ((c = getchar()) != '$' && i < sizeof(input) - 1) {
        input[i++] = c;
    }
    input[i] = '\0';
    n = i - 1;

    printf("Given Expression: %s\n", input);

    printf("\nSymbol Table display\n");
    printf("Symbol \t Address \t Type\n");

    for (j = 0; j <= n; j++) {
        c = input[j];
        if (isalpha((unsigned char)c)) {
            mypointer = malloc(sizeof(char));
            if (mypointer == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            address[x] = mypointer;
            symbols[x] = c;
            printf("%c \t %p \t identifier\n", c, mypointer);
            x++;
        } 
        else if (c == '+' || c == '-' || c == '*' || c == '=') {
            mypointer = malloc(sizeof(char));
            if (mypointer == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
            address[x] = mypointer;
            symbols[x] = c;
            printf("%c \t %p \t operator\n", c, mypointer);
            x++;
        }
    }

    for (i = 0; i < x; i++) {
        free(address[i]);
    }

    return 0;
}

