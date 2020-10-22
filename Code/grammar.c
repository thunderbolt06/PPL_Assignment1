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
