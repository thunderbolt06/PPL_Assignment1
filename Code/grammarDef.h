/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#ifndef GRAMMARDEF_H_INCLUDED
#define GRAMMARDEF_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <malloc.h>
#include <unistd.h>
#include <signal.h>

extern int line_count;
extern int no_of_terminals;

typedef struct RHS RHS;
struct RHS{
    int check;
    char *value;
    RHS* next;
};


typedef struct LHS{
    char* value;
    int e;
    RHS* head;
}LHS;


typedef struct grammar{
    LHS* start;
    int size;
    int no_of_nt;
}grammar;

#endif // GRAMMARDEF_H_INCLUDED
