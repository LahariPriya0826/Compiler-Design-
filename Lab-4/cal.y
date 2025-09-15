%{
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE double

int yylex(void);
int yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%

lines:
    lines expr '\n' { printf("Result: %g\n", $2); }
  | lines '\n'
  | /* empty */
  ;

expr:
    expr '+' expr { $$ = $1 + $3; }
  | expr '-' expr { $$ = $1 - $3; }
  | expr '*' expr { $$ = $1 * $3; }
  | expr '/' expr { 
      if ($3 == 0) {
          yyerror("division by zero");
          $$ = 0;
      } else {
          $$ = $1 / $3;
      }
    }
  | '(' expr ')' { $$ = $2; }
  | '-' expr %prec UMINUS { $$ = -$2; }
  | NUMBER
  ;

%%

int yylex(void) {
    int c;

    // Skip whitespace except newline
    while ((c = getchar()) == ' ');

    if (c == EOF) {
        return 0;
    }

    if (c == '.' || isdigit(c)) {
        ungetc(c, stdin);
        if (scanf("%lf", &yylval) != 1) {
            yyerror("Invalid number");
            exit(EXIT_FAILURE);
        }
        return NUMBER;
    }

    return c; // Return the character as token (e.g. '+', '-', '*', '/', '(', ')', '\n')
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}

int main(void) {
    printf("Enter expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}

