#include "expressions_stack.c"
#include "expressions.h"
#include "scanner.c"


int precence_table[TABLE_SIZE][TABLE_SIZE] =
{
//     +,- | *,/,// | .. |   #  |  i   |  RO  |  (   |   )  | $  
    { REDUC, SHIFT, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, REDUC },   // +,-
    { REDUC, REDUC, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, REDUC },   // *, /, //
    { EMPTY, EMPTY, SHIFT, EMPTY, SHIFT, REDUC, SHIFT, REDUC, REDUC },   // .. 
    { REDUC, REDUC, EMPTY, EMPTY, SHIFT, REDUC, SHIFT, REDUC, REDUC },   // #
    { REDUC, REDUC, REDUC, EMPTY, EMPTY, REDUC, EMPTY, REDUC, REDUC },   // i - id, number, int, string
    { SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, EMPTY, SHIFT, REDUC, REDUC },   // RO - relational operators ( >, <, <=, >=, ==, ~=, )
    { SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, EQUAL, EMPTY },   // (
    { REDUC, REDUC, REDUC, EMPTY, EMPTY, REDUC, EMPTY, REDUC, REDUC },   // )
    { SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, EMPTY, EMPTY }    // $
};

int rozpoznani_znaku(char*znak){
    if(!strcmp(znak,"+")||!strcmp(znak,"-")){
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
    else if(!strcmp(znak,"identifier")||!strcmp(znak,"number")||!strcmp(znak,"int")||!strcmp(znak,"string")){
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
    else{
        return 8;
    }
}

/**
 * @brief Rozpoznani znaku na vstupu
 * 
 * @returns druhy index precendencni tabulky nebo -1 pri znaku se kterym nepracuje down-top
 */

int vstupni_znak(Token* token){
    char*znak=token->name;
    int table_column = rozpoznani_znaku(znak);
    return table_column;
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
                return 8;
            }
            else if(!strcmp(znak,"E")){
                return -1;
            }
        }
    }
    if(znak==NULL){
        return 8;
    }
    else {
        int table_row=rozpoznani_znaku(znak);
        return table_row;
    }
    return-1;
}


/**
 * @brief Ulozi na zasobnik token ze vstupu
 * 
 * 
 */
void do_shift(Stack*s,Token*token,int vstup){
    char *type;
    if(vstup==4){
        if(!strcmp(token->name,"identifier")){
            type="int"; //volani ts
        }
        else{
            type=token->name;
        }
    }
    else{
       type="op"; 
    }
    push(s,token->name,type);
}

/**
 * @brief provede zmenu zasobniku podle pravidla E->(E);
 * 
 * 
 */
void do_equal(Stack*s){
    if(!strcmp(top(s),"E")&&!strcmp(top1(s),"(")){
        char type[7];
        strcpy(type,top_type(s));
        pop(s);
        pop(s);
        push(s,"E",type);
    }
    else return;
}



/**
 * @brief Provede zmenu zasobniku podle pravidel
 * 
 * @returns 0 pri uspechu, -1 pri chybe;
 */
int do_reduc(Stack*s){
    if(!strcmp(top(s),"string")){                           //E -> string
        pop(s);
        push(s,"E","string");
    }
    else if(!strcmp(top(s),"int")){                         //E -> int
        pop(s);
        push(s,"E","int");
    }
    else if(!strcmp(top(s),"number")){                      //E -> number
        pop(s);
        push(s,"E","number");
    }
    else if(!strcmp(top(s),"identifier")){                  //E -> id
        char type[7];
        strcpy(type,top_type(s));
        pop(s);
        push(s,"E",type);
    }
    else if(!strcmp(top(s),"E")){                           //E -> #E
        if(!strcmp(top1(s),"#")){
            if(!strcmp(top_type(s),"string")){      //semanticka kontrola
                pop(s);
                pop(s);
                push(s,"E","int");
            }
            else{
                return -1;                         //semanticka chyba
            }
        }
        else if(!strcmp(top1(s),"+")){                      //E -> E + E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"-")){                      //E -> E - E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"*")){                      //E -> E * E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"/")){                      //E -> E / E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"//")){                     //E -> E // E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"<")){                      //E -> E > E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),">")){                      //E -> E < E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"<=")){                     //E -> E <= E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),">=")){                     //E -> E >= E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"==")){                     //E -> E == E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"~=")){                     //E -> E ~= E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        else if(!strcmp(top1(s),"..")){                     //E -> E..E
            pop(s);
            pop(s);
            if(!strcmp(top(s),"E")){
                //zmenit typ
            }
        }
        
    }
    else{
       return -1; //chyba;
    }
return 0;
}

Token *exp_analysator(Token*token){
    Stack * s=(Stack *)malloc(sizeof(Stack));
    init_stack(s);
    //push(s,token->name,"int");
    int error=0;
    int i,j;
    i=zasobnikovy_znak(s);
    j=vstupni_znak(token);
    while(i!=8 || j!=8){

//Vypis stavu zasobniku pro debug
/*
    char*print=top(s);
    char*print2=top1(s);
    printf("Vrchol zasobniku: %s%s\n",print2,print);
    print=token->name;
    printf("Vstupni znak: %s\n",print);
*/
    i=zasobnikovy_znak(s);
    j=vstupni_znak(token);
/*
    printf("Index tabulky:(%i, %i) \n",i,j);
    printf("Pravidlo tabulky: %i\n",precence_table[i][j]);
*/
///////////////////////////////////////////////////////////////    
    
        if(precence_table[i][j]==0&&error!=-1){         //SHIFT
                do_shift(s,token,j);
                read_token(token);
            }                                           
        else if(precence_table[i][j]==1&&error!=-1){    //EQUAL
                do_equal(s);
                read_token(token);
            }                                           
        else if(precence_table[i][j]==2&&error!=-1){    //REDUCE
                error = do_reduc(s);
            }                                           
        else if(precence_table[i][j]==3||error==-1){    //Prazdny zasobnik a vstup je prazdny nebo ')'
                if(i==8 && (j==7||j==8)){               
                    return token;
                }
                else{                                  //EMPTY
                    printf("Chyba syntaktickeho analyzatoru zdola nahoru\n");
                    break;//chyba
                }
            }                                           
//Vypis stavu zasobniku po provedeni operace
/*    
    print=top(s);
    print2=top1(s);
    printf("Vrchol zasobniku: %s%s\n",print2,print);
    print=top_type(s);
    printf("Type: %s\n\n",print);
*/
///////////////////////////////////////////////////////////
    }
    return token;
}

int main(){
    Token *token = malloc(sizeof(Token));
    strcpy(token->name,"int");
    token->value="sfd";
    token= exp_analysator(token);
    return 0;
}

/* End of file expressions.c */