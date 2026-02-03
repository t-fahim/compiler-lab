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
%token ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN POW_ASSIGN IDIV_ASSIGN
%token POW IDIV AND OR NEWLINE

%type <cvar> expr term factor unary primary

%left OR
%left AND
%left '<' '>'
%left '+' '-'
%left '*' '/' '%' IDIV
%right POW
%right '!'

%%
program: 
      program stmt
    | stmt
    ;

stmt:
      ID '=' expr NEWLINE { printf("%d %s = %s\n", line_no++, $1, $3); }
    | ID ADD_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s + %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID SUB_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s - %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID MUL_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s * %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID DIV_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s / %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID MOD_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s %% %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID POW_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s ** %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | ID IDIV_ASSIGN expr NEWLINE { char *t = getTemp(); printf("%d %s = %s // %s\n", line_no++, t, $1, $3); printf("%d %s = %s\n", line_no++, $1, t); }
    | NEWLINE
    ;

expr:
      expr '+' term    { strcpy($$, getTemp()); printf("%d %s = %s + %s\n", line_no++, $$, $1, $3); }
    | expr '-' term    { strcpy($$, getTemp()); printf("%d %s = %s - %s\n", line_no++, $$, $1, $3); }
    | expr OR term     { strcpy($$, getTemp()); printf("%d %s = %s || %s\n", line_no++, $$, $1, $3); }
    | expr AND term    { strcpy($$, getTemp()); printf("%d %s = %s && %s\n", line_no++, $$, $1, $3); }
    | expr '>' term    { strcpy($$, getTemp()); printf("%d %s = %s > %s\n", line_no++, $$, $1, $3); }
    | expr '<' term    { strcpy($$, getTemp()); printf("%d %s = %s < %s\n", line_no++, $$, $1, $3); }
    | term             { strcpy($$, $1); }
    ;

term:
      term '*' factor  { strcpy($$, getTemp()); printf("%d %s = %s * %s\n", line_no++, $$, $1, $3); }
    | term '/' factor  { strcpy($$, getTemp()); printf("%d %s = %s / %s\n", line_no++, $$, $1, $3); }
    | term IDIV factor { strcpy($$, getTemp()); printf("%d %s = %s // %s\n", line_no++, $$, $1, $3); }
    | term '%' factor  { strcpy($$, getTemp()); printf("%d %s = %s %% %s\n", line_no++, $$, $1, $3); }
    | factor           { strcpy($$, $1); }
    ;

factor:
      factor POW unary { strcpy($$, getTemp()); printf("%d %s = %s ** %s\n", line_no++, $$, $1, $3); }
    | unary            { strcpy($$, $1); }
    ;

unary:
      '!' primary      { strcpy($$, getTemp()); printf("%d %s = ! %s\n", line_no++, $$, $2); }
    | '-' primary      { strcpy($$, getTemp()); printf("%d %s = - %s\n", line_no++, $$, $2); }
    | primary          { strcpy($$, $1); }
    ;

primary:
      ID               { strcpy($$, $1); }
    | NUM              { strcpy($$, $1); }
    | '(' expr ')'     { strcpy($$, $2); }
    ;

%%
void yyerror(char *s) { fprintf(stderr, "Error: %s\n", s); }

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) return 1;
    yyparse();
    return 0;
}