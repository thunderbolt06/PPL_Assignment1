/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#ifndef TOKENISESOURCECODE_H_INCLUDED
#define TOKENISESOURCECODE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>



typedef struct tokenStream {
	char* lexeme;
	char* token;

	int line_no;
    struct tokenStream* next;
}tokenStream;


#endif // TOKENISESOURCECODE_H_INCLUDED
