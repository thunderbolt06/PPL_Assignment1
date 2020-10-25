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


// #define FILEBYTES 100

// typedef union value{
// 	int Int;
// 	double Real;
// }value;

typedef struct tokenStream {
	char* lexeme;
	char* token;
	// value value;
	int line_no;
    struct tokenStream* next;
}tokenStream;


#endif // TOKENISESOURCECODE_H_INCLUDED
