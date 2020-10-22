#include "grammar.h"
int main(int argc, char* argv[])
{
	line_count = 1;
	buf_count = 0;
	//DFA_state = Start;
	//Printst = Initial;
	no_of_terminals = 0;
	factor_nt = 317;
	factor_t = 127;

	//FIRST MESSAGE
	printf("\nLEVEL 4 Compiler: Symbol Table / Type Checking / Semantic Rules Modules Work / Handled Static and Dynamic Arrays in Type Checking and Code Generation\n");

	//ht = initialize_hash_table();
	//ast_ht = ast_initialization();
	parser();
	int incorrect_attempts = 0;
	char filename[30];
	char* correctfile;
	char *asmfile;
	if(argv[2]==NULL || argv[1]==NULL)
		asmfile = "code.asm";
	else
		asmfile = argv[2];
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
		printf("1 -> Printing the token list generated by the Lexer\n");
		printf("2 -> Parsing the input by the Parser and produce Parse Tree\n");
		printf("3 -> Creating the Abstract Syntax Tree\n");
		printf("4 -> Calculating the Compression Percentage\n");
		printf("5 -> Printing the Symbol Table\n");
		printf("6 -> Printing the Activation Record Size (Stack Size) for each Function\n");
		printf("7 -> Listing all the Static and Dynamic Arrays\n");
		printf("8 -> Verifying the Semantic Correctness and Calculating Compile Time\n");
		printf("9 -> Generating the Assembly Code (LINUX Based NASM v2.14.02)\n\n");
		printf("Select an option: ");
		scanf("%d", &option);
		sourceCode = fopen(correctfile, "r");
		if(option==0)
			break;
		menuOptions(option, sourceCode, correctfile, asmfile);
	}while(1);
	fclose(sourceCode);
	printExitMsg();
	return 0;
}
