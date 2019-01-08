#include "parser.h"

/* Variable Declarations */
token *TK;

/* Leading Parser of the program */
Node *parser() {
  printf("Entered parser.\n");

  /* Call the 1st token */
  TK = scanner();TK = scanner();
  printf("%s is a %s from Line %d\n", TK->tokenName.c_str(), TK->tokenType.c_str(), TK->line);

	/* Create the ROOT of the tree */
	Node *root = NULL;
  root = program();

  printf("\n Parser completed.\n\n");
  return root;

  /* Auxilary check for EOFTTK */
  if(TK->tokenID == 555) {
    printf("Parser completed!\n");
		return root;

	} else {
		printf("Parser Error : Missing expected EOF TK\n");
		exit(EXIT_FAILURE);
	}
}

/* <program> → void <vars> <block> */
Node *program() {
  printf("Entered program.\n");

	/* Create the next node of the tree */
	Node *newNode = createNode("<program>");

  /* If an IDTK is found and it is "void" */
	if(TK->tokenID == 101 && TK->tokenName == "void") {

    /* Consume the TK */
    TK = scanner();
    printf("%s is a %s from Line %d\n", TK->tokenName.c_str(), TK->tokenType.c_str(), TK->line);

    /* Declare the children of "program" */
		newNode->child1 = vars();
		newNode->child2 = block();

    /* Return from <program> */
		return newNode;

  } else {
		printf("Parser Error : Missing expected 'void' TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <block> → begin <vars> <stats> end */
Node *block() {
	printf("Entered block\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<block>");

  /* If an IDTK is found and it is "begin" */
	if(TK->tokenID == 101 && TK->tokenName == "begin") {

    /* Consume the TK */
    TK = scanner();

    /* Declare the children of "block" */
		newNode->child1 = vars();
		newNode->child2 = stats();

    /* If an IDTK is found and it is "end" */
		if(TK->tokenID == 101 && TK->tokenName == "end") {

      /* Return from "block" */
			return newNode;

		} else {
      printf("Scanner Error : Missing expected 'end' TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error: Missing expected 'begin' TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <vars> → empty | let Identifier = integer <vars> */
Node *vars() {
	printf("Entered vars\n");

  /* Create the next node of the tree */
	Node *newNode = createNode("<vars>");

  /* If the next TK is let */
  if(TK->tokenID == 101 && TK->tokenName == "let") {

    /* Consume the TK */
    TK = scanner();
    //printf("%s is a %s from Line %d\n", TK->tokenName.c_str(), TK->tokenType.c_str(), TK->line);

    /* If the next TK is an identifier */
    if(TK->tokenID == 101 && !TK->isToken) {
      newNode->TK.push_back(TK);
      /* Consume the TK */
      TK = scanner();

      newNode->child1 = vars();

      return newNode;

    } else {
      printf("Scanner Error : Missing expected ID TK \n");
      exit(EXIT_FAILURE);
    }
  }
}

/* <expr> → <A> / <expr> | <A> * <expr> | <A> */
Node *expr() {
	printf("Entered expr\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<expr>");

  /* Declare the child <A> */
	newNode->child1 = A();

  /* If the next TK is a / */
	if(TK->tokenID == 110) {
		newNode->TK.push_back(TK);
		/* Consume the TK */
    TK = scanner();


		newNode->child2 = A();
		return newNode;

  /* If the next TK is a * */
  } else if(TK->tokenID == 109) {
    newNode->TK.push_back(TK);
		/* Consume the TK */
    TK = scanner();


		newNode->child2 = A();
		return newNode;
	}

  /* Only A was called and explicit return */
	return newNode;
}

/* <A> → <M> + <A> | <M> - <A> | <M> */
Node *A() {
	printf("Entered A\n");
	/* Create the next node of the tree */
	Node *newNode = createNode("<A>");

	newNode->child1 = M();

  /* If the next TK is a + */
	if(TK->tokenID == 107) {
		newNode->TK.push_back(TK);
		/* Consume the TK */
    TK = scanner();


		newNode->child2 = A();
		return newNode;

  /* If the next TK is a - */
	} else if(TK->tokenID == 108) {
		newNode->TK.push_back(TK);
		/* Consume the TK */
    TK = scanner();


		newNode->child2 = A();
		return newNode;
	}

  /* Only M was called and explicit return */
	return newNode;
}

/* <M> → - <M> | <R> */
Node *M() {
	printf("Entered M\n");
	/* Create the next node of the tree */
	Node *newNode = createNode("<M>");

  /* If the next TK is a - */
	if(TK->tokenID == 108) {
		newNode->TK.push_back(TK);
		/* Consume the TK */
    TK = scanner();


    /* Declare the child <M> */
		newNode->child1 = M();

		return newNode;
	}

  /* Else declare the child <R> and continue*/
	newNode->child2 = R();

	return newNode;
}

/* <R> → ( <expr> ) | Identifier | Number */
Node *R() {
	printf("Entered R\n");

  /* Create the next node of the tree */
	Node *newNode = createNode("<R>");

  /* If the token is ( */
	if(TK->tokenID == 114) {

    /* Consume the TK */
    TK = scanner();


    /* Declare the children of R */
		newNode->child1 = expr();

    /* If the token is ) */
		if(TK->tokenID == 115) {

      /* Consume the TK and return */
    TK = scanner();


			return newNode;

		} else {
			printf("Scanner Error : Missing expected ) TK \n");
			exit(EXIT_FAILURE);
		}

    /* If the next TK is an ID TK */
	} else if(TK->tokenID == 101 && !TK->isToken) {
		newNode->TK.push_back(TK);

    /* Consume the TK and return */
    TK = scanner();


		return newNode;

    /* If the next TK is a # TK */
	} else if(TK->tokenID == 102) {
		newNode->TK.push_back(TK);

    /* Consume the TK and return */
    TK = scanner();


		return newNode;

	} else {
		printf("Scanner Error : Missing expected ID/# TK\n");
		exit(EXIT_FAILURE);
	}
}

/* <stats> → <stat> <mStat> */
Node *stats() {
	printf("Entered stats\n");

  /* Create the next node of the tree */
	Node *newNode = createNode("<stats>");

  /* Declare the children of <stats> */
	newNode->child1 = stat();
	newNode->child2 = mStat();

  /* Return from <stats> */
	return newNode;
}

/* <mStat> → empty | <stat> <mStat> */
Node *mStat() {
	printf("Entered mStat\n");

  /* Create the next node of the tree */
	Node *newNode = createNode("<mStat>");

  /* If the token is one of the First(in/out/block/if/loop/assign) */
	if((TK->tokenID == 101 && TK->tokenName == "read") ||
     (TK->tokenID == 101 && TK->tokenName == "print") ||
     (TK->tokenID == 101 && TK->tokenName == "begin") ||
     (TK->tokenID == 101 && TK->tokenName == "cond") ||
     (TK->tokenID == 101 && TK->tokenName == "iter") ||
     (TK->tokenID == 101 && TK->tokenName == "Identifier") ||
     (TK->tokenID == 101 && !TK->isToken)) {

    /* Declare the children of <mStat> */
		newNode->child1 = stat();
		newNode->child2 = mStat();

    /* Return from <mStat> */
		return newNode;
	}

  /* Explicit return (empty) */
	return newNode;

}

/* <stat> → <in> | <out> | <block> | <if> | <loop> | <assign> */
Node *stat() {
	printf("Entered stat\n");
	/* Create the next node of the tree */
	Node *newNode = createNode("<stat>");

  /* If the token is "read" → the child is <in> */
	if(TK->tokenID == 101 && TK->tokenName == "read") {
		newNode->child1 = in();

    /* Return from <stat> */
		return newNode;

  /* If the token is "print" → the child is <out> */
	} else if(TK->tokenID == 101 && TK->tokenName == "print") {
		newNode->child1 = out();

    /* Return from <stat> */
		return newNode;

  /* If the token is "begin" → the child is <block> */
} else if(TK->tokenID == 101 && TK->tokenName == "begin") {
		newNode->child1 = block();

    /* Return from <stat> */
		return newNode;

  /* If the token is "cond" → the child is <if> */
} else if(TK->tokenID == 101 && TK->tokenName == "cond") {
		newNode->child1 = ifStatement();

    /* Return from <stat> */
		return newNode;

  /* If the token is "iter" → the child is <loop> */
} else if(TK->tokenID == 101 && TK->tokenName == "iter") {
		newNode->child1 = loop();

    /* Return from <stat> */
		return newNode;

  /* If the token is IDTK → the child is <assign> */
	} else if(TK->tokenID == 101 && !TK->isToken) {
		newNode->child1 = assign();

    /* Return from <stat> */
		return newNode;

	} else {
    printf("Parser Error: Missing expected read/print/brgin/cond/iter/Identifier TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <in> → read ( Identifier ) : */
Node *in() {
	printf("Entered in\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<in>");

    /* If the token is "read" */
	if(TK->tokenID == 101 && TK->tokenName == "read") {

    /* Consume the TK */
    TK = scanner();


    /* If the token is ( */
		if(TK->tokenID == 114) {

			/* Consume the TK */
      TK = scanner();


      /* If the token is an ID TK */
			if(TK->tokenID == 101 && !TK->isToken) {

				newNode->TK.push_back(TK);
				/* Consume the TK */
        TK = scanner();


        /* If the token is a ) TK */
				if(TK->tokenID == 115) {
          /* Consume the TK */
					TK = scanner();


					return newNode;

				} else {
					printf("Parser Error : Missing expected ) TK \n");
					exit(EXIT_FAILURE);
				}

			} else {
				printf("Parser Error : Missing expected ID TK \n");
				exit(EXIT_FAILURE);
			}

		} else {
			printf("Parser Error : Missing expected ( TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error : Missing expected 'read' TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <out> → print ( <expr> ) : */
Node *out() {
	printf("Entered out\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<out>");

  /* IF the next token is 'print' */
	if(TK->tokenID == 101 && TK->tokenName == "print") {

    /* Consume the TK */
    TK = scanner();


    /* If the next token is ( */
		if(TK->tokenID == 114) {
			//newNode->TK.push_back(TK);
      /* Consume the TK */
      TK = scanner();


      /* Declare the child <exprs> */
			newNode->child1 = expr();

      /* If the next TK is ) */
			if(TK->tokenID == 115) {

        /* Consume the TK */
        TK = scanner();


        /* If the next TK is : */
        if(TK->tokenID == 106) {

          /* Consume the TK */
          TK = scanner();


        } else {
      			printf("Parser Error : Missing expected : TK \n");
      			exit(EXIT_FAILURE);
      		}

      } else {
  			printf("Parser Error : Missing expected ) TK \n");
  			exit(EXIT_FAILURE);
  		}

		} else {
			printf("Parser Error : Missing expected ( TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error : Missing expected 'print' TK \n");
		exit(EXIT_FAILURE);
	}
}

// <if> → cond ( <expr> <RO> <expr> ) <block>
Node *ifStatement() {
	printf("Entered if\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<if>");

  /* If the next TK is 'cond' */
	if(TK->tokenID == 101 && TK->tokenName == "cond") {

    /* Consume the TK */
    TK = scanner();


    /* If the next TK is ( */
		if(TK->tokenID == 114) {

      /* Consume the TK */
      TK = scanner();


      /* Declare the children <expr> <RO> <expr> */
			newNode->child1 = expr();
			newNode->child2 = RO();
			newNode->child3 = expr();

      /* If the next TK is ) */
			if(TK->tokenID == 115) {

        /* Consume the TK */
        TK = scanner();


        /* Declare the child <block> */
				newNode->child4 = block();

        /* Return from <if> */
				return newNode;

			} else {
				printf("Parser Error : Missing expected ) TK \n");
				exit(EXIT_FAILURE);
			}

		} else {
			printf("Scanner Error : Missing expected ( TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error: Missing expected 'cond' TK \n");
		exit(EXIT_FAILURE);
	}
}

// <loop> → iter ( <expr> <RO> <expr> ) <stat>
Node *loop() {
	printf("Entered loop\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<loop>");

   /* If the next TK is "iter" */
	if(TK->tokenID == 101 & TK->tokenName == "iter") {
    /* Consume the TK */
    TK = scanner();


    /* If the next TK is ( */
		if(TK->tokenID == 114) {

      /* Consume the TK */
      TK = scanner();


      /* Declare the children <expr> <RO> <expr> */
			newNode->child1 = expr();
			newNode->child2 = RO();
			newNode->child3 = expr();

      /* If the next TK is ) */
			if(TK->tokenID == 115) {
        /* Consume the TK */
        TK = scanner();


        /* Declare the child <stat>  */
				newNode->child4 = stat();

        /* Return from <loop> */
				return newNode;

			} else {
				printf("Scanner Error : Missing expected ) TK \n");
				exit(EXIT_FAILURE);
			}

		} else {
			printf("Parser Error : Missing expected ( TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error : Missing expected 'iter' TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <assign> → Identifier = <expr> : */
Node *assign() {
	printf("Entered assign\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<assign>");

  /* If the next TK is an ID TK*/
	if(TK->tokenID == 101 && !TK->isToken) {

    /* Consume the TK */
		newNode->TK.push_back(TK);
    TK = scanner();


    /* If the next TK is = */
		if(TK->tokenID == 103) {

      /* Consume the TK */
      TK = scanner();


      /* Declare the child <expr> */
      newNode->child1 = expr();

      /* If the next TK is : */
  		if(TK->tokenID == 106) {

        /* Consume the TK */
        TK = scanner();


        /* Return from <assign> */
        return newNode;

  		} else {
  			printf("Parser Error : Missing expected : TK \n");
  			exit(EXIT_FAILURE);
  		}

		} else {
			printf("Parser Error : Missing expected = TK \n");
			exit(EXIT_FAILURE);
		}

	} else {
		printf("Parser Error : Missing expected ID TK \n");
		exit(EXIT_FAILURE);
	}
}

/* <RO> → < | < = | > | > = | = = | = */
Node *RO() {
	printf("Entered RO\n");
  /* Create the next node of the tree */
	Node *newNode = createNode("<RO>");

  /* If the next TK is < */
	if(TK->tokenID == 104) {
		newNode->TK.push_back(TK);
    /* Consume the TK */
    TK = scanner();


    /* If the next TK is = aka <= */
		if(TK->tokenID == 103) {
			newNode->TK.push_back(TK);
      /* Consume the TK */
      TK = scanner();


			return newNode;
		}

		return newNode;

  /* If the next TK is > */
} else if(TK->tokenID == 105) {
		newNode->TK.push_back(TK);
    /* Consume the TK */
    TK = scanner();


    /* If the next TK is = aka >= */
		if(TK->tokenID == 103) {
			newNode->TK.push_back(TK);
      /* Consume the TK */
      TK = scanner();


			return newNode;
		}

		return newNode;

    /* If the next TK is = */
	} else if(TK->tokenID == 103) {
		newNode->TK.push_back(TK);
    /* Consume the TK */
    TK = scanner();


    /* If the next TK is = aka == */
    if(TK->tokenID == 103) {
	    newNode->TK.push_back(TK);
      /* Consume the TK */
      TK = scanner();


  		return newNode;
    }

    return newNode;

	} else {
    printf("Parser Error : Missing expected </< =/>/> =/= =/= TK \n");
		exit(EXIT_FAILURE);
	}
}

/* Function to create the nodes of the tree */
Node *createNode(string name) {
	Node* newNode = new Node();

  /* Default child values to NULL */
	newNode->child1 = NULL;
	newNode->child2 = NULL;
	newNode->child3 = NULL;
	newNode->child4 = NULL;
	newNode->name = name;

	return newNode;
}
