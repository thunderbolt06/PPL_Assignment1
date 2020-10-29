#ifndef _LEXERDEF_H
#define _LEXERDEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>


#define FILEBYTES 100
#define table_size 53

#define RED "\x1b[1;31m"
#define YELLOW "\x1b[1;33m"
#define MAGENTA "\x1b[1;35m"
#define GREEN "\x1b[1;32m"
#define RESET "\x1b[0m"
#define CYAN "\x1b[1;36m"
#define BLUE "\x1b[1;34m"
#define LINE "\033[1m\033[34m"


int line_count;
int buf_count;
int DFA_state;
int Printst;
int factor_nt;
int factor_t;
int no_of_terminals;
int SynxErr;
int LexErr;
int SemErr;

FILE* sourceCode;


enum state{Error, Start, Alpha1, Alpha2, Num1, Num2, RNum1, RangRet, RNum2, RNum3, RNum4, RNum5, RNum6, RNum7, RNum8, C1, C2, C3, C4, Mul, Les1, Les2, Les3, Les4, Les5, Les6, Grt1, Grt2, Grt3, Grt4, Grt5, Grt6, Col1, Col2, Col3, Ran1, Ran2, Plus, Minus, Divide, Semcol, Equal1, Equal2, NotEqual1, NotEqual2, Com, SqbO, SqbC, BracO, BracC, ROP, Start2, End2} States;

enum printstate{Initial, Com1, Com2, Com3} PrintState;

char* buffer1;
char* buffer2;
char* free_ptr[10];

struct keywords{
	char* pattern;
	char* token;
	struct keywords* next;
};

struct h_table{
	int size;
	struct keywords* arr[table_size];
};

struct h_table* ht;

typedef union value{
	int val;
	double real_val;
}value;

typedef struct Lexeme {
	char* lexeme;
	char* TOKEN;
    value Value;
	struct Lexeme* next;
	int Line_No;
}Lexeme;


#endif
