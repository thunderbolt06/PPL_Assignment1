/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include "grammarDef.h"
int last_occurence(char* s,grammar G);

int first_occurence(char* s,grammar G);

int checkntort(char * ch, char ** strs,grammar G);

void find_nt(grammar G);

void populate_nt(grammar *G);


#endif // GRAMMAR_H_INCLUDED
