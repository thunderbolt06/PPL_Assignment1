#include "grammar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>

int line_count;
FILE* sourceCode;

void menuOptions(int option, FILE* sourceFile, char* filename,){
    line_count = 1;
    switch(option){
        case 1:
            printf("\n\n Parse tree created \n");
            printf("*************************************************************************************\n");

        case 2:
            printf("\n\n Traverse the parse tree to construct typeExpressionTable. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable \n");
            printf("*************************************************************************************\n");

        case 3:
            printf("\n\n : Printing parse tree \n");
            printf("*************************************************************************************\n");

        case 4:
            printf("\n\n  Printing typeExpressionTable \n");
            printf("*************************************************************************************\n");

        default:
			printf("\n\nPLEASE ENTER A VALID OPTION BETWEEN 0 AND 4\n");
			return;
    }

    return;

}

int main(int argc, char* argv[])
{
	line_count = 1;


	//FIRST MESSAGE
	printf("\nStarting the program\n");

	//parser();
	int incorrect_attempts = 0;
	char filename[30];
	char* correctfile;

	do{
		if(incorrect_attempts>0)
		{
			printf("\n*************************** ERROR Opening the Source file (FILE NOT FOUND/ FILE NAME MORE THAN 30 CHARACTERS) ***************************\n\n\n");
			printf("Try Different Name: ");
			scanf("%s", filename);
			sourceCode = fopen(filename, "r");
			incorrect_attempts++;
		}
		else
		{
			sourceCode = fopen(argv[1], "r");
			incorrect_attempts++;
		}
	}while(sourceCode==NULL || strlen(filename)>30);

	incorrect_attempts--;

	if(incorrect_attempts==0)
		correctfile = argv[1];
	else
		correctfile = filename;

	printf("\n******************* OPENED FILE \"%s\"*******************\n\n", correctfile);
	fclose(sourceCode);

	int option;
	do{
		printf("\n*************************************************************************************");
		printf("\nMAIN MENU\n\n");
		printf("0 -> EXIT\n");
		printf("1 -> Create parse tree\n");
		printf("2 -> Traverse the parse tree to construct typeExpressionTable. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable.\n");
		printf("3 -> Print parse tree in the specified format \n");
		printf("4 -> Print typeExpressionTable in the specified format\n");

		printf("Select an option: ");
		scanf("%d", &option);
		sourceCode = fopen(correctfile, "r");
		if(option==0)
			break;
		menuOptions(option, sourceCode, correctfile);
	}while(1);
	fclose(sourceCode);
	printExitMsg();
	return 0;
}
