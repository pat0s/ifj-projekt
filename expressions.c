/**
 * Project: IFJ21
 * @file expressions.c
 * @author Dovhalenko Dmytro
 * @version 0.1
 * 
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include "expressions.h"
#include <string.h>
#include "error.h"

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
    else if(!strcmp(znak,"identifier")||!strcmp(znak,"number")||!strcmp(znak,"int")||!strcmp(znak,"string")||!strcmp(znak,"nil")){
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
    if(!strcmp(token->name,"keyword")){
        if(!strcmp(token->value,"nil")){
            strcpy(token->name,"nil");
        }
    }
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
void do_shift(Stack*s,Data_t * data,Token*token,int vstup,Tframe_list *frames){
    char *type;
    if(vstup==4){
        if(!strcmp(token->name,"identifier")){
            TNode *node = searchFrames(frames,token->value);
            if(node==NULL){
                //chyba nedefinovana premenna;
                        //while(frames!=NULL){
                           // deleteFirst(frames);
                        //}                  
                        fprintf(stderr, "ERROR - undef var\n");
                        free(token);
                        free(data);
                        exit(UNDEFINED_VAR);
            }
            int idtype = node->var->data_type;
            if(idtype==0){
                type="int"; 
               //printf("idtype = int\n");
            }
            else if(idtype==1){
                type="number"; 
                //printf("idtype = num\n");
            }
            else if(idtype==2){
                type="string";
                //printf("idtype = string\n");
            }
            else {
                type="nil";
                //printf("idtype = nil\n");
            }
        }
        else{
            type=token->name;
            if(!strcmp(token->value,"0")||!strcmp(token->value,"0.0")){
                if (!is_empty(s)){

                    if(!strcmp(top(s),"/")||!strcmp(top(s),"//")){
                        //chyba deleni nulou;
                        //while(frames!=NULL){
                           // deleteFirst(frames);
                        //}                  
                        fprintf(stderr, "ERROR - Deleni 0\n");
                        free(token);
                        free(data);
                        exit(DIVISION_BY_ZERO);
                    }
                }
            }
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
 * @brief Provede kontrolu typu u binarnich operatoru a nastavi typ vysledneho vyrazu;
 * 
 * @returns 0 pri uspechu, -1 pri chybe;
 */
int kontrola_typu(Stack *s){
    char type[7];
    if(!strcmp(top_type(s),"string")){
        pop(s);
        pop(s);
        if(!strcmp(top_type(s),"string")){
            strcpy(type,"string");
            change_top_type(s,type);
            return 0;
        }
        else{
            return -1;
            
        }
    }
    else if(!strcmp(top_type(s),"int")){
        pop(s);
        pop(s);
        if(!strcmp(top_type(s),"int")){
            strcpy(type,"int");
            change_top_type(s,type);
            return 0;
        }
        else if(!strcmp(top_type(s),"number")){
            //zmenit typ posledniho vlozeneho na number
            strcpy(type,"number");
            change_top_type(s,type);
            return 0;
        }
        else{
            return -1;
        }
    }
    else if(!strcmp(top_type(s),"nil")){
        return -1;
    }
    else {
        pop(s);
        pop(s);
        if(!strcmp(top_type(s),"number")){
            strcpy(type,"number");
            change_top_type(s,type);
            return 0;
        }
        else if(!strcmp(top_type(s),"int")){
            //zmenit typ predposledniho na number
            strcpy(type,"number");
            change_top_type(s,type);
            return 0;
        }
        else {
            return -1;
        }
    }
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
    else if(!strcmp(top(s),"nil")){                         //E -> nil
        pop(s);
        push(s,"E","nil");
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
            if(kontrola_typu(s)==0){
            //zavolat generovani +
            }
            else{
                return -1;
            }
            
        }
        else if(!strcmp(top1(s),"-")){                      //E -> E - E
            if(kontrola_typu(s)==0){
            //zavolat generovani -
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"*")){                      //E -> E * E
            if(kontrola_typu(s)==0){
            //zavolat generovani *
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"/")){                      //E -> E / E
            if(kontrola_typu(s)==0){
            //zavolat generovani /
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"//")){                     //E -> E // E
            if(kontrola_typu(s)==0){
            change_top_type(s,"int");
            //zavolat zmenu typu na int
            //zavolat generovani //
                }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"<")){                      //E -> E > E
            if(kontrola_typu(s)==0){
            change_top_type(s,"bool");
            //zavolat generovani >
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),">")){                      //E -> E < E
            if(kontrola_typu(s)==0){
            change_top_type(s,"bool");
            //zavolat generovani <
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"<=")){                     //E -> E <= E
            if(kontrola_typu(s)==0){
            change_top_type(s,"bool");
            //zavolat generovani <=
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),">=")){                     //E -> E >= E
            if(kontrola_typu(s)==0){
            change_top_type(s,"bool");
            //zavolat generovani >=
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"==")){                     //E -> E == E
            if(strcmp(top_type(s),"nil")){
                if(kontrola_typu(s)==-1){
                    if(strcmp(top_type(s),"nil")){
                        return-1;
                    }
                }
            }
            else{
                pop(s);
                pop(s);
            }
            change_top_type(s,"bool");
            //zavolat generovani ==
        }
        else if(!strcmp(top1(s),"~=")){                     //E -> E ~= E
            if(strcmp(top_type(s),"nil")){
                if(kontrola_typu(s)==-1){
                    if(strcmp(top_type(s),"nil")){
                        return-1;
                    }
                }
            }
            else{
                pop(s);
                pop(s);
            }
            change_top_type(s,"bool");
            //zavolat generovani ~=
        }
        else if(!strcmp(top1(s),"..")){                     //E -> E..E
            if(!strcmp(top_type(s),"string")){
                pop(s);
                pop(s);
                if(!strcmp(top_type(s),"string")){
                    change_top_type(s,"string");
                    //zavolat generovani ..
                }
                else {
                    return -1;
                }
            }
            else {
                return -1;
            }
        }
        
    }
    else{
       return -1; //chyba;
    }
return 0;
}

void *exp_analysator(Data_t *data){
    Stack * s=(Stack *)malloc(sizeof(Stack));
    init_stack(s);

    Token *token = data->token;
    Tframe_list *frames= data->list;

//Vymazat
/*
    TNode *rootPtr = NULL;    
    int error_c;
    insert(&rootPtr, createVarNode("a", 0, "32", &error_c));
    insert(&rootPtr, createVarNode("b", 1, "33", &error_c));
    insert(&rootPtr, createVarNode("c", 2, "34", &error_c));
    */
//

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
                do_shift(s,data,token,j,frames);
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
                if(error!=-1){
                   if((i==8 && (j==7||j==8)) ||(i==4&&j==4) ){ 
                    if((i==4&&j==4)) {
                        while(top1(s)!=NULL&&error!=-1){
                            error=do_reduc(s);
                        }
                    } 
                    if(error!=-1){
                        destroy(s);  
                        //data->token = token; 
                        //printf("Return token %s\n",data->token->name);         
                        return 0;
                        }
                    }
                }
                if(precence_table[i][j]==3||error==-1){
                    fprintf(stderr, "ERROR - Chyba syntaktickeho analyzatoru zdola nahoru\n");
                    destroy(s);
                    /*while(frames!=NULL){
                        deleteFirst(frames); 
                        } 
                        */
                    free(token);
                    free(data);
                    exit(INCOMPATIBLE_TYPES);//chyba
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
    destroy(s);
    //printf("Return token %s\n",data->token->name);
    return 0;
}
/*
int main(){
    Token *token = malloc(sizeof(Token));
    strcpy(token->name,"int");
    token->value="sfd";

    
    token= exp_analysator(token);
    free(token);
    return 0;
}*/

/* End of file expressions.c */