#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <unistd.h>
#include <fstream>
#include "token.h" 

using namespace std;

/* Variable Declarations*/
extern int index;
extern char *data;
extern int lineNum;

/* Prototypes */
token *scanner();
int getNext(char);
token *createNewToken(int, int, string);
int checkIfKeyword(string);

#endif
