#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "scanner.c"
#include "error.h"




enum STATE {assign, assigns, arg, args, exp, item, item_n, init, init_value, prog, prog_con, par_type, ret_val, ret_type, st_list, type, types, value, values, params, params_n};

typedef struct sAnalysRet{
    int  SynCorrect;
    bool isNotError;


} analysRet;


bool precAnalys(){


}



void checkError(int errorValue, Token *token){
    if(errorValue == 1){
        fprintf(stderr, "Lexical analysis Error\n");
        free(token);        
        exit (LEX_ERROR);
    }
    else if(errorValue == 2){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 3){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 4){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 5){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 6){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 7){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 8){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if(errorValue == 9){
        fprintf(stderr, "Syntax Error\n");
        free(token);
        exit(SYNTAX_ERROR);
    }
    else if (errorValue == 99){
        fprintf(stderr, "Internal Error\n");
        free(token);
        exit(INTERNAL_ERROR);
    }

   
}



analysRet synAnalys(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    
    //STRCMP -> ak sa stringy rovnaju, tak je return 0, preto v podmienkach !
    if(*state == prog){
        if(!strcmp(token->name,"keyword") && !strcmp(token->value,"require")){
            //nacitanie dalsieho tokenu
            errorValue = read_token(token);
            checkError(errorValue, token);
            

            //Zmena stavu a nasledne rekurzivne zanorenie
            *state = exp;
            returnValue = synAnalys(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
            

            //Natahanie dalsieho tokenu
            errorValue = read_token(token);
            checkError(errorValue, token);

            //Zmena stavu a rekurzovne zanorenie
            *state = prog_con;
            returnValue = synAnalys(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
        }
        else{
            fprintf(stderr, "Syntax Error\n");
            exit(SYNTAX_ERROR);
        }
    }
    else if(*state == exp){
        //TODO CALL precedencnu analyzu
        //TODO check token in symtable
        
        //if(!isExpression()){
            if(!strcmp(token->name,"string") && !strcmp(token->value,"ifj21")){
                returnValue.SynCorrect = 0;
                return returnValue;
            }
            else{
                returnValue.SynCorrect = 2;
                return returnValue;
            }
        //}

    }
    else if(*state == prog_con){
        if(!strcmp(token->name,"keyword") && !strcmp(token->value,"global")){
              
            //nacitanie ID funkcie
            //TODO pridaj do tabulky symbolov
            errorValue = read_token(token);
            checkError(errorValue, token);
            
            //ocakavanie dvojbodky
            errorValue = read_token(token);
            checkError(errorValue, token);

            if(!strcmp(token->name, ":")){
                //Ocakavam klucove slovo 'function'
                errorValue = read_token(token);
                checkError(errorValue, token);

                if(!strcmp(token->name,"keyword") && !strcmp(token->value,"function")){
                
                    //Ocakavam '('
                    errorValue = read_token(token);
                    checkError(errorValue, token);

                    if(!strcmp(token->name,"(")){
                        
                        //Ocakavam <par-type>
                        errorValue = read_token(token);
                        checkError(errorValue, token);
                        
                        //Zmena stavu
                        *state = par_type;
                        returnValue = synAnalys(token, state);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(returnValue.SynCorrect, token);


                        //Ocakavam <ret-type>
                        errorValue = read_token(token);
                        checkError(errorValue, token);
                        
                        //Zmena stavu
                        *state = par_type;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
                        returnValue = synAnalys(token, state);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(returnValue.SynCorrect, token);

                         
                    }
                    else{
                        returnValue.SynCorrect = 2;
                        return returnValue;
                    }

                }
                else{
                    returnValue.SynCorrect = 2;
                    return returnValue;
                }

            }
            else{
                returnValue.SynCorrect = 2;
                return returnValue;
            }

        }
        else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"local")){



        }
        else if(!strcmp(token->name,"identifier")){


        

        }
        else if(!strcmp(token->name,"-1")){
            //Token je to EOF


        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }

    }
    else if(*state == ret_type){
        //TODO AK JE TOKEN EPSILON
        if(!strcmp(token->name,":")){
        //TODO treba poriesit EPSILON, zasekol som sa pri <type>-> EPSILON a <types>->EPSILON
        }


    }
    else if(*state == par_type){
        if(!strcmp(token->name,")")){
            //parameter funkcie je prazdny, nie je tam nic 
            return returnValue;
        }
        else if(!strcmp(token->name,"string") || !strcmp(token->name,"integer") || !strcmp(token->name,"number")){
            //parameter je jeden z datovych typov


            //ocakavam <types>
            errorValue = read_token(token);
            checkError(errorValue, token);

            //Zmena stavu na types
            *state = types;
            returnValue = synAnalys(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }


    }
    else if(*state == type){
        if(!strcmp(token->name,"string") || !strcmp(token->name,"integer") || !strcmp(token->name,"number")){
            return returnValue;
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }


    }

    else if(*state == types){
        if(!strcmp(token->name,")")){
            //parameter funkcie je prazdny, nie je tam nic 
            return returnValue;
        }
        else if(!strcmp(token->name,",")){

             //ocakavam <type>
            errorValue = read_token(token);
            checkError(errorValue, token);

            *state = type;
            returnValue = synAnalys(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);



             //ocakavam <types>
            errorValue = read_token(token);
            checkError(errorValue, token);

            *state = types;
            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
            returnValue = synAnalys(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }

    }

    return returnValue;
}   




int main(){

    enum STATE *state = malloc(sizeof(enum STATE));
    //Osetrenie chyby mallocu

    *state = prog;

    int errorValue;


    Token *token = malloc(sizeof(Token));
    //TODO osetri malloc error

    errorValue = read_token(token);
    checkError(errorValue, token);


    analysRet returnValue = synAnalys(token, state);

    
    
    printf("Syn analys: %d", returnValue.SynCorrect);  


    return 0;
}