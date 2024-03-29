/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#include "parser.c"
#include "tokeniseSourcecode.c"
#include "tokeniseSourcecode.h"
#include "parserDef.h"
#include "lexerDef.h"
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
struct Lexeme s;
struct grammar gram;
factor_nt=7;
//s.token = "START";
void menuOptions(int option, FILE* sourceFile, char* filename){
    line_count = 1;table T;
    switch(option){
        case 1:
            printf("Printing tokenised source code \n");
            tokeniseSourcecode(filename, &s);
            print_token_stream(s.next);


            FILE * fp = fopen("grammar.txt", "r");
	if(fp==NULL)
	{
		perror("Grammar file not found");
		exit(0);
	}
	char str[100];
	char* token;
	char* rest;
	char* lhsvalue;
	LHS* lhs;
	RHS* rhs;
	int i = 0;
	char prev_lhs_value[50] = "";
	int j =0;
	char temp[50] = "";
	gram.no_of_nt=0;


	while(fscanf(fp, "%[^\n]\n", str) != EOF)
	{
		rest = str;
		token = strtok_r(rest," ", &rest);
		if(i == 0)
		{
			gram.start=malloc(sizeof(LHS));
			gram.start[i].value=malloc(sizeof(char)*(strlen(token)+1));
			strcpy(gram.start[i].value, token);
			gram.start[i].head = NULL;
			gram.size=1;
		}
		else
		{
			LHS* ptr=gram.start;
			gram.start=realloc(gram.start,sizeof(LHS)*(i+1));
			gram.start[i].value=malloc(sizeof(char)*(strlen(token)+1));
			strcpy(gram.start[i].value, token);
			gram.start[i].head = NULL;
			gram.size++;
		}

		populate_nt(&gram);
		token = strtok_r(rest,"-", &rest);
		char str[]="#";
		if(!strcmp(token, str))
		{
			gram.start[i].e = 1;
			rhs = (RHS *)malloc(sizeof(RHS));
			gram.start[i].head = rhs;
			rhs->value=malloc(sizeof(char)*(strlen(token)+1));
			strcpy(rhs -> value, token);
			rhs -> next = NULL;
			i++;
			continue;
		}

		if((i != 0) && (!strcmp(gram.start[i-1].value, gram.start[i].value)) && (gram.start[i-1].e == 1))
			gram.start[i].e = 1;

		else
			gram.start[i].e = 0;

		rhs = (RHS *)malloc(sizeof(RHS));
		gram.start[i].head = rhs;
		rhs->value=malloc(sizeof(char)*(strlen(token)+1));
		strcpy(rhs -> value, token);
		rhs -> next = NULL;
		RHS * prev = rhs;

		while ((token = strtok_r(rest, "-", &rest)))
		{

				rhs = (RHS *)malloc(sizeof(RHS));
				prev -> next = rhs;
				rhs->value=malloc(sizeof(char)*(strlen(token)+1));
				strcpy(rhs -> value, token);
				rhs -> next = NULL;
				prev = rhs;
    		}
		i++;
	}
	find_nt(gram );



            //parseInputSourceCode(sourceFile, T, &s);
            //parser();
            printf("\n\n Grammar Imported \n");
            printf("\n\n Parse tree created \n");
            printf("*************************************************************************************\n");
            break;

        case 2:
            printf("\n\n Traverse the parse tree to construct typeExpressionTable. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable \n");
            printf("*************************************************************************************\n");
            break;

        case 3:
            //printParseTree(node* n);
            printf("\n\n : Printing parse tree \n");
            printf("*************************************************************************************\n");
            break;

        case 4:
            printf("\n\n  Printing typeExpressionTable \n");
            printf("*************************************************************************************\n");
            break;

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

	return 0;
}
