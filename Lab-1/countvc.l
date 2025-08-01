%{
    int vow_count = 0;
    int const_count = 0;
%}

%%
[aeiouAEIOU]                  { vow_count++; }
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]  { const_count++; }
%%
int yywrap() { return 1; }

int main()
{
    printf("Enter the string of vowels and consonants:\n");
    yylex();
    printf("Number of vowels are: %d\n", vow_count);
    printf("Number of consonants are: %d\n", const_count);
    return 0;
}

