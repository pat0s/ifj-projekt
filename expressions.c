#include "expressions_stack.c"
#include "expressions.h"
#include "scanner.c"


int precence_table[TABLE_SIZE][TABLE_SIZE] =
{
//     +,- | *,/,// | .. |   #  |  i   |  RO  |  (   |   )  | string | $  
    { REDUC, SHIFT, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, EMPTY, REDUC },   // +,-
    { REDUC, REDUC, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, EMPTY, REDUC },   // *, /, //
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, SHIFT, REDUC },   // .. 
    { REDUC, REDUC, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, EMPTY, SHIFT, REDUC },   // #
    { REDUC, REDUC, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // i - id, number, int
    { SHIFT, SHIFT, EMPTY, SHIFT, SHIFT, EMPTY, SHIFT, REDUC, EMPTY, REDUC },   // RO - relational operators ( >, <, <=, >=, ==, ~=, )
    { SHIFT, SHIFT, EMPTY, SHIFT, SHIFT, SHIFT, SHIFT, EQUAL, EMPTY, EMPTY },   // (
    { REDUC, REDUC, REDUC, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // )
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // string
    { SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, EMPTY, SHIFT, EMPTY }    // $
};

/**
 * @brief Rozpoznani znaku na vstupu
 * 
 * @returns druhy index precendencni tabulky nebo -1 pri znaku se kterym nepracuje down-top
 */

int vstupni_znak(Token* token){
    if(!strcmp(token->name,"+")||!strcmp(token->name,"-")){
        return 0;
    }
    else if(!strcmp(token->name,"*")||!strcmp(token->name,"/")||!strcmp(token->name,"//")){
        return 1;
    }
    else if(!strcmp(token->name,"..")){
        return 2;
    }
    else if(!strcmp(token->name,"#")){
        return 3;
    }
    else if(!strcmp(token->name,"identifier")||!strcmp(token->name,"number")||!strcmp(token->name,"int")){
        return 4;
    }
    else if(!strcmp(token->name,"<")||!strcmp(token->name,">")||!strcmp(token->name,"<=")||!strcmp(token->name,">=")||!strcmp(token->name,"==")||!strcmp(token->name,"~=")){
        return 5;
    }
    else if(!strcmp(token->name,"(")){
        return 6;
    }
    else if(!strcmp(token->name,")")){
        return 7;
    }
    else if(!strcmp(token->name,"string")){
        return 8;
    }
    else return 9;
}


/**
 * @brief Rozpoznani znaku na zasobniku ke zpracovani
 * 
 * @returns prvni index precendencni tabulky nebo -1 pro chybu;
 */
int zasobnikovy_znak(Stack*s){
    //nacteni znaku z vrholu, jestli na vrcholu E - nacita druhy znak
    char*znak=NULL;
    if(!is_empty(s)){
        znak = top(s);
        if(!strcmp(znak,"E")){
            znak=top1(s);
            if(znak==NULL){
                return 9;
            }
            else if(!strcmp(znak,"E")){
                return -1;
            }
        }
    }
    if(znak==NULL){
        return 9;
    }
    else if(!strcmp(znak,"+")||!strcmp(znak,"-")){
        return 0;
    }
    else if(!strcmp(znak,"*")||!strcmp(znak,"/")||!strcmp(znak,"//")){
        return 1;
    }
    else if(!strcmp(znak,"..")){
        return 2;
    }
    else if(!strcmp(znak,"#")){
        return 3;
    }
    else if(!strcmp(znak,"identifier")||!strcmp(znak,"number")||!strcmp(znak,"int")){
        return 4;
    }
    else if(!strcmp(znak,"<")||!strcmp(znak,">")||!strcmp(znak,"<=")||!strcmp(znak,">=")||!strcmp(znak,"==")||!strcmp(znak,"~=")){
        return 5;
    }
    else if(!strcmp(znak,"(")){
        return 6;
    }
    else if(!strcmp(znak,")")){
        return 7;
    }
    else if(!strcmp(znak,"string")){
        return 8;
    }
    return-1;
}

Token *exp_analysator(Token*token){
    Stack * s=(Stack *)malloc(sizeof(Stack));
    init_stack(s);
    push(s,token->name);

    while(vstupni_znak(token)!=9){
    char*print=top(s);
    printf("Vrchol zasobniku: %s\n",print);
    print=token->name;
    printf("Vstupni znak: %s\n",print);
    int i,j;
    i=zasobnikovy_znak(s);
    j=vstupni_znak(token);
    printf("Index tabulky:(%i, %i) \n",i,j);

    printf("Pravidlo tabulky: %i\n",precence_table[i][j]);
    read_token(token);
    }
    return token;
}

int main(){
    Token *token = malloc(sizeof(Token));
    strcpy(token->name,"identifier");
    token->value="sfd";
    token= exp_analysator(token);
    return 0;
}

/* End of file expressions.c */