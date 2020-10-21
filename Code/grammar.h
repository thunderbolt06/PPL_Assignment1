#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED
int last_occurence(char* s,grammar G);

int first_occurence(char* s,grammar G);

int checkntort(char * ch, char ** strs,grammar G);

void find_nt(grammar G);

void populate_nt(grammar *G);


#endif // GRAMMAR_H_INCLUDED
