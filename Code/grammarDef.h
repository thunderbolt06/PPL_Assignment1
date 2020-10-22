#ifndef GRAMMARDEF_H_INCLUDED
#define GRAMMARDEF_H_INCLUDED

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
