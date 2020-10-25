#include "tokeniseSourcecode.h"

char* getNextToken(FILE *fp,int *line_no){
    char ch = ' ';
    char *token = (char *)malloc(sizeof(char)*50);
    int sz = 0;
    while( !feof(fp) ){

        ch = fgetc(fp);
        if(ch == ' '){
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
    if(len==3){
        if(*s=='|' && *(s+1)=='|' && *(s+2)=='|')return "OR_KEYWORD";
        if(*s=='&' && *(s+1)=='&' && *(s+2)=='&')return "AND_KEYWORD";
    }
    if(len==7){
        if(*(s+0)=='d' && *(s+1)=='e' && *(s+2)=='c' && *(s+3)=='l' && *(s+4)=='a' && *(s+5)=='r' && *(s+6)=='e')return "DECLARE_KEYWORD";
        if(*(s+0)=='i' && *(s+1)=='n' && *(s+2)=='t' && *(s+3)=='e' && *(s+4)=='g' && *(s+5)=='e' && *(s+6)=='r')return "INTEGER_KEYWORD";
        if(*(s+0)=='b' && *(s+1)=='o' && *(s+2)=='o' && *(s+3)=='l' && *(s+4)=='e' && *(s+5)=='a' && *(s+6)=='n')return "BOOLEAN_KEYWORD";
    }
    if(len==4){
        if(*(s+0)=='s' && *(s+1)=='i' && *(s+2)=='z' && *(s+3)=='e')return "SIZE_KEYWORD";
        if(*(s+0)=='r' && *(s+1)=='e' && *(s+2)=='a' && *(s+3)=='l')return "REAL_KEYWORD";
        if(*(s+0)=='l' && *(s+1)=='i' && *(s+2)=='s' && *(s+3)=='t')return "LIST_KEYWORD";
    }
    if(len==5){
        if(*(s+0)=='a' && *(s+1)=='r' && *(s+2)=='r' && *(s+3)=='a' && *(s+4)=='y')return "ARRAY_KEYWORD";
    }
    if(len==6){
        if(*(s+0)=='j' && *(s+1)=='a' && *(s+2)=='g' && *(s+3)=='g' && *(s+4)=='e' && *(s+5)=='d')return "JAGGED_KEYWORD";
        if(*(s+0)=='v' && *(s+1)=='a' && *(s+2)=='l' && *(s+3)=='u' && *(s+4)=='e' && *(s+5)=='s')return "VALUES_KEYWORD";
    }
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
        char* tok = getNextToken(fp,line_no);
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
        printf("\t%-30d %-50s %-30s\n", s->line_no, s->lexeme, s->token);
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
