
//TODO pridaj do fexp podmienku pre vsetky znaky ako su napriklad #, .., ()


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "synAnalys.h"
#include "error.h"

#include "symtable.h"





/**
 * @brief Function for checking errors
 * 
 * @param data Pointer to data structure with errorValue which trigger error message
 */

void checkError(Data_t *data){

        if(data->errorValue == 1){
            fprintf(stderr, "Lexical analysis Error\n");
            free(data->token);
            free(data);
            exit(1);

        }
        else if(data->errorValue == 2){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(2);

        }
        else if(data->errorValue == 3){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(3);

        }
        else if(data->errorValue == 4){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(4);

        }
        else if(data->errorValue == 5){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(5);

        }
        else if(data->errorValue == 6){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(6);

        }
        else if(data->errorValue == 7){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(7);

        }
        else if(data->errorValue == 8){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(8);

        }
        else if(data->errorValue == 9){
            fprintf(stderr, "Syntax Error\n");
            free(data->token);
            free(data);
            exit(9);

        }
        else if (data->errorValue == 99){
            fprintf(stderr, "Internal Error\n");
            free(data->token);
            free(data);
            exit(99);

        }else
            data->errorValue = 0;
}



/**
 * @brief Create a Inbuild Functions object
 * 
 * @param data 
 * @return int 
 */

int createInbuildFunctions(Data_t *data){
    Function_t funkcia;
        //pridavanie funkcie write() do tabulky symbolov
    funkcia.ID = malloc(sizeof(char)*11);
    if(funkcia.ID == NULL)
        return INTERNAL_ERROR;
    memset(funkcia.ID, '\0', 11);
    funkcia.ID = "write";    
    funkcia.param_types = NULL;
    funkcia.param_length = 0;
    funkcia.ret_types = NULL;
    funkcia.ret_length = 0;
    TNode *newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);

        //pridanie funkcie tointeger(n: number): integer
    funkcia.ID = "tointeger";
    funkcia.param_types = malloc(sizeof(int));
    if(funkcia.param_types == NULL)
        return INTERNAL_ERROR;
    funkcia.param_types[0] = 1;
    funkcia.param_length = 1;
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 0;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);
    
        //pridanie funkcie substr(s:string, i:number, : number): string
    funkcia.ID = "substr";
    free(funkcia.param_types);
    funkcia.param_types = malloc(sizeof(int)*3);
    if(funkcia.param_types == NULL)
        return INTERNAL_ERROR;
    funkcia.param_types[0] = 2;
    funkcia.param_types[1] = 1;
    funkcia.param_types[2] = 1;
    funkcia.param_length = 3;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 2;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);


        //pridanie funkcie ord(s: string, i: integer): integer
    funkcia.ID = "ord";
    free(funkcia.param_types);
    funkcia.param_types = malloc(sizeof(int)*2);
    if(funkcia.param_types == NULL)
        return INTERNAL_ERROR;
    funkcia.param_types[0] = 2;
    funkcia.param_types[1] = 0;
    funkcia.param_length = 2;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 0;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);

        //pridanie funkcie chr(i: integer): string
    funkcia.ID = "chr";
    free(funkcia.param_types);
    funkcia.param_types = malloc(sizeof(int));
    if(funkcia.param_types == NULL)
        return INTERNAL_ERROR;
    funkcia.param_types[0] = 0;
    funkcia.param_length = 1;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 2;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);
    

        //pridanie funkcie reads():string
    funkcia.ID = "reads";
    free(funkcia.param_types);
    funkcia.param_types = NULL;
    funkcia.param_length = 0;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 2;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);

        //pridanie funkcie readi():integer
    funkcia.ID = "readi";
    free(funkcia.param_types);
    funkcia.param_types = NULL;
    funkcia.param_length = 0;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 0;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);


        //pridanie funkcie readn():number
    funkcia.ID = "readn";
    free(funkcia.param_types);
    funkcia.param_types = NULL;
    funkcia.param_length = 0;
    free(funkcia.ret_types);
    funkcia.ret_types = malloc(sizeof(int));
    if(funkcia.ret_types == NULL)
        return INTERNAL_ERROR;
    funkcia.ret_types[0] = 1;
    funkcia.ret_length = 1;
    newLeaf = createFuncNode(funkcia.ID, true, funkcia.param_types, funkcia.param_length, funkcia.ret_types, funkcia.ret_length, &(data->errorValue));
    insert(&(data->list->first->rootPtr), newLeaf);

    return 0;
}


/**
 * @brief Function for nondeterminal Values in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fValues(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,",")){
    
        data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){
            if(!strcmp(token->name,"identifier") && isFunction(NULL, token->value)){
                printf("Error in state %d, fValues, Function instead of variable\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory pojdem analyzovat

            fValues(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

        }
        else{
            printf("Error in state %d, fValues, missing expression after \',\'\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else{
        //EPSILON PRECHOD
        //Sybmolicky else
    }

}



/**
 * @brief Function for nondeterminal Value in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fValue(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(") ){
        if(!strcmp(token->name,"identifier")){
            if(isFunction(NULL, token->value)){
                    //je to ID funkcie
                    //TODO treba zistit zo symtable, ci je funkcia aspon deklarovana

                    //Nacitanie '('
                data->errorValue = read_token(token);
                checkError(data);

                if(strcmp(token->name,"(")){
                    printf("Error in state %d, fValue, missing \'(\'\n", *state);
                    data->errorValue = 2;
                    checkError(data);
                }

                    //Nacitanie argumentu funkcie
                data->errorValue = read_token(token);
                checkError(data);

                fArg(token, state, data);
                checkError(data);

                    //Nacitanie dalsieho tokenu, ocakavam <st-list>
                data->errorValue = read_token(token);
                checkError(data);
            }
            else{
                    //Token je ID premennej
                    //TODO treba zistit zo symtable, ci je ID premenna inicializovana
                    //je to ID premennej, idem do <exp> fExp
                fExp(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
                    //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory idem teraz analyzovat

                fValues(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);

            }
        }
        else{
                //Token je string, number lebo int
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory idem teraz analyzovat

            fValues(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

        }
    }
    else{
        //ELSE je tu len symbolicky pre pochopenie situacie s EPLISON prechodom
        //Som v EPSILON prechode a returnujem NIL
        //TODO treba zabezpecit navratovu hodnotu NIL
    }
}


/**
 * @brief Function for nondeterminal Init_value in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fInit_value(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"identifier")){
        if(isFunction(NULL, token->value)){
                //je to ID funkcie
                //TODO treba zistit zo symtable, ci je funkcia aspon deklarovana

                //Nacitanie '('
            data->errorValue = read_token(token);
            checkError(data);

            if(strcmp(token->name,"(")){
                printf("Error in state %d, fInit_value, missing \'(\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

                //Nacitanie argumentu funkcie
            data->errorValue = read_token(token);
            checkError(data);

            fArg(token, state, data);
            checkError(data);

                //Nacitanie dalsieho tokenu, ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);
        }
        else{
                //TODO treba zistit zo symtable, ci je ID premenna inicializovana
                //je to ID premennej, idem do <exp> fExp
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati <st-list>
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            //Pocitam s tym, ze mi precedencna analyza v tokene vrati <st-list>
    }
    else{
        printf("Error in state %d, fInit_value\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}



/**
 * @brief Function for nondeterminal Init in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fInit(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,"=")){
            //nacitam dalsi token, ocakavam <init-value>
        data->errorValue = read_token(token);
        checkError(data);

        fInit_value(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //WARNING -> postaraj sa o to, aby bol v tokene nacitany <st-list>, pri vynoreni s tym pocitas
            //          - Pre string, int a number je to ZABEZPECENE
            //          - Pre ID premennej je to ZABEZPECENE
            //          - Pre ID funkcie je to ZABEZPECENE
    }
    else{
        //Znaci EPSILON PRECHOD
        //Tento 'else' je tu len symbolicky pre spravne porozumenie situacie
    }
}



/**
 * @brief Function for nondeterminal Assigns in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fAssigns(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,",")){
            //nacitam dalsi token, ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);

            //TODO treba zistit ci je to identifikator funkcie alebo premennej
            //Ak je ID funkcie, tak problem, lebo je vo viacnasobnom priradeni ID funkcia, ktora vracia hodnotu
            //Ak je ID premennej, idem do funkcie <exp>
            //Ak je to int, number alebo string, volame <exp>

            //Osetrenie, ci je token int, number, string alebo ID
        if(!strcmp(token->name,"identifier")){
                //Osetrenie, aby ID bolo ID premennej a nie funkcie
            if(isFunction(NULL, token->value)){
                printf("Error in state %d, fAssigns, ID of function in <assigns>\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){
            //Naschval prazdne, pre jednoduchost tu nechavam tuto podmienku


        }
        else{
            printf("Error in state %d, fAssigns,unexpected token type\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

        fExp(token, state, data);
        checkError(data);


            //Nebude treba nacitavat token, lebo v precedencnej analyze bude musiet nacitat dalsi token, aby vedel ze ukonicl vyraz.
            // Bud nacita ',' a pokracujem, alebo nacita EPSILON PRECHOD a koncim

            //Vzdy sa rekurzivne zanorim do fAssigns(), ak bude EPSILON prechod, tak sa vynori, ak bude ',' tak riesim dalsie priradenie
        fAssigns(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        //EPSILON PRECHOD
        //Tato funkcia je tu len pre spravne porozumenie
        //Riesi EPLISON prechod
        //TO, ci je v tokene <st-list> osetri az samotna funkcia fSt_list(), v ktorej sa momentalne vynorim, raz sa rekurzivne zanorim a skontrolujem ci je token <st-list> alebo nie
        //Error sa osetri vo funkcii fSt_list()
    }
}


/**
 * @brief Function for nondeterminal Assign in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fAssign(Token *token, enum STATE *state, Data_t *data){
        //Ocakavam bud ID funkcie alebo <exp>(<exp> moze byt aj nazov premennej, treba zistit v symtable)
        //TODO zistit v symtable

    if(!strcmp(token->name,"identifier")){
            //TODO treba zistit ci je to identifikator funkcie alebo premennej, ak funkcie tak riesim (<arg>), ak premennej tak idem to <exp>
        if(isFunction(NULL, token->value)){
                //TODO Zistit v symtable, ci je deklarovana, ak nie tak ERROR
                //Nacitanie '('
            data->errorValue = read_token(token);
            checkError(data);

            if(strcmp(token->name,"(")){
                printf("Error in state %d, fAssign, missing \'(\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

                //Nacitanie argumentu funkcie
            data->errorValue = read_token(token);
            checkError(data);

            fArg(token, state, data);
            checkError(data);
                //Netreba nacitat dalsi token, ked sa vynorim, a bude posledny token ')', tak sa nacita novy token
        }
        else{
                // ide o ID premennej
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //nemusim nacitavat dalsi token, lebo mi to precedencna analyza vrati v ukazatali a premennej 'token'
                //precedencna analyza sa musi zastavit v momente, kedy narazi na ',' alebo EPSILON PRECHOD, v tomto pripade <st-list>
                //Az vo funkcii fAssings() zistim, ci sa jednalo o EPSILON prechod alebo o ',' a teda dalsie hodnoty do priradenia
            fAssigns(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){

        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //nemusim nacitavat dalsi token, lebo mi to precedencna analyza vrati v ukazatali a premennej 'token'
            //precedencna analyza sa musi zastavit v momente, kedy narazi na ',' alebo EPSILON PRECHOD, v tomto pripade <st-list>
            //Az vo funkcii fAssings() zistim, ci sa jednalo o EPSILON prechod alebo o ',' a teda dalsie hodnoty do priradenia
        fAssigns(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, fAssign\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}



/**
 * @brief Function for nondeterminal Item_n in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fItem_n(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,",")){
            //Ocakavam ID premennej
        data->errorValue = read_token(token);
        checkError(data);

            //Musim sa spytat, ci je TOKEN ID, pretoze budem cez funkciu isFunction(NULL, token->value) zistovat v symtable, ci je to ID funkcie alebo premennej a mohol by nastat problem
        if(!strcmp(token->name,"identifier")){
            if(!isFunction(NULL, token->value)){
                    //ocakavam ',' alebo '=' a teda prechod od <item-n>
                data->errorValue = read_token(token);
                checkError(data);
    
                fItem_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
            }
            else{
                printf("Error in state %d, fItem_n, function instead of ID of variable\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            printf("Error in state %d, fItem_n, expect ID but token is not ID\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"=")){

            //Ocakavam <assign>
        data->errorValue = read_token(token);
        checkError(data);


        fAssign(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, fItem_n\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}




/**
 * @brief Function for nondeterminal Item in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fItem(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"(")){
            //Ide argumnet funkcie, dany identifikator by mal patrit funkcii

            //TODO treba skontrolovat, ci je funkcia aspon deklarovana
        
            //Ocakavam token argumentu
        data->errorValue = read_token(token);
        checkError(data);

        fArg(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Som v stave, kedy mam nacitanu ')' argumentu a musim prejst do <st-list>
        data->errorValue = read_token(token);
        checkError(data);
            //Teraz som nacital dalsi token, v ktorom ocakavam <st-list>, spravil som to preto tu, pretoze musim pocitat situaciu spojenu s pravidlo 16. kde priradzujem a musim rozpoznat EPSILON prechod
    }
    else if(!strcmp(token->name,"=")){
            //Prikaz priradenia, dany identifikator by mal byt premenna

            //Ocakavam bud ID funkcie alebo <exp>(<exp> moze byt aj nazov premennej, treba zistit v symtable)
            //TODO zistit v symtable
        data->errorValue = read_token(token);
        checkError(data);

        fAssign(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Token so <st-list> som nacital vo fAssign()
    }
    else if(!strcmp(token->name,",")){
            //prikaz priradenia, viacnasobne priradenie

            //ocakavam ID premennej
        data->errorValue = read_token(token);
        checkError(data);

            //Musim sa spytat, ci je TOKEN ID, pretoze budem cez funkciu isFunction(NULL, token->value) zistovat v symtable, ci je to ID funkcie alebo premennej a mohol by nastat problem
        if(!strcmp(token->name,"identifier")){
            if(!isFunction(NULL, token->value)){

                    //ocakavam ',' alebo '=' a teda prechod od <item-n>
                data->errorValue = read_token(token);
                checkError(data);

                fItem_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
            }
            else{
                printf("Error in state %d, fItem_n, function instead of ID of variable\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            printf("Error in state %d, fItem_n, expect ID but token is not ID\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else{
        printf("Error in state %d, fItem\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}

/**
 * @brief Function for nondeterminal st-list in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */


void fSt_list(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
            //Narazil som na EPSILON prechod
        
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"if")){

            //Ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);
        
            //Ak je nacitany token identifikator a je to ID funkcie, tak Error
        if(!strcmp(token->name,"identifier")){
            if(isFunction(NULL, token->value)){
                printf("Error in state %d, fSt_list, ID of function in if statement as a condition\n", *state);
                data->errorValue = 2;
                checkError(data);
            }    
        }

            //precedencna analyza by sa mala zastavit po nacitany klucoveho slova 'then', netreba to teda potom nacitavat
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Nemusim nacitavat dalsi token, lebo precedencna analyza nacita do premennje token klucove slovo 'then'
        if(!strcmp(token->name,"keyword") && !strcmp(token->value,"then")){
            
                //TODO zmena framu v symtable, tabulke symbolov

                //Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);

            fSt_list(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //Teraz by sa v tokene mal nachadza 'else', otestujem to a pokracujem v behu
            if(!strcmp(token->name,"keyword") && !strcmp(token->value,"else")){
                    //Ocakavam <st-list>
                data->errorValue = read_token(token);
                checkError(data);

                fSt_list(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);    

                    //v Tokene by sa mal nachadza 'end', idem to otestovat a pokracujem v behu programu uz mimo if statement
                if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
                        //nacitam dalsi token a idem do stavu <st-list>, pokracujem v behu pogramu uz mimo if statement

                        //Ocakavam <st-list>
                    data->errorValue = read_token(token);
                    checkError(data);


                    fSt_list(token, state, data);
                        //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                    checkError(data);
                }
                else{
                    printf("Error in state %d, fSt_list, missing keyword \'end\'\n", *state);
                    data->errorValue = 2;
                    checkError(data);
                }
            }
            else{
                printf("Error in state %d, fSt_list, missing od keyword \'else\' in if statement \n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            printf("Error in state %d, fSt_list, missing od keyword \'then\' in if statement \n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"while")){
        
            //Ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);
        
            //Ak je nacitany token identifikator a je to ID funkcie, tak Error
        if(!strcmp(token->name,"identifier")){
            if(isFunction(NULL, token->value)){
                printf("Error in state %d, fSt_list, ID of function in while cycle as a condition\n", *state);
                data->errorValue = 2;
                checkError(data);
            }    
        }

            //precedencna analyza nacitava dovtedy, kym nenarazi na klucove slovo 'do'
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Nemusim nacitavat dalsi token, lebo v tokene bude nacitane klucove slovo 'do', pretoze sa na tomto tokene precedencna analyza zastavi
            //Prestane nacitavat vyraz a spracuje ho

        if(!strcmp(token->name,"keyword") && !strcmp(token->value,"do")){

                //Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);


            fSt_list(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //Teraz by som mal mat v tokene slovo 'end', spytam sa, ci tam je
            if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
                //nacitam dalsi token a idem do stavu <st-list>, pokracujem v behu pogramu uz mimo while cyklu

                    //Ocakavam <st-list>
                data->errorValue = read_token(token);
                checkError(data);

                fSt_list(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
            }
            else{
                printf("Error in state %d, fSt_list, missing keyword \'end\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            printf("Error in state %d, fSt_list, missing keyword \'do\'\n", *state);
                data->errorValue = 2;
                checkError(data);
        }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"local")){

            //Ocakavam ID
        data->errorValue = read_token(token);
        checkError(data);

            //test, ci je dany token ID, ak nie tak ERROR
        if(strcmp(token->name,"identifier")){
            printf("Error in state %d, fSt_list->local, missing ID of variable\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

            //TODO zistit ci sa dane ID vyskytuje v tomto frame v symtable, ak ano tak error, ak nie tak treba nasledne vlozit do symtable tuto premennu

            //Ocakavam ':'
        data->errorValue = read_token(token);
        checkError(data);

            //Ak chyba ':' tak ERROR inak pokracujeme
        if(strcmp(token->name,":")){
            printf("Error in state %d, fSt_list->local, missing \':\'\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

            //Ocakavam <type>
        data->errorValue = read_token(token);
        checkError(data);

        fType(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);


            //Ocakavam <init>
        data->errorValue = read_token(token);
        checkError(data);

        fInit(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //v tokene sa nachadza <st-list>,treba sa rekurzivne zanorit do fSt-list a skontrolovat nacitany token
            //Nacitanie som spravil v fInit() v epsilon prechode alebo vo <init-value>

        *state = st_list;
        fSt_list(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"return")){
            //Ocakavam <ret-val> a rovno <value>
        data->errorValue = read_token(token);
        checkError(data);


        fValue(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        
            //V EPSILON prechode mam rovno nacitany dalsi token
    }
    else if(!strcmp(token->name,"identifier")){

            //Ocakavam <item>
        data->errorValue = read_token(token);
        checkError(data);

        fItem(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Ak som mal ID funkcie, tak v tokene je ')', musim  teda nacitat za tejto podmienky dalsi token a prejst do <st-list>
        if(!strcmp(token->name,")")){
                //Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);
        }

            //v tokene sa nachadza <st-list>,treba sa rekurzivne zanorit do fSt-list a skontrolovat nacitany token
            //Token som nacital preto dopredu, lebo pri pravidle 16. musim rozpoznat EPSILON prechod a to tak, ze tam nacitam token, vynorim sa az sem a v 
            //dalsom zanoreni skontrolujem ci je tancitany token <st-list>
        fSt_list(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, fSt_list\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}



/**
 * @brief Function for nondeterminal Params-n in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fParams_n(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod


    }
    else if(!strcmp(token->name,",")){
            //Ocakavam ID
        data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,"identifier")){
            if(searchFrames(data->list, token->value) != NULL){
                data->errorValue = 3;
                checkError(data);
            }

            //search ci sa nenachadza v symtable
            char pole[] = "";
            TNode *variable = createVarNode(token->value, 0, pole, &(data->errorValue));
            checkError(data);

            //Ocakavam ':'
            data->errorValue = read_token(token);
            checkError(data);


            //Vlozenie ID do symtable

            if(!strcmp(token->name,":")){
                    //ocakavam argument <type>
                data->errorValue = read_token(token);
                checkError(data);

                fType(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
                   //predanie datoveho typu z fType
                variable->var->data_type = data->premenna->dataType;
                data->funkcia->param_types[data->funkcia->param_length] = data->premenna->dataType;
                data->funkcia->param_length++;

                //printf("datovy typ: %d\n", variable->var->data_type);

                    //Vlozenie do symtable
                insert(&(data->list->first->rootPtr), variable);
                free(variable);



                    //ocakavam argument <params_n>
                data->errorValue = read_token(token);
                checkError(data);


                fParams_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);            
            }
            else{
                printf("Error in state %d, fParams_n\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            printf("Error in state %d, fParams_n\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else {
        printf("Error in state %d, fParams_n\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}



/**
 * @brief Function for nondeterminal Params in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fParams(Token *token, enum STATE *state, Data_t *data){    

    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        data->funkcia->param_types = NULL;
        data->funkcia->param_length = 0;


    }
    else if(!strcmp(token->name,"identifier")){
        
        //Netreba hladat ID v symtable, lebo je novy frame a je to parameter funkcie
        //Create Tnode kde ulozim ID premennej
        char pole[]="";
        
        data->premenna = malloc(sizeof(Variable_t));
        if(data->premenna == NULL){
            data->errorValue = 99;
            checkError(data);
        }

        TNode *variable = createVarNode(token->value, 0, pole, &(data->errorValue));
        checkError(data);

        data->funkcia->param_types = malloc(sizeof(int)*15);
        if(data->funkcia->param_types == NULL){
            data->errorValue = 99;
            checkError(data);
        }
        data->funkcia->param_length = 0;
        

            //ocakavam argument ':'
        data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,":")){
                //ocakavam argument <type>
            data->errorValue = read_token(token);
            checkError(data);

                //nejako nacitat data type do *variable

            fType(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //predanie datoveho typu z fType
            variable->var->data_type = data->premenna->dataType;
            data->funkcia->param_types[data->funkcia->param_length] = data->premenna->dataType;
            data->funkcia->param_length++;


                //Vlozenie do symtable
            insert(&(data->list->first->rootPtr), variable);
            free(variable);


                //ocakavam argument <params_n>
            data->errorValue = read_token(token);
            checkError(data);

            fParams_n(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            free(data->premenna);

        }else{
            printf("Error in state %d, fParams\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else{
        printf("Error in state %d, fParams\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}

void fArgs(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
    }
    else if(!strcmp(token->name,",")){

            //ocakavam argument <arg>
        data->errorValue = read_token(token);
        checkError(data);

        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Nesmusim nacitat dalsi token, pretoze precedencna analyza v <exp> fExp nacita token, a podla neho sa rozhodne ci ma prestat nacitavat vyraz
            // Ak nacita ')', znaci to EPSILON PRECHOD v <args>, ak nacita ',' tak to znaci dalsie argumenty
            //Token vrati precedencna analyza v premennej 'token'
        fArgs(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, fArgs\n", *state);
        data->errorValue = 2;
        checkError(data);    
    }
}



/**
 * @brief Function for nondeterminal Arg in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fArg(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,")")){
        //nacitali sme EPSILON
        //Nacitane: ID ()
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){

        if(!strcmp(token->name,"identifier")){
            if(isFunction(NULL, token->value)){
                printf("Error in state %d, fArg, ID of function in <arg>\n", *state);
                data->errorValue = 2;
                checkError(data);

            }
        }
            //Ocakavam argument <arg>
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
       
            //Nesmusim nacitat dalsi token, pretoze precedencna analyza v <exp> fExp nacita token, a podla neho sa rozhodne ci ma prestat nacitavat vyraz
            // Ak nacita ')', znaci to EPSILON PRECHOD v <args>, ak nacita ',' tak to znaci dalsie argumenty
            //Token vrati precedencna analyza v premennej 'token'
        fArgs(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data); 
    }
    else{
        printf("Error in state %d, fArg\n", *state);
        data->errorValue = 2;
        checkError(data);   
    }
}


/**
 * @brief Function for nondeterminal Ret-type in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fRet_type(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,":")){
        //Nacitane: global ID : function(<par-type>) : 
       
            //ocakavam <type>
        data->errorValue = read_token(token);
        checkError(data);
            //Zanorenie sa do fType
        
        

        fType(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            //Nacitane: global ID : function(<par-type>) : integer
        
            //ocakavam <types>
        data->errorValue = read_token(token);
        checkError(data);
        
            //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x  synAnalys(token, state)
        fTypes(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Nacitane: global ID : function(<par-type>) : integer, string
    }
    else if(((!strcmp(token->name,"keyword") && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))) || !strcmp(token->name,"identifier")) && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 3., 4. a 5. 
        free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;

        
    }
    else if(!strcmp(token->name,"-1") && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 2. 
        free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;
        
    }
    else if(*state == params_n && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
        //Znaci EPSILON prechod do <st-list>, pravidlo 4.
        free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;
        
    }
    else{
        printf("Error in state %d, fRet_type\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}



/**
 * @brief Function for nondeterminal Type in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fType(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")){
            if(*state == par_type){
                if(!strcmp(token->value,"integer"))
                    data->funkcia->param_types[data->funkcia->param_length] = 0;
                else if (!strcmp(token->value,"number"))
                    data->funkcia->param_types[data->funkcia->param_length] = 1;
                else if (!strcmp(token->value,"string"))
                    data->funkcia->param_types[data->funkcia->param_length] = 2;
                data->funkcia->param_length++;
                //TODO realloc
            }else if(*state == ret_type || *state == params_n ){
                if(!strcmp(token->value,"integer"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 0;
                else if (!strcmp(token->value,"number"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 1;
                else if (!strcmp(token->value,"string"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 2;
                data->funkcia->ret_length++;
                //TODO realloc
            }else if(*state == params){
                if(!strcmp(token->value,"integer"))
                    data->premenna->dataType = 0;
                else if (!strcmp(token->value,"number"))
                    data->premenna->dataType = 1;
                else if (!strcmp(token->value,"string"))
                    data->premenna->dataType = 2;

            }
    }
    else{
        printf("Error in state %d, fType\n", *state);
        data->errorValue = 2;
        checkError(data);
        
    }
}



/**
 * @brief Function for nondeterminal Types in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fTypes(Token *token, enum STATE *state, Data_t *data){
    
        if(!strcmp(token->name,")") && *state == par_type){
            //Nacitane: global ID : function (string,integer) 

            //parameter funkcie je prazdny, nie je tam nic 
            //riesim parameter funkcie a momentalne je token v parmetri brany ako EPSILON
            
        }
        else if(!strcmp(token->name,",")){
                //Nacitane: global ID : function (string, 
                //ocakavam <type>
            data->errorValue = read_token(token);
            checkError(data);

                //Zanorenie sa do fType
            fType(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Nacitane: global ID : function (string, integer  / global ID : function (string,integer) : integer, integer

                //ocakavam <types>
            data->errorValue = read_token(token);
            checkError(data);


                //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
                //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x  synAnalys(token, state)
             fTypes(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Nacitane: global ID : function (string, integer,number, / global ID : function (string,integer) : integer, integer, string, 
        }
        else if((*state == ret_type && !strcmp(token->name,"keyword")) && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 3. a 4.
            // printf("name : %s\n", token->name);
            // printf("value : %s\n", token->value);

            

        }
        else if(*state == ret_type && !strcmp(token->name,"identifier")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 5. 
            
        }
        else if(*state == ret_type && !strcmp(token->name,"-1")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 2.
            
        }
        else if(*state == params_n && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
            //Znaci EPSILON prechod od <st-list>, pravidlo 4.
            
        }
        else{
            printf("Error in state %d, fTypes\n", *state);
            data->errorValue = 2;
            checkError(data);   
        }
}


/**
 * @brief Function for nondeterminal Par-type in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */


void fPar_type(Token *token, enum STATE *state, Data_t *data){
   // printf("name : %s\n", token->name);
   // printf("value : %s\n", token->value);

     if(!strcmp(token->name,")")){
            //Nacitane: global ID : function ()
            //parameter funkcie je prazdny, nie je tam nic 
            free(data->funkcia->param_types);
            data->funkcia->param_types = NULL;
            data->funkcia->param_length = 0;

            
    }
    else if(!strcmp(token->name,"keyword") && (!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")) ){
                //parameter je jeden z datovych typov
            if(!strcmp(token->value,"integer"))
                data->funkcia->param_types[data->funkcia->param_length] = 0;
            else if (!strcmp(token->value,"number"))
                data->funkcia->param_types[data->funkcia->param_length] = 1;
            else if (!strcmp(token->value,"string"))
                data->funkcia->param_types[data->funkcia->param_length] = 2;

            data->funkcia->param_length++;
            //TODO realloc

            //if(funkcia->param_length == LENGTH(funkcia->param_types)){
             //   printf("HELLO\n");
            //}



                //ocakavam <types>
            data->errorValue = read_token(token);
            checkError(data);

                //Zanorenie sa do funkcie fTypes, kde budem riesit datove typy
            fTypes(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Nacitane: global ID : function (string, integer)
    }
    else{
            printf("Error in state %d, fPar_type\n", *state);
            data->errorValue = 2;
            checkError(data);   
    }
}


/**
 * @brief Function for nondeterminal Prog-con in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fProg_con(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"global")){
        //Riesime pravidlo 3. kedy ideme inizializovat globalnu funkciu
        //nacitane: global, pravidlo 3.
              
                //nacitanie ID funkcie
                //TODO pridaj do tabulky symbolov

            
            data->errorValue = read_token(token);
            checkError(data);
                
                


             //printf("name : %s\n", token->name);
             //printf("value : %s\n", token->value);
            
            if(strcmp(token->name,"identifier")){
                printf("Error in state %d, ID not included\n", *state);
                data->errorValue = 2;
                checkError(data);
                
            }

                //zistenie, ci sa dane ID uz vyskytuje v tabulke alebo nie
            if (search(data->list->last->rootPtr, token->value) != NULL){
                data->errorValue = 3;
                printf("rovnake meno funkcie\n");
                checkError(data);
            }
                //nacitane: global ID

            Function_t *funkcia = malloc(sizeof(Function_t));
            data->funkcia = funkcia;
            funkcia->ID = malloc(sizeof(char)*strlen(token->value));
            if(funkcia->ID == NULL){
                data->errorValue = 99;
                checkError(data);
            }
            memset(funkcia->ID, '\0',strlen(token->value));
            funkcia->ID = token->value;
            //printf("token: %s\n", token->value);
            //printf("funkcia: %s\n", funkcia->ID);
            


                //ocakavanie dvojbodky
            data->errorValue = read_token(token);
            checkError(data);

            if(!strcmp(token->name, ":")){
                //nacitane: global ID :
                    
                    //Ocakavam klucove slovo 'function'
                data->errorValue = read_token(token);
                checkError(data);

                if(!strcmp(token->name,"keyword") && !strcmp(token->value,"function")){
                    //Nacitane: global ID : function
                    
                        //Ocakavam '('
                    data->errorValue = read_token(token);
                    checkError(data);

                    if(!strcmp(token->name,"(")){
                        //Nacitane: global ID : function (
                        
                        funkcia->param_types = malloc(sizeof(int)*15);
                        if(funkcia->param_types == NULL){
                            free(funkcia->ID);
                            free(funkcia);
                            data->funkcia = NULL;
                            data->errorValue = 99;
                            checkError(data);
                        }

                        funkcia->param_length = 0;

                            //Ocakavam <par-type>
                        data->errorValue = read_token(token);
                        checkError(data);
                        
                            //Zmena stavu
                        *state = par_type;
                        fPar_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                        checkError(data);
                            //Nacitane: global ID : function(<par-type>)


                            //Ocakavam <ret-type>
                        data->errorValue = read_token(token);
                        checkError(data);


                        funkcia->ret_types = malloc(sizeof(int)*15);
                        if(funkcia->ret_types == NULL){
                            free(funkcia->param_types);
                            free(funkcia->ID);
                            free(funkcia);
                            data->funkcia = NULL;
                            data->errorValue = 99;
                            checkError(data);
                        }

                        funkcia->ret_length = 0;
                        
                            //Zmena stavu
                        *state = ret_type;
                            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x  synAnalys(token, state)
                        fRet_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                        checkError(data);
                            //Nacitane: global ID : function(<par-type>)<ret-type>

                        //Tu by mala byt data->funkcia naplnena vsetkym co potrebujem pre vytvorenie FunNode
                        //Vytvaranie FunNode
                        TNode * newLeaf = createFuncNode(data->funkcia->ID, false, data->funkcia->param_types, data->funkcia->param_length, data->funkcia->ret_types, data->funkcia->ret_length, &(data->errorValue));
                        insert(&(data->list->first->rootPtr), newLeaf);
                        
                        
                        //TODO GENEROVANIE KODU


                        //Uvolnenie alokovanej premennej
                        free(funkcia->ID);
                        free(funkcia->param_types);
                        free(funkcia->ret_types);
                        free(funkcia);
                        data->funkcia = NULL;


                            //Ocakavam <prog_con>                        
                            //Zmena stavu
                        *state = prog_con;
                            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x  synAnalys(token, state)
                        fProg_con(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                        checkError(data);
                        //Nacitane: global ID : function(<par-type>)<ret-type><prog-con>
                        
                    }
                    else{
                        printf("Error in state %d, \'(\' not included\n", *state);
                        data->errorValue = 2;
                        checkError(data);
                    }
                }
                else{
                    printf("Error in state %d, function keyword not included\n", *state);
                    data->errorValue = 2;
                    checkError(data);                   
                }
            }
            else{
                printf("Error in state %d, : not included\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"function")){
        //Nacitane: function, pravidlo 4.

            //Ocakavam ID
        data->errorValue = read_token(token);
        checkError(data);

            //nacitane: function ID
        if(strcmp(token->name,"identifier")){
            printf("Error in state %d, ID not included\n", *state);
            data->errorValue = 2;
            checkError(data);    
        }


        TNode * element = search(data->list->last->rootPtr, token->value);
        if (element != NULL){
            if(!(element->function)){
                data->errorValue = 3;
                checkError(data);
            }
            else if((element->func->defined)){
                data->errorValue = 3;
                checkError(data);
            }
        }


        Function_t funkcia;
        data->funkcia = &funkcia;
        data->funkcia->ID = malloc(sizeof(char)*strlen(token->value));
        if(data->funkcia->ID == NULL){
            data->errorValue = 99;
            checkError(data);
        }





            //Ocakavam '('
        data->errorValue = read_token(token);
        checkError(data);
            //nacitane: function ID (
        if(!strcmp(token->name,"(")){

            //Crete frame
            TNode *rootPtr = NULL;
            insertFirst(data->list, true, rootPtr);


            *state = params;
                //Ocakavam <params>
            data->errorValue = read_token(token);
            checkError(data);

            fParams(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //TU JE ZOZNAM PARAMETROV

                //Tento stav simuluje pravidlo 4., teda definiciu funkcie aj s telom
                //Stav je tu preto, aby som v <ret-type> dokazal rozoznat EPSILON prechod do <st-list>

                //Ocakavam <ret-type>
            data->errorValue = read_token(token);
            checkError(data);

            data->funkcia->ret_types = malloc(sizeof(int)*15);
            if(data->funkcia->ret_types == NULL){
                free(data->funkcia->param_types);
                free(data->funkcia->ID);
                free(data->funkcia);
                data->funkcia = NULL;
                data->errorValue = 99;
                checkError(data);
            }

            data->funkcia->ret_length = 0;

            
            *state = params_n;

            fRet_type(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


                //Kontrola ci dana funkcia existuje, ak ano tak jej zmenim definiciu
            TNode *leaf =search(data->list->last->rootPtr, data->funkcia->ID); 
            if(leaf != NULL){
                leaf->func->defined = true;

            }else{
                //Vlozenie do symtable
                insert(&(data->list->last->rootPtr), createFuncNode(data->funkcia->ID, true, data->funkcia->param_types, data->funkcia->param_length, data->funkcia->ret_types, data->funkcia->ret_length, &(data->errorValue)));
                checkError(data);
            }



            //Vkladanie Function_t do symtable


                //ZOZNAM RETURN TYPOV
            
            *state = st_list;
                //Token mam nacitany z fRet_type, na zaklane neho som urcoval EPSILON prechod
             fSt_list(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                //Zaver
            *state = prog_con;

                //Ocakavam <prog_con>, musim nacitat token lebo <st-list> konicl v EPSILON prechode a tym bol keyword 'end' danej funkcie
            data->errorValue = read_token(token);
            checkError(data);

            fProg_con(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
        }
        else{
            printf("Error in state %d, \'(\' not included\n", *state);
            data->errorValue = 2;
            checkError(data);   
        }
    }
    else if(!strcmp(token->name,"identifier")){
        //Nacitane: ID, pravidlo 5.
        //TODO zistit ci je funkcia aspon deklarovana

            //Ocakavam '('
        data->errorValue = read_token(token);
        checkError(data);
        
        if(!strcmp(token->name,"(")){
            //Nacitane: ID (

            data->errorValue = read_token(token);
            checkError(data);

            *state = arg;
                //Ocakavam argument

            fArg(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

                // pokracovanie do prog_con
            *state = prog_con;    
            data->errorValue = read_token(token);
            checkError(data);

            fProg_con(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);        
        }
        else{
            printf("Error in state %d, \'(\' not included\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"-1")){
        //Token je to EOF, znaeci EPSILON
        //Nacitane: EPSILON, pravidlo 2.   
    }
    else{
        printf("Error in state %d, fProg_con\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}




/**
 * @brief Function for nondeterminal Exp in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fExp(Token *token, enum STATE *state, Data_t *data){
        //TODO CALL precedencnu analyzu
        //TODO check token in symtable

    if(*state == prog){
        if(!strcmp(token->name,"string") && !strcmp(token->value,"ifj21")){
            data->errorValue = 0;
        }
        else{
            printf("Error in state %d, fExp\n", *state);
            data->errorValue = 2;
            checkError(data);   
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(")){
        //TODO ALL
            //TODO treba do podmienky zahrnut NIL
            //Check if is Expression
            //if Expression and *state = arg then ERROR;
            //if Function ID and *state = arg then ERROR;
            //Call precedence analysis
            
            //TODO treba sa dohodnut na returnoch, precedencna analyza by mala nacitat dalsi token a podla abecedy usudit, kedy treba prestat nacitavat
            //TODO Parser uz nenacitava dalsi token, funkcie pocitaju s tym, ze sa z precedencnej analyzi vrati v premennej 'token' dalsi nacitany token
        exp_analysator(data);
    }
    else if(*state == arg && !strcmp(token->name,")")){
            //situacia, ak by som v argumetne dostal nedokonceny argument, takze napr: (x,5,), to znamena ze by to koncilo ciarkou co je semanticka chyba
        printf("Error in state %d, fExp\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
    
    //TODO poriesit ostatne znaky ako napriklad operatory 
    
}




/**
 * @brief Function synAnalys, which start complilation of code
 *        Load require "ifj21"
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void synAnalys(Token *token, enum STATE *state, Data_t *data){
    
        //STRCMP -> ak sa stringy rovnaju, tak je return 0, preto v podmienkach !
        //Inizializovany stav, state->prog
    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"require")){
            //nacitanie dalsieho tokenu
        data->errorValue = read_token(token);
        checkError(data);
    
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            

            //Natahanie dalsieho tokenu
        data->errorValue = read_token(token);
        checkError(data);

            //Zmena stavu a rekurzovne zanorenie
        *state = prog_con;
         fProg_con(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, keyword require not included\n", *state);
        data->errorValue = 2;
        checkError(data);   
    }  

}   




int main(){

    
    Data_t *data = malloc(sizeof(Data_t));
    //osetrenie chyby mallocu
    
    data->errorValue = 0;
    data->isError = false;  

    Tframe_list *frames = malloc(sizeof(Tframe_list));
    initList(frames);
    TNode *rootPtr = NULL;
    insertFirst(frames, true, rootPtr);

    data->list = frames;


        //Idem vytvarat a vkladat vestavene funkce
    data->errorValue = createInbuildFunctions(data);
    checkError(data);
    
    
    enum STATE state = prog;
    //Osetrenie chyby mallocu



    Token *token = malloc(sizeof(Token));
    //TODO osetri malloc error

    data->token = token;

    data->errorValue = read_token(token);
    checkError(data);


    synAnalys(token, &state, data);
    checkError(data);
    
    printf("Syn analys: %d\n", data->errorValue);  

    free(token);
    free(data);


    return 0;
}