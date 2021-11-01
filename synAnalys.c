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





analysRet fRet_type(Token *token, enum STATE *state);
analysRet fType(Token *token, enum STATE *state);
analysRet fTypes(Token *token, enum STATE *state);
analysRet fPar_type(Token *token, enum STATE *state);
analysRet fProg_con(Token *token, enum STATE *state);
analysRet fExp(Token *token, enum STATE *state);
analysRet synAnalys(Token *token, enum STATE *state);




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




analysRet fRet_type(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    
    if(!strcmp(token->name,":")){
    //TODO treba poriesit EPSILON, zasekol som sa pri <type>-> EPSILON a <types>->EPSILON
       
        //ocakavam <type>
        errorValue = read_token(token);
        checkError(errorValue, token);
        //Zanorenie sa do fType

        returnValue = fType(token, state);
         //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(returnValue.SynCorrect, token);
        
         //ocakavam <types>
        errorValue = read_token(token);
        checkError(errorValue, token);
        
        //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
        returnValue = fTypes(token, state);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(returnValue.SynCorrect, token);
    
    
    }
    else if((!strcmp(token->name,"keyword") && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))) || !strcmp(token->name,"identifier")){
        //Znaci EPSILON prechod od <prog_con>, pravidlo 3., 4. a 5. 
        return returnValue;
    }
    else if(!strcmp(token->name,"-1")){
        //Znaci EPSILON prechod od <prog_con>, pravidlo 2. 
        return returnValue;
    }
    
    return returnValue;
}


analysRet fType(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    if(!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")){
            return returnValue;
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }
}



analysRet fTypes(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;

        if(!strcmp(token->name,")") && *state == par_type){
            //parameter funkcie je prazdny, nie je tam nic 
            //riesim parameter funkcie a momentalne je token v parmetri brany ako EPSILON
            return returnValue;
        }
        else if(!strcmp(token->name,",")){

             //ocakavam <type>
            errorValue = read_token(token);
            checkError(errorValue, token);

            //Zanorenie sa do fType
            returnValue = fType(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);



             //ocakavam <types>
            errorValue = read_token(token);
            checkError(errorValue, token);

            
            //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
            returnValue = fTypes(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
        }
        else if((*state == ret_type && !strcmp(token->name,"keyword")) && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 3. a 4. 
            return returnValue;

        }
        else if(*state == ret_type && !strcmp(token->name,"identifier")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 5. 
            return returnValue;
        }
        else if(*state == ret_type && !strcmp(token->name,"-1")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 2.
            return returnValue;
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    return returnValue;
}



analysRet fPar_type(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    

    printf("name : %s\n", token->name);
    printf("value : %s\n", token->value);

     if(!strcmp(token->name,")")){
            //parameter funkcie je prazdny, nie je tam nic 
            return returnValue;
        }
        else if(!strcmp(token->name,"keyword") && (!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")) ){
            //parameter je jeden z datovych typov

            //ocakavam <types>
            errorValue = read_token(token);
            checkError(errorValue, token);

            //Zanorenie sa do funkcie fTypes, kde budem riesit datove typy
            returnValue = fTypes(token, state);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(returnValue.SynCorrect, token);
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    return returnValue;
}


analysRet fProg_con(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;

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
                        returnValue = fPar_type(token, state);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(returnValue.SynCorrect, token);


                        //Ocakavam <ret-type>
                        errorValue = read_token(token);
                        checkError(errorValue, token);
                        
                        //Zmena stavu
                        *state = ret_type;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
                        returnValue = fRet_type(token, state);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(returnValue.SynCorrect, token);


                        //Ocakavam <prog_con>
                        errorValue = read_token(token);
                        checkError(errorValue, token);
                        
                        //Zmena stavu
                        *state = prog_con;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
                        returnValue = fRet_type(token, state);
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
            //Token je to EOF, znaeci EPSILON
            return returnValue;
        }
        else{
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    return returnValue;
}



analysRet fExp(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;

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


analysRet synAnalys(Token *token, enum STATE *state){
    int errorValue;
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    
    //STRCMP -> ak sa stringy rovnaju, tak je return 0, preto v podmienkach !
    //Inizializovany stav, state->prog
    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"require")){
        //nacitanie dalsieho tokenu
        errorValue = read_token(token);
        checkError(errorValue, token);
            

        //Zmena stavu a nasledne rekurzivne zanorenie
        *state = exp;
        returnValue = fExp(token, state);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(returnValue.SynCorrect, token);
            

        //Natahanie dalsieho tokenu
        errorValue = read_token(token);
        checkError(errorValue, token);

        //Zmena stavu a rekurzovne zanorenie
        *state = prog_con;
        returnValue = fProg_con(token, state);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(returnValue.SynCorrect, token);
    }
    else{
        returnValue.SynCorrect = 2;
        return returnValue;
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
    checkError(returnValue.SynCorrect, token);
    
    
    printf("Syn analys: %d", returnValue.SynCorrect);  


    return 0;
}