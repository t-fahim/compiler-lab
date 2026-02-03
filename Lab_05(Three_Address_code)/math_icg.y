%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern FILE* yyin;
int yylex(void);
void yyerror(char *s);

int t_count = 1;
int line_no = 1;

char* getTemp() {
    char *ret = (char *)malloc(20);
    sprintf(ret, "t%d", t_count++);
    return ret;
}
%}

%union { char cvar[64]; }

%token <cvar> NUM ID
%token SQRT POW LOG EXP SIN COS TAN ABS NEWLINE

%type <cvar> Expression Term Factor FunctionCall

%left '+' '-'
%left '*' '/' '%'

%%
Program: StatementList ;

StatementList:
      Statement
    | StatementList NEWLINE Statement
    ;

Statement:
      ID '=' Expression { printf("%d %s = %s\n", line_no++, $1, $3); }
    | /* empty */
    ;

Expression:
      Expression '+' Term { strcpy($$, getTemp()); printf("%d %s = %s + %s\n", line_no++, $$, $1, $3); }
    | Expression '-' Term { strcpy($$, getTemp()); printf("%d %s = %s - %s\n", line_no++, $$, $1, $3); }
    | Term                { strcpy($$, $1); }
    ;

Term:
      Term '*' Factor { strcpy($$, getTemp()); printf("%d %s = %s * %s\n", line_no++, $$, $1, $3); }
    | Term '/' Factor { strcpy($$, getTemp()); printf("%d %s = %s / %s\n", line_no++, $$, $1, $3); }
    | Term '%' Factor { strcpy($$, getTemp()); printf("%d %s = %s %% %s\n", line_no++, $$, $1, $3); }
    | Factor          { strcpy($$, $1); }
    ;

Factor:
      FunctionCall          { strcpy($$, $1); }
    | '(' Expression ')'    { strcpy($$, $2); }
    | ID                    { strcpy($$, $1); }
    | NUM                   { strcpy($$, $1); }
    | '-' Factor            { strcpy($$, getTemp()); printf("%d %s = -%s\n", line_no++, $$, $2); }
    ;

FunctionCall:
      SQRT '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = sqrt ( %s )\n", line_no++, $$, $3); }
    | POW '(' Expression ',' Expression ')' { strcpy($$, getTemp()); printf("%d %s = pow ( %s , %s )\n", line_no++, $$, $3, $5); }
    | LOG '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = log ( %s )\n", line_no++, $$, $3); }
    | EXP '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = exp ( %s )\n", line_no++, $$, $3); }
    | SIN '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = sin ( %s )\n", line_no++, $$, $3); }
    | COS '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = cos ( %s )\n", line_no++, $$, $3); }
    | TAN '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = tan ( %s )\n", line_no++, $$, $3); }
    | ABS '(' Expression ')' { strcpy($$, getTemp()); printf("%d %s = abs ( %s )\n", line_no++, $$, $3); }
    ;

%%
void yyerror(char *s) { fprintf(stderr, "Error: %s\n", s); }

int main() {
    // UPDATED FILE NAME HERE
    yyin = fopen("math_input.txt", "r");
    if(!yyin) { printf("Error: math_input.txt not found!\n"); return 1; }
    yyparse();
    return 0;
}