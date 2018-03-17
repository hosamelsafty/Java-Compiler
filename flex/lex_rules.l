
DIGIT      [0-9]
DIGITS     DIGIT+
LETTER     [a-zA-Z]

ID         LETTER (LETTER|DIGIT)*

NUM        DIGITS | DIGITS . DIGITS (E DIGITS){0,1}

RELOP      \=\= | !\= | > | >\= | < | <\=

ASSIGN     \=

PRIMITIVE  boolean | int | float

FLOW   if | else | while

PUNCT  \; | \, | \( | \) | \[ | \] | \{ | \}

ADDOP  \+ | \-

MULOP  \* | \\

%%

ID          printf( "An identifier: %s\n", yytext );
PRIMITIVE   printf( "A primitive type: %s\n", yytext );
NUM         printf( "A number: %s\n", yytext );
RELOP       printf( "Relational Operator: %s\n", yytext );
ASSIGN      printf( "Assign: %s\n", yytext );
FLOW        printf( "Flow control: %s\n", yytext );
PUNCT       printf( "Punctuation: %s\n", yytext );
ADDOP       printf( "Add operator: %s\n", yytext );
MULOP       printf( "Mul operator: %s\n", yytext );

.	       printf( "Unrecognized character: %s\n", yytext );

%%

int main( int argc, char **argv )
{
    ++argv, --argc;	/* skip over program name */
    if ( argc > 0 )
        yyin = fopen( argv[0], "r" );
    else
        yyin = stdin;

    yylex();
}