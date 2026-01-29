%{
#include <stdio.h>
#include <stdlib.h>

// Prototypes
void yyerror(const char *s);
int yylex();
%}

/* Token definitions */
%token SWITCH CASE DEFAULT PRINT ID INT
%token PLUS MINUS LBRACE RBRACE LPAREN RPAREN COLON SEMI ASSIGN

/* Operator precedence */
%left PLUS MINUS

%%

program:
    statements
    ;

statements:
    /* One or more statements */
    statement
    | statements statement
    ;

statement:
    switchStatement
    | printStatement
    | variableAssignment
    | varDeclaration
    | LBRACE statements RBRACE
    ;

switchStatement:
    SWITCH LPAREN expr RPAREN LBRACE switchGroups defaultOptional RBRACE
    ;

/* One or more case groups */
switchGroups:
    switchGroup
    | switchGroups switchGroup
    ;

switchGroup:
    labels statements
    ;

labels:
    labels switchLabel
    | switchLabel
    ;

switchLabel:
    CASE expr COLON
    ;

defaultOptional:
    /* empty */
    | DEFAULT COLON statements
    ;

printStatement:
    PRINT LPAREN expr RPAREN SEMI
    ;

variableAssignment:
    ID ASSIGN expr SEMI
    ;

varDeclaration:
    INT ID ASSIGN expr SEMI
    ;

expr:
    INT
    | ID
    | LPAREN expr RPAREN
    | expr PLUS expr
    | expr MINUS expr
    ;

%%

// Error reporting
void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    if (yyparse() == 0) {
        printf("\nSuccess: Input matches the Switch-Case grammar!\n");
    } else {
        printf("\nFailure: Syntax errors detected.\n");
    }
    return 0;
}
