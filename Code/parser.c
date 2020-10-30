/*
GROUP NUMBER : 50
ID: 2017B4A70541P	Name: Rahil Jain
ID: 2017B5A70615P  Name: Kaustubh Dwivedi
ID: 2017B5A70761P Name: Ayush Kumar
*/
#include "parserDef.h"
#include "lexerDef.h"

//checks if it is terminal or non terminal
int checkntort(char * ch, char ** strs,grammar G)
{
	if(strcmp(ch,"#")==0)
		return -1;
	for(int i = 0; i < G.no_of_nt; i++)
	{
		if(!strcmp(strs[i], ch))
			return 0;
	}
	return 1;
}

//finds non terminal
void find_nt(grammar G)
{
	for(int i=0;i<G.size;i++)
	{
		RHS* head=G.start[i].head;
		while(head!=NULL)
		{
			head->check=checkntort(head->value,nonterminals,G);
			head=head->next;
		}
	}
}

//populates non terminals
void populate_nt(grammar *G)
{
	if(G->size==1)
	{
		nonterminals=realloc(nonterminals,sizeof(char*)*(G->no_of_nt+1));
		nonterminals[G->no_of_nt]=malloc(sizeof(char)*(strlen(G->start[G->size-1].value)+1));
		strcpy(nonterminals[G->no_of_nt],G->start[G->size-1].value);
		G->no_of_nt++;
	}
	else if(strcmp(nonterminals[G->no_of_nt-1],G->start[G->size-1].value)!=0)
	{
		nonterminals=realloc(nonterminals,sizeof(char*)*(G->no_of_nt+1));
		nonterminals[G->no_of_nt]=malloc(sizeof(char)*(strlen(G->start[G->size-1].value)+1));
		strcpy(nonterminals[G->no_of_nt],G->start[G->size-1].value);
		G->no_of_nt++;
	}
}

//calculates hash function
int calculate_hash(char* s,int factor)
{
	int sum=0;
	for(int i=0;i<strlen(s);i++)
		sum += s[i];
	return sum%factor;
}

//fills hash non terminal table
void fill_hash_nt_table()
{
    factor_nt=7;
	for(int i=0;i<gram.no_of_nt;i++)
	{
		int t=calculate_hash(nonterminals[i],factor_nt);
		hash_nt* start = hash_nt_ptr[t];
		if(start==NULL)
		{
			hash_nt_ptr[t]=malloc(sizeof(hash_nt));
			hash_nt_ptr[t]->value=nonterminals[i];
			hash_nt_ptr[t]->index=i;
			hash_nt_ptr[t]->next=NULL;
			continue;
		}
		while(start->next!=NULL)
			start=start->next;

		start->next=malloc(sizeof(hash_nt));
		start->next->value=nonterminals[i];
		start->next->index=i;
		start->next->next=NULL;
		continue;
	}
}

//fills hash terminal table
void fill_hash_t_table()
{
	for(int i=0;i<no_of_terminals;i++)
	{
		int t=calculate_hash(terminals[i],factor_t);
		hash_t* start = hash_t_ptr[t];
		if(start==NULL)
		{
			hash_t_ptr[t]=malloc(sizeof(hash_t));
			hash_t_ptr[t]->value=terminals[i];
			hash_t_ptr[t]->index=i;
			hash_t_ptr[t]->next=NULL;
			continue;
		}
		while(start->next!=NULL)
			start=start->next;

		start->next=malloc(sizeof(hash_t));
		start->next->value=terminals[i];
		start->next->index=i;
		start->next->next=NULL;
		continue;
	}
}

//checks is the pattern is already present
bool already_present(char** arr, char* str,int size)
{
	for(int i=0;i<size;i++)
		if(strcmp(arr[i],str)==0)
			return 1;
	return 0;
}

//checks rank of the non terminal
int rank(char* nt)
{
	int t=calculate_hash(nt,factor_nt);
	hash_nt* start=hash_nt_ptr[t];
	while(start!=NULL )
	{
		if(strcmp(start->value,nt)==0)
			return start->index;
		start=start->next;
	}
	return -1;
}

//checks rank of the terminal
int terminal_rank(char* s)
{
	int t=calculate_hash(s,factor_t);
	hash_t* start=hash_t_ptr[t];
	while(start!=NULL)
	{
		if(strcmp(start->value,s)==0)
			return start->index;
		start=start->next;
	}
	return -1;
}

//fills out the terminal
int fill_terminal(char* s,int size)
{
	if(already_present(terminals,s,size))
		return size;
	terminals=realloc(terminals,sizeof(char*)*(size+1));
	terminals[size]=malloc(strlen(s)+1);
	strcpy(terminals[size],s);
	size++;
	return size;
}

//prints parse tree by taking the root node
void printParseTree(node* n)
{
    if(n==NULL)
		return;
    if(n->numofchild!=0)
    	printParseTree(n->children[0]);
	if(n->check == 1 && n->lex != NULL)
	{
		if(strcmp(n->lex->TOKEN , "NUM")==0)
			printf("  %-30s %-20d %-20s %-20d %-40s %-20s %-30s \n" , n->lex->lexeme , n->lex->Line_No , n->lex->TOKEN , n->lex->Value.val , n->parent->value , "YES" , "----" );

		else
			printf("  %-30s %-20d %-20s %-20s %-40s %-20s %-30s \n" , n->lex->lexeme , n->lex->Line_No , n->lex->TOKEN , "----" , n->parent->value , "YES" , "----");
	}
	else if(n->check == 0)
		printf("  %-30s %-20s %-20s %-20s %-40s %-20s %-30s \n" , "----" , "----" , "----" , "----", n->parent==NULL?"ROOT":n->parent->value , "NO", n->value );

    	for(int i = 1 ; i < n->numofchild; i++)
        	printParseTree(n->children[i]);
	return;
}


