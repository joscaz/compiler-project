%{
#include "small_calc.tab.h"
%}

%% 

[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[+]           { return '+'; }
[\n]          { return EOL; }
[ \t]         ;
.             { return yytext[0]; }

%%