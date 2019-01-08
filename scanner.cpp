#include "scanner.h"

/* scanner function that utilizes the FSA table to locate tokens (driver) */
token *scanner() {

	/* Variable Declarations */ 
	int current = FSATable[0][0];
	int lookAhead;
	int nextChar = getNext(data[index]);;
	string word;
	token *tempToken;

	/* While the scanner is running */
	while (current <= 100) {

		/* Find the current and look ahead values */
		nextChar = getNext(data[index]);
		lookAhead = FSATable[current][nextChar];

		/* If scanner returns a final state */
		if (lookAhead >= 100) {
			/* If value is an ID token */
			if (lookAhead == 101) {

			  /* Create and return the token */
				tempToken = createNewToken(lookAhead, lineNum, word);
				return tempToken;

			/* If value is a number token */
			} else if (lookAhead == 102) {

				/* Create and return the token */
				tempToken = createNewToken(lookAhead, lineNum, word);
				return tempToken;

				/* If value is a special charater token */
			} else {

				/* If value is a WS, new line, or EOF, append the value */
				if ((data[index] != ' ') && (data[index] != '\n') && (data[index] != '\0')) {
						word.push_back(data[index]);
				}

				if(lookAhead <= 100) {
					index++;
				}

				/* Create and return the token */
				tempToken = createNewToken(lookAhead, lineNum, word);
				return tempToken;

			}

		/* If the scanner returns a non-final state */
		} else {
				/* Move the placement marker to the lookAhead value */
				current = lookAhead;

				/* If the data value isn't a new line or a WS, append the value */
				if(data[index] != '\n' && data[index] != ' ') {
					word.push_back(data[index]);
				}
			}

		/* If the next value is a new line - increment the line count */
		if(data[index] == '\n') {
			lineNum++;
		}

		/* Increment the index to read the next position */
		index++;
	}

} /* End of scanner function */

/* Returns the ASCII value of the next character in the inputdata array */
int getNext(char ch) {

	if(isalpha(ch)) {									/* If char is a letter (identifier)*/
		return 1;
	} else if(isdigit(ch)) {					/* If char is a number */
		return 2;
	} else if(ch == '\n') {						/* If char is a end-of-line */
		return 24;
	} else if(ch == '\0') {						/* If char is a EOF */
		return 24;
	} else {

		int num = ch;
		switch(num) {
			case 13:
				return 24;
			case 32:			/* WS */
				return 24;
			case 35:			/* # */
				return 23;
			case 37:			/* % */
				return 13;
			case 38:			/* & */
				return 12;
			case 40:			/* ( */
				return 15;
			case 41:			/* ) */
				return 16;
			case 42:			/* * */
				return 10;
			case 43:			/* + */
				return 8;
			case 44:			/* , */
				return 17;
			case 45:			/* - */
				return 9;
			case 46:			/* . */
				return 14;
			case 47:			/* / */
				return 11;
			case 58:			/* : */
				return 7;
			case 59:			/* ; */
				return 20;
			case 60:			/* < */
				return 4;
			case 61:			/* = */
				return 3;
			case 62:			/* > */
				return 5;
			case 91:			/* [ */
				return 21;
			case 93:			/* ] */
				return 22;
			case 123:			/* { */
				return 18;
			case 125:			/* } */
				return 19;
			default:			/* If invalid char value - Scanner Error*/
				printf("Scanner Error : Invalid character: %c\nAborted.\n", (char)num);
				exit(EXIT_FAILURE);
		}
	}
}


/* function to assign the string value of the token */
token *createNewToken(int value, int line, string word) {

	/* Variable Declarations */
	token *tempToken = new token;

	tempToken->tokenID = value;
	tempToken->line = line;

	/* Using the values indicated by the FSA Table - assign the proper token type */
	switch (value) {
		case 554:
			tempToken->tokenType = "EOFTK";
			tempToken->tokenName = "EOF";
			return tempToken;
		case 555:
			tempToken->tokenType = "EOFTK";
			tempToken->tokenName = "EOF";
			return tempToken;
		case 101:
			tempToken->tokenType = "IDTK";
			break;
		case 102:
			tempToken->tokenType = "NumTK";
			break;
		case 103:
			tempToken->tokenType = "EqualTK";
			break;
		case 104:
			tempToken->tokenType = "LessTK";
			break;
		case 105:
			tempToken->tokenType = "GreatTK";
			break;
		case 106:
			tempToken->tokenType = "ColonTK";
			break;
		case 107:
			tempToken->tokenType = "PlusTK";
			break;
		case 108:
			tempToken->tokenType = "MinusTK";
			break;
		case 109:
			tempToken->tokenType = "AsteriskTK";
			break;
		case 110:
			tempToken->tokenType = "SlashTKN";
			break;
		case 111:
			tempToken->tokenType = "AmpersandTK";
			break;
		case 112:
			tempToken->tokenType = "ModTK";
			break;
		case 113:
			tempToken->tokenType = "PeriodTK";
			break;
		case 114:
			tempToken->tokenType = "OpParTK";
			break;
		case 115:
			tempToken->tokenType = "ClParTK";
			break;
		case 116:
			tempToken->tokenType = "CommaTK";
			break;
		case 117:
			tempToken->tokenType = "OpCurBraTK";
			break;
		case 118:
			tempToken->tokenType = "ClCurBraTK";
			break;
		case 119:
			tempToken->tokenType = "SemiCoTK";
			break;
		case 120:
			tempToken->tokenType = "OpBrackTK";
			break;
		case 121:
			tempToken->tokenType = "ClBrackTK";
			break;
		case 122:
			tempToken->tokenType = "PoundTK";
			break;
		default:
			printf("Scanner Error : Found token that does not exist: %i\n", value);
			exit(EXIT_FAILURE);
		}

		/* Compare the ID value against the keyword array */
	if(checkIfKeyword(word)) {
		tempToken->tokenType = "keyword";
		tempToken->tokenName = word;
    tempToken->isToken = 1;
	} else {
		tempToken->tokenName = word;
    tempToken->isToken = 0;
	}

	/* Print token info to the screen on a single line */
	/* printf("%s is a %s from Line %d\n", tempToken->tokenName.c_str(), tempToken->tokenType.c_str(), tempToken->line); */

	return tempToken;
}

/* Check if the passed string is a keyword defined by the language */
int checkIfKeyword(string word) {

	/* Loop through the array and return 1 if keyword is found */
	for(int i = 0; i < 10; i++) {
		if(!(word.compare(keywords[i]))) {
			return 1;
		}
	}

	return 0;
}
