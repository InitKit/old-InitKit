%{
#include "idb_parse.hh"
#include "idb_parse.tab.h"
%}

%option noyywrap
%option stack
%option yylineno
%option reentrant
%option extra-type = "idb_parser_t *"
%option prefix = "idb"
%option caseless

%{

#define YY_USER_ACTION \
    yyextra->recOldPos(); \
    for(int i = 0; yytext[i] != '\0'; i++) \
    { \
        if(yytext[i] == '\n') \
        { \
            yyextra->cr(); \
        } \
        else \
            yyextra->incCol(); \
    }

#define p(x) yyextra->parse(TOK_##x)
#define ps(x) yyextra->parse(TOK_##x, yytext)
#define pi(x) yyextra->parse(TOK_##x, atol(yytext))
#define pf(x) yyextra->parse(TOK_##x, atof(yytext))
#define ph(x) yyextra->parse(TOK_##x, strtol(yytext, NULL, 16))

%}

%%

 //"import"    { return p(IMPORT); }

"\n"        { p(NL); }

[^ \t\n"]+ { ps(TEXT); }

" " 
