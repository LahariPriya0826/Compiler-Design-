#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[20], stack[20];

int main() {
    char m[5][6][3] = {
        {"tb", " ",  " ",  "tb", " ",  " "},
        {" ",  "+tb"," ",  " ",  " ",  " "},
        {"n",  "n",  "fc", " ",  " ",  " "},
        {"fc", " ",  " ",  "n",  " ",  " "},
        {"n",  "*fc","a",  "n",  "n",  "i"}
    };

    int size[5][6] = {
        {2, 0, 0, 2, 0, 0},
        {0, 3, 0, 0, 0, 0},
        {1, 1, 2, 0, 0, 0},
        {2, 0, 0, 0, 1, 3},
        {0, 1, 1, 1, 0, 0}
    };

    int i, j, k, n, str1, str2;

    printf("\nEnter the input string: ");
    scanf("%s", s);
    strcat(s, "$");
    n = strlen(s);

    stack[0] = '$';
    stack[1] = 'e';  // Assuming 'e' is the start symbol here
    i = 1;  // stack top index
    j = 0;  // input index

    printf("\nStack\tInput\n");
    printf("______\n\n");

    while ((stack[i] != '$') && (s[j] != '$')) {
        if (stack[i] == s[j]) {
            i--;
            j++;
        } else {
            // Map stack top to row index
            switch (stack[i]) {
                case 'e': str1 = 0; break;
                case 'b': str1 = 1; break;
                case 't': str1 = 2; break;
                case 'c': str1 = 3; break;
                case 'f': str1 = 4; break;
                default:
                    printf("\nERROR");
                    exit(0);
            }

            // Map current input char to column index
            switch (s[j]) {
                case 'i': str2 = 0; break;
                case '+': str2 = 1; break;
                case '*': str2 = 2; break;
                case '(': str2 = 3; break;
                case ')': str2 = 4; break;
                case '$': str2 = 5; break;
                default:
                    printf("\nERROR");
                    exit(0);
            }

            if (m[str1][str2][0] == ' ') {
                printf("\nERROR");
                exit(0);
            } else if (m[str1][str2][0] == 'n') {
                i--;
            } else if (m[str1][str2][0] == 'i') {
                stack[i] = 'i';
            } else {
                for (k = size[str1][str2] - 1; k >= 0; k--) {
                    stack[i] = m[str1][str2][k];
                    i++;
                }
                i--;
            }
        }

        // Print stack
        for (k = 0; k <= i; k++)
            printf("%c", stack[k]);
        printf("\t");
        // Print remaining input
        for (k = j; k < n; k++)
            printf("%c", s[k]);
        printf("\n");
    }

    if (stack[i] == '$' && s[j] == '$')
        printf("\nSUCCESS\n");
    else
        printf("\nERROR\n");

    return 0;
}

