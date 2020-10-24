#include <stdio.h>


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

int main(){
    char* s = patternMatch(".5");
    printf(s);
}
