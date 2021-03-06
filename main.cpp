#include "project2.h"

/* Global Variable Declarations */
char *data = new char[500];
int index = 0;
int lineNum = 1;

int main(int argc, char *argv[]) {

  /* printf("This is main.cpp. Beginning program.\n"); */

  /* If no arguments were passed to the program */
  if (argc == 1) {
    printf("Main Error : You must pass a file to the program.\nAborted.\n");
    exit(EXIT_FAILURE);

    /* If there is one argument passed to the program */
    } else if (argc == 2) {

        /* Assign input file name to variable */
        FILE *testOpen = fopen(argv[1], "r");
        string inputFile(argv[1]);

        /* if file could not be opened */
        if (!testOpen) {
          printf("Main Error : File not found or could not be opened.\nAborted.\n");
				  exit(EXIT_FAILURE);
			    }

        /* Pass the file to a function to store all data in a character array */
        int size = fileToDataArray(inputFile, data);

        /* for (int i = 0; i < 55; i++)
          cout << data[i]; */

        /* Declare the root node and call the parser */
        Node *root;
        root = parser();

        /* Print the parse tree */
        testTree(root, 0);

    /* If too many arguments were passed to the program */
    } else if (argc > 2) {
        printf("Main Error : You've entered too many arguments. \nAborted.\n");
        exit(EXIT_FAILURE);
    }

   /* printf("Exiting main.cpp. Program completed.\n"); */
   return 0;

}/* End of main */

/* Function to transfer file data to a character array */
int fileToDataArray(string fileName, char *charArray) {

  /* Declare needed variables */
	int size = getFileSize(fileName);
	int num = 0;

  /* Open the input file*/
	FILE *file = fopen(fileName.c_str(), "r");
	if(file) {

    /* Read from the input file and store data into array */
		char value;
		while(true) {

			value = fgetc(file);

      /* If reader reaches the end of a line, assign \n value */
			if (value == '\n') {
				charArray[num] = value;
				num++;
				continue;

      /* If reader reaches the end of the file, assign EOF value */
    } else if (value == EOF) {
  				charArray[num] = '\0';
          num++;
  				break;

      } else if (value == '\t') {
        	size--;
        	continue;

        /* If reader finds a comment, assign # value */
  		} else if (value == '#') {
  				charArray[num] = value;
  				num++;

        /* Ignore the comment values until a WS is reached */
				do {
					value = fgetc(file);
					size--;
				} while(value != ' ');

				continue;

      /* If reader finds a "standard" element, save to array */
			} else {
				charArray[num] = value;
				num++;
			   }
		}

  /* If the input file could not be opened, exit program */
	} else {
		printf("Main Error : Could not open file \n");
		exit(EXIT_FAILURE);
	}

  /* Close the input file */
	fclose(file);
	charArray = (char*)realloc(charArray, size);

  /* Return file size to MAIN */
	return size;
}

/* Function to get the size of the input file */
int getFileSize(string fileName) {

  /* Open the input file */
	ifstream file(fileName.c_str(), ios::in);

  /* Calculate the difference between start & finish */
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.close();

  /* Return file size */
	return size;
}
