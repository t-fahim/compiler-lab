%{
#include <stdio.h>
#include <string.h>
#include "icg.tab.h"
%}

%%
[ \t]+          { } /* ignore spaces */

"+="            { return ADD_ASSIGN; }
"-="            { return SUB_ASSIGN; }
"*="            { return MUL_ASSIGN; }
"/="            { return DIV_ASSIGN; }
"%="            { return MOD_ASSIGN; }
"**="           { return POW_ASSIGN; }
"//="           { return IDIV_ASSIGN; }
"**"            { return POW; }
"//"            { return IDIV; }
"&&"            { return AND; }
"||"            { return OR; }

[0-9]+          { strcpy(yylval.cvar, yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]* { strcpy(yylval.cvar, yytext); return ID; }

[-+*/%<>=!()]   { return yytext[0]; }
\n              { return NEWLINE; }
.               { printf("Unknown: %s\n", yytext); }
%%

int yywrap() { return 1; }