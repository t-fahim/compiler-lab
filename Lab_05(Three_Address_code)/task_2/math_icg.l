%{
#include <stdio.h>
#include <string.h>
#include "math_icg.tab.h"
%}

%%
[ \t]+          { } /* skip spaces */

"sqrt"          { return SQRT; }
"pow"           { return POW; }
"log"           { return LOG; }
"exp"           { return EXP; }
"sin"           { return SIN; }
"cos"           { return COS; }
"tan"           { return TAN; }
"abs"           { return ABS; }

[0-9]+          { strcpy(yylval.cvar, yytext); return NUM; }
[a-zA-Z][a-zA-Z0-9]* { strcpy(yylval.cvar, yytext); return ID; }

[-+*/%=(),]     { return yytext[0]; }
\n              { return NEWLINE; }

.               { printf("Unknown: %s\n", yytext); }
%%

int yywrap() { return 1; }