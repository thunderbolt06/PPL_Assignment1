/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#include "grammar.h"

void grammar()
{
	FILE * fp = fopen("Grammar.txt", "r");
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


}
