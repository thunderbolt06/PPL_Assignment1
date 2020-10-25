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

bool compare_string(char *first, char *second)
{
   while(*first==*second)
   {
      if ( *first == '\0' || *second == '\0' )
         break;

      first++;
      second++;
   }
   if( *first == '\0' && *second == '\0' )
      return true;
   else
      return false;
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

    if(compare_string(s,"variables"))return "VARIABLES_KEYWORD";
    if(compare_string(s,".."))return "RANGEOP";
    if(compare_string(s,"of"))return "OF_KEYWORD";
    if(compare_string(s,"()"))return "OPEN_CLOSE_BRA";
    if(compare_string(s,"|||"))return "OR_KEYWORD";
    if(compare_string(s,"&&&"))return "AND_KEYWORD";
    if(compare_string(s,"declare"))return "DECLARE_KEYWORD";
    if(compare_string(s,"integer"))return "INTEGER_KEYWORD";
    if(compare_string(s,"boolean"))return "BOOLEAN_KEYWORD";
    if(compare_string(s,"list"))return "LIST_KEYWORD";
    if(compare_string(s,"real"))return "REAL_KEYWORD";
    if(compare_string(s,"size"))return "SIZE_KEYWORD";
    if(compare_string(s,"array"))return "ARRAY_KEYWORD";
    if(compare_string(s,"jagged"))return "JAGGED_KEYWORD";
    if(compare_string(s,"values"))return "VALUES_KEYWORD";
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
