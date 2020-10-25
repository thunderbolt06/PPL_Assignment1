#include "tokeniseSourcecode.h"

char* getNextToken(FILE *fp,int *line_no){
    char ch = ' ';
    char *token = (char *)malloc(sizeof(char)*50);
    int sz = 0;
    while( !feof(fp) ){

        ch = fgetc(fp);
        if(ch == ' '){
            if(sz == 0)continue;
            else
            break;
        }
        else if(ch == '\n'){
            *line_no = *line_no  + 1;
            break;
        }
        else {
            token[sz++] = ch;
        }

    }   
    token[sz] = '\0';
    return token;
}

char* patternMatch(char* s){
    int len = strlen(s);
    if(len==1){
        if(*s=='=')
            return "ASSIGN";
        else if(*s=='+')
            return "PLUS";
        else if(*s=='-')
            return "MINUS";
        else if(*s=='*')
            return "MULTIPLY";
        else if(*s=='/')
            return "DIVIDE";
        else if(*s=='{')
            return "CURLOPEN";
        else if(*s=='{')
            return "CURLOPEN";
        else if(*s=='}')
            return "CURLCLOSE";
        else if(*s=='[')
            return "SQUOPEN";
        else if(*s==']')
            return "SQUCLOSE";
        else if(*s=='(')
            return "BRAOPEN";
        else if(*s==')')
            return "BRACLOSE";
        else if(*s==';')
            return "SEMICOLON";
        else if(*s==':')
            return "COLON";
        else if(*s=='\0')
            return "NEWLINE";
    }
    if(len==2){
        if(*s=='.' && *(s+1)=='.')return "RANGEOP";
        else if(*s=='o' || *(s+1)=='f')return "OF_KEYWORD";
    }
    if(*s>='0' && *s<='9'){
        int real=0;
        while(*s!='\0'){
            if(*s=='.' && real==0)real=1;
            else if(*s=='.' && real==1)return "ERROR";
            if(!(*s>='0' && *s<='9') && *s!='.')return "ERROR";
            s++;
        }
        if(real)return "RNUM1";
        return "NUM1";
    }
    if( strcmp(s, "|||") == 0)return "OR_KEYWORD";
    if( strcmp(s, "&&&") == 0)return "AND_KEYWORD";
    if( strcmp(s, "declare") == 0)return "DECLARE_KEYWORD";
    if( strcmp(s, "integer") == 0)return "INTEGER_KEYWORD";
    if( strcmp(s, "boolean") == 0)return "BOOLEAN_KEYWORD";
    if( strcmp(s, "size") == 0)return "SIZE_KEYWORD";
    if( strcmp(s, "real") == 0)return "REAL_KEYWORD";
    if( strcmp(s, "list") == 0)return "LIST_KEYWORD";
    if( strcmp(s, "array") == 0)return "ARRAY_KEYWORD";
    if( strcmp(s, "jagged") == 0)return "JAGGED_KEYWORD";
    if( strcmp(s, "values") == 0)return "VALUES_KEYWORD";
    if( strcmp(s, "program") == 0)return "START1_KEYWORD";
    if( strcmp(s, "()") == 0)return "START2_KEYWORD";
    if( strcmp(s, "R1") == 0)return "R1_KEYWORD";
    if( strcmp(s, "variables") == 0)return "VARIABLES_KEYWORD";
    if((*s>='a' && *s<='z') || (*s>='A' && *s<='Z'))return "VARIABLE";
    return "ERROR";
}

void tokeniseSourcecode(  char* file_address,struct  tokenStream  *s){
    FILE *fp = fopen(file_address,"r");
    if(fp == NULL)
    {
        printf("Error!");   
        exit(1);             
    }
    
    int count = 1;

    int *line_no = (int*)malloc(sizeof(int));

    *line_no = 1;

    while(!feof(fp)){
        struct tokenStream* nex = (tokenStream*)malloc(sizeof(tokenStream));
        char* tok;
        do{
            tok = getNextToken(fp,line_no);
        }while(strcmp( tok , "\0") == 0);
        
        char* lex = patternMatch(tok);
        // printf("%s", tok);
        nex->token = tok;
        // printf("tokenising");
        nex->lexeme = lex;
        nex->line_no = *line_no;
        nex->next = NULL;
        s->next = nex;
        s = s->next;
    }

}

void print_token_stream(struct tokenStream *s){
    printf("   %-30s      %-50s %-30s\n", "LINE NUMBER", "LEXEME", "TOKEN NAME");
	for(int i=0; i<=100; i++)
		printf("_");
	printf("\n");

    while(s){
        printf("\t%-30d %-50s %-30s\n", s->line_no, s->lexeme, (int)s->token);
        s = s->next;
    }
}

int main(int argc, char const *argv[])
{
    struct tokenStream s;

    s.token = "START";
    tokeniseSourcecode("sourcecode.txt", &s);
    print_token_stream(s.next);
    return 0;
}
