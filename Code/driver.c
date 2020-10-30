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
	int sum=0;
	F.first=malloc(sizeof(First)*(gram.no_of_nt));
	F.follow=malloc(sizeof(Follow)*(gram.no_of_nt));

	for(int i=0;i<gram.no_of_nt;i++)
	{
		F.first[i].size_first_list=0;
		F.follow[i].size_follow_list=0;
		F.first[i].e=0;
		F.follow[i].d=0;
	}


	hash_nt_ptr=malloc(sizeof(hash_nt*)*factor_nt);


	for(int i=0;i<factor_nt;i++)
		hash_nt_ptr[i]=NULL;

	fill_hash_nt_table();
	F.no_of_firsts=gram.no_of_nt;
	F.no_of_follows=gram.no_of_nt;
	F.follow[0].follow_list=malloc(sizeof(char*));
	F.follow[0].follow_list[0]=malloc(sizeof(char)*2);
	F.follow[0].follow_list[0][0]='$';
	F.follow[0].follow_list[0][1]=0;
	F.follow[i].d=1;
	F.follow[0].size_follow_list++;
	int it=0;
	F=ComputeFirstAndFollowSets(gram,F,it);
	it++;
	F=ComputeFirstAndFollowSets(gram,F,it);
	F=ComputeFirstAndFollowSets(gram,F,it);
	F=ComputeFirstAndFollowSets(gram,F,it);
	int size=0;
	for(int i=0;i<gram.size;i++)
	{
		RHS* start=gram.start[i].head;
		while(start!=NULL)
		{
			if(start->check==1)
				size=fill_terminal(start->value,size);
			start=start->next;
		}
	}
	printf("hi1");
	size=fill_terminal("$",size);
	printf("hi2");
	no_of_terminals=size;



	hash_t_ptr=malloc(sizeof(hash_t*)*factor_t);
	for(int i=0;i<factor_t;i++)
		hash_t_ptr[i]=NULL;

	fill_hash_t_table();
	fo=&F;
	T.r = gram.no_of_nt;
	T.c = no_of_terminals;
	T = createParseTable(F,  T);
	T = createParseTable(F,  T);
	printf("\n\n*************************** FIRST and FOLLOW SETS AUTOMATED ***************************\n\n");


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
