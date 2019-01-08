#ifndef TOKEN_H
#define TOKEN_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string>

using namespace std;

/* Tripolet token struct definition  */
typedef struct token {
  int tokenID;
  string tokenName;
  string tokenType;
  int line;
  int isToken;
} token;

/* Reserved keywords array */
static const char *keywords[12] = {"begin", "end", "iter", "void", "var", "return", "read", "print", "program", "cond", "then", "let"};

/* FSA TABLE                       L     D     =    <    >    :    +    -    *    /    &    %    .    (    )    ,    {    }    ;    [    ]    #   WS  EOF */
static int FSATable[3][25] = {{0,    1,   2, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,   0, 555},
                              {1,    1,   1, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101},
                              {2,  102,   2, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102}};

#endif
