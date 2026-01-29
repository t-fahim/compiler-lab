%{
#include "parser.tab.h"
%}

%%
"switch"    { return SWITCH; }
"case"      { return CASE; }
"default"   { return DEFAULT; }
"print"     { return PRINT; }
[0-9]+      { yylval = atoi(yytext); return INT; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
"("         { return LPAREN; }
")"         { return RPAREN; }
":"         { return COLON; }
";"         { return SEMI; }
"="         { return ASSIGN; }
[ \t\n\r]+  { /* skip whitespace */ }
.           { printf("Unknown character: %s\n", yytext); }
%%

int yywrap() { return 1; }