%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"
%}

%union {
    char *string;
}

%token <string> NAME
%token <string> VALUE
%token <string> TEXT
%token OPEN_TAG CLOSE_TAG EMPTY_TAG GREATER_THAN EQUALS

%type <string> document elements element tag open_tag close_tag empty_tag attributes attribute

%%
document    : elements            { printf("%s\n", $1); free($1); }
            ;

elements    : element             { $$ = $1; }
            | elements element    { $$ = strcat($1, $2); free($2); }
            ;

element     : tag                 { $$ = $1; }
            | text                { $$ = $1; }
            ;

tag         : open_tag elements close_tag  { $$ = strcat($1, $2); $$ = strcat($$, $3); free($1); free($2); free($3); }
            | empty_tag             { $$ = strdup($1); free($1); }
            ;

open_tag    : OPEN_TAG attributes GREATER_THAN    { $$ = strdup($1); $$ = strcat($$, $2); $$ = strcat($$, ">"); free($1); free($2); }
            ;

close_tag   : CLOSE_TAG            { $$ = strdup($1); free($1); }
            ;

empty_tag   : OPEN_TAG attributes EMPTY_TAG       { $$ = strdup($1); $$ = strcat($
                                                                                 
                                                             
void yyerror(char const *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}

