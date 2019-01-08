This is the README file for Allie Robbins' Program Translation Project 2.
 
All files were written in C++.

List of files included in program:
  - scanner.cpp
  - scanner.h
  - main.cpp
  - token.h
  - makefile
  - README.txt
  - parser.cpp
  - parser.h
  - testTree.cpp
  - testTree.h

To execute the program:
    Run command "make" to build/compile the programs.
    Run command "./scanner "fileName" to run a program after it is built.

To clean the object files:
    Run command "make clean".

Purpose of program:
    The purpose of this program is to read from an input file and identify tokens.

Outline of Project 2 by file:
  main.cpp - reads in the command line arguments
           - opens the filename from argv[1]
           - reads from the file and stores values to an array
           - launches parser()
           - launched testTree()
  parser.cpp - declares the nodes of the tree
             - gets a new TK by calling scanner()
             - following the BNF logic, the tree moves through the logic depending on the given TK
             - If an incorrect grammar is found, the program terminates and prints an error
  scanner.cpp - when called, the scanner gets the next token
              - it returns a TK value and then finishes
  testTree.cpp - function to print the parse tree in preorder fashion
