grammar Task1;

// Parser Rules
program : statement* EOF ;

statement 
    : switchStatement
    | printStatement
    | variableAssignment
    | '{' statement* '}' 
    ;

switchStatement 
    : 'switch' '(' expr ')' '{' switchBlockStatementGroup* defaultClause? '}'
    ;

switchBlockStatementGroup 
    : switchLabel+ statement*
    ;

switchLabel 
    : 'case' expr ':'
    ;

defaultClause 
    : 'default' ':' statement*
    ;

printStatement : 'print' '(' expr ')' ';' ;
variableAssignment : ID '=' expr ';' ;

// Renamed from 'expression' to 'expr' to match your Makefile
expr 
    : INT 
    | ID 
    | expr ('+'|'-') expr 
    ;

// Lexer Rules
SWITCH  : 'switch' ;
CASE    : 'case' ;
DEFAULT : 'default' ;
ID      : [a-zA-Z_][a-zA-Z0-9_]* ;
INT     : [0-9]+ ;
WS      : [ \t\r\n]+ -> skip ;