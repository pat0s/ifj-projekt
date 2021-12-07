/**
 * Project: IFJ21
 * @file synAnalys.c
 * @author Dalibor Králik
 * @version 0.1
 * 
 * 
 * @copyright Copyright (c) 2021
 * 
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "synAnalys.h"
#include "error.h"
#include "code_generator.h"
#include "symtable.h"





/**
 * @brief Function for checking errors
 * 
 * @param data Pointer to data structure with errorValue which trigger error message
 */

void checkError(Data_t *data){

        if(data->errorValue == 1){
            fprintf(stderr,  "Lexical analysis Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(1);

        }
        else if(data->errorValue == 2){
            fprintf(stderr,  "Syntax Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(2);

        }
        else if(data->errorValue == 3){
            fprintf(stderr,  "Semantic Error - definition/redefinition problem\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(3);

        }
        else if(data->errorValue == 4){
            fprintf(stderr,  "Semantic Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(4);

        }
        else if(data->errorValue == 5){
            fprintf(stderr,  "Semantic Error - bad number of data type, type incompatibility\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(5);

        }
        else if(data->errorValue == 6){
            fprintf(stderr,  "Semantic Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(6);

        }
        else if(data->errorValue == 7){
            fprintf(stderr,  "Other semantic Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(7);

        }
        else if(data->errorValue == 8){
            fprintf(stderr,  "Runtime Error - Unexpected nil value\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(8);

        }
        else if(data->errorValue == 9){
            fprintf(stderr,  "Runtime Error - Dividing by zero\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
            free(data);
            exit(9);

        }
        else if (data->errorValue == 99){
            fprintf(stderr,  "Internal Error\n");
            free(data->token);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
                deleteFirst(data->list);
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
    funkcia.ID = malloc(sizeof(char)*10);
    if(funkcia.ID == NULL)
        return INTERNAL_ERROR;
    memset(funkcia.ID, '\0', 10);
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

        if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(") ||(!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){
            if(!strcmp(token->name,"identifier")){
                if(isFunction(data->list->last->rootPtr, token->value)){
                    fprintf(stderr, "Error in state %d, fValues, Function instead of variable\n", *state);
                    data->errorValue = 2;
                    checkError(data);
                }
                
                TNode * element = searchFrames(data->list, token->value);
                if(element == NULL){
                    fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru1\n");
                    data->errorValue = 3;
                    checkError(data);
                }
            }

                //semanticka kontrola spravneho poctu returnovych hodnot
            if(data->arrayTypeLength == data->indexType){
                fprintf(stderr, "\nERROR - Nadmerny pocet vyrazov v returne2\n");
                data->errorValue = 5;
                checkError(data);
            }
            data->dataType = data->arrayType[data->indexType];

            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory pojdem analyzovat
            
            RETURN_RETVALS(&(data->string), data->whileDeep, INT2STRING(data->indexType));

            //inkrementacia pocitadla indexu pre pole datovy typova navratovych hodnot
            data->indexType++;

            fValues(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            
        }
        else{
            fprintf(stderr, "Error in state %d, fValues, missing expression after \',\'\n", *state);
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
    data->errorCode = 5;
    if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(") ||(!strcmp(token->name,"keyword") && !strcmp(token->value,"nil")) ){
        if(!strcmp(token->name,"identifier")){
            
                //TODO tu to padalo na segmentation fault ak funkcia neexistovala -> preslo to do fexp a padlo
            if(isFunction(data->list->last->rootPtr, token->value)){

                TNode * element2 = search(data->list->last->rootPtr, token->value);
                if(element2 == NULL){
                    fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru5\n");
                    data->errorValue = 3;
                    checkError(data);
                }

                    //inicializacia pre semanticke kontroly
                data->leaf = element2;
                data->indexType = 0;                  
                    //je to ID funkcie
                    //TODO treba zistit zo symtable, ci je funkcia aspon deklarovana

                    //Nacitanie '('
                data->errorValue = read_token(token);
                checkError(data);

                if(strcmp(token->name,"(")){
                    fprintf(stderr, "Error in state %d, fValue, missing \'(\'\n", *state);
                    data->errorValue = 2;
                    checkError(data);
                }

                    //Nacitanie argumentu funkcie
                data->errorValue = read_token(token);
                checkError(data);


                    //generovanie kodu, createframe pre funkciu
                CREATEFRAME(&(data->string), data->whileDeep);

                fArg(token, state, data, element2->ID);
                checkError(data);
                data->errorCode = 4;

                if(data->leaf->func->param_length != data->indexType){
                    fprintf(stderr, "ERROR - zly pocet parametrov volania funkcie\n");
                    data->errorValue = 5;
                    checkError(data);
                }
                    //return funkcie, kontrola spravneho poctu parametrov

                if(data->leaf->func->ret_length > data->arrayTypeLength){
                    fprintf(stderr, "ERROR - Vysoky pocet returnovych hodnot inej funckie v returne sucastnej funkcie\n");
                    data->errorValue = 5;
                    checkError(data);
                }
                
                    //generovanie kodu call_func
                if(strcmp(element2->ID, "write")){
                    CALL_FUNC(&(data->string), data->whileDeep, data->leaf->ID);

                }
                
                //TODO TODO
                //TODO musim ist odzadu ale neviem podla ktorej premennej, treba skontrolovat
                //priradenie returnov vnorenej funkcie do returnov vonkajsej funkcie, musim priradit zozadu
                for(int i = data->leaf->func->ret_length-1; i >= 0 ; i--){
                    RETURN_RETVALS(&(data->string), data->whileDeep, INT2STRING(i));

                }

                   //vycistenie ukazatela na pomocny TNode
                data->indexType = 0;
                data->leaf = NULL;

                    //Nacitanie dalsieho tokenu, ocakavam <st-list>
                data->errorValue = read_token(token);
                checkError(data);
            }
            else{
                TNode * element = searchFrames(data->list, token->value);
                if(element == NULL){
                    fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru2\n");
                    data->errorValue = 3;
                    checkError(data);
                }
                
                    //pripradava na semanticku kontrolu, ulozenie datoveho typu a vynulovanie poctu
                data->indexType = 0;
                //printf("arrayLength1: %d\n", data->arrayTypeLength);
                if(data->arrayTypeLength == data->indexType){
                    fprintf(stderr, "\nERROR - Nadmerny pocet vyrazov v returne3\n");
                    data->errorValue = 5;
                    checkError(data);

                }
                data->dataType = data->arrayType[data->indexType];

                    //Token je ID premennej
                    //TODO treba zistit zo symtable, ci je ID premenna inicializovana
                    //je to ID premennej, idem do <exp> fExp
                fExp(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
                    //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory idem teraz analyzovat
                
                RETURN_RETVALS(&(data->string), data->whileDeep, INT2STRING(data->indexType));
                
                    //inkrementacia pocitadla indexu pre pole datovy typova navratovych hodnot
                data->indexType++;


                fValues(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);

                data->indexType = 0;

            }
        }
        else{
                //pripradava na semanticku kontrolu, ulozenie datoveho typu a vynulovanie poctu
            data->indexType = 0;
            //printf("arrayLength2: %d\n", data->arrayTypeLength);
            if(data->arrayTypeLength == data->indexType){
                fprintf(stderr, "\nERROR - Nadmerny pocet vyrazov v returne1\n");
                data->errorValue = 5;
                checkError(data);
            }
            data->dataType = data->arrayType[data->indexType];

                //Token je string, number lebo int
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati token, ktory idem teraz analyzovat
            RETURN_RETVALS(&(data->string), data->whileDeep, INT2STRING(data->indexType)); 
                //inkrementacia pocitadla indexu pre pole datovy typova navratovych hodnot
            data->indexType++;


            fValues(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            data->indexType = 0;

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
    //fprintf(stderr, "name: %s, value: %s\n", token->name, token->value);


    if(!strcmp(token->name,"identifier")){
        if(isFunction(data->list->last->rootPtr, token->value)){
            TNode * element2 = search(data->list->last->rootPtr, token->value);
            if(element2 == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru30\n");
                data->errorValue = 3;
                checkError(data);
            }
                //inicializacia pre semanticke kontroly
            data->leaf = element2;
            data->indexType = 0;
                //je to ID funkcie
                //TODO treba zistit zo symtable, ci je funkcia aspon deklarovana

                //Nacitanie '('
            data->errorValue = read_token(token);
            checkError(data);

            if(strcmp(token->name,"(")){
                fprintf(stderr, "Error in state %d, fInit_value, missing \'(\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

                //Nacitanie argumentu funkcie
            data->errorValue = read_token(token);
            checkError(data);

                //generovanie kodu, createframe pre funkciu
            CREATEFRAME(&(data->string), data->whileDeep);

            fArg(token, state, data, element2->ID);
            checkError(data);
            
            data->errorCode = 4;
            if(data->leaf->func->param_length != data->indexType){
                fprintf(stderr, "ERROR - zly pocet parametrov volania funkcie\n");
                data->errorValue = 5; // aelbo 7, alebo 4
                checkError(data);
            }

                //skontrolovanie datoveho typu a poctu navratovych hodnot
            if(data->leaf->func->ret_length < 1){
                //TODO skontroluj chybovy kod
                fprintf(stderr, "ERROR - priradenie funkcie, ktora vracia nehodny pocet navratovych hodnot\n");
                data->errorValue = 5;
                checkError(data);

            }

                //kontrola spravneho datoveho typu medzi priradenim predemmenj a returnu funkcie
            //printf("leaf: %d, premenna: %d\n",data->leaf->func->ret_types[0],data->premenna->dataType  );
            if(data->leaf->func->ret_types[0] != data->premenna->dataType){
                //TODO skontroluj chybovy kod
                fprintf(stderr, "ERROR - priradenie funkcie, ktora vracia nehodny datovy typ navratovej hodnoty\n");
                data->errorValue = 4;
                checkError(data);

            }


                //generovanie kodu call_func

            if(strcmp(element2->ID, "write")){
                CALL_FUNC(&(data->string), data->whileDeep, data->leaf->ID);
            }
            //TODO POPS DO VOIDU AK funkcia vrati viac ako 1 return na zasobnik
            for(int i = data->leaf->func->ret_length; i > 1; i--){
                //TODO POPS DO VOIDU
                POPS_INFINITE(&(data->string), data->whileDeep);
            }

               //vycistenie ukazatela na pomocny TNode
            data->indexType = 0;
            data->leaf = NULL;

                //Nacitanie dalsieho tokenu, ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);
        }
        else{
            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru3\n");
                data->errorValue = 3;
                checkError(data);
            }

                //posielanie datoveho typu precedencnej analyze
            data->dataType = data->premenna->dataType;
                //TODO treba zistit zo symtable, ci je ID premenna inicializovana
                //je to ID premennej, idem do <exp> fExp
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
                //Pocitam s tym, ze mi precedencna analyza v tokene vrati <st-list>
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#") || !strcmp(token->name,"(") ||(!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){
       
            //posielanie datoveho typu precedencnej analyze
        data->dataType = data->premenna->dataType;
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            //Pocitam s tym, ze mi precedencna analyza v tokene vrati <st-list>
        //data->errorValue = read_token(token);
        //checkError(data);
        //data->errorValue = read_token(token);
        //checkError(data);
    }
    else{
        fprintf(stderr, "Error in state %d, fInit_value\n", *state);
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

        POPS(&(data->string), data->whileDeep, data->premenna->ID, INT2STRING(data->specialIDNumber));

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
            if(isFunction(data->list->last->rootPtr, token->value)){
                fprintf(stderr, "Error in state %d, fAssigns, ID of function in <assigns>\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru4\n");
                data->errorValue = 3;
                checkError(data);
            }
        }
        else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#")  || !strcmp(token->name,"(") || (!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){
            //Naschval prazdne, pre jednoduchost tu nechavam tuto podmienku


        }
        else{
            fprintf(stderr, "Error in state %d, fAssigns,unexpected token type\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

            //osetrenie segmentation fault pri moznom priradeni vaic hodnot ako je identifikatorov: id1, id2 = 10, 10, 10
            //Ak nastane tato situacia, hodnoty by sa mali zahodit
        if(data->assignArrayIndex < data->assignArrayLength){
                //vlozenie datoveho type pre precedencnu analyzu
            data->dataType = data->assignArray[data->assignArrayIndex].dataType;

        }else{
            data->checkDataType = false;
        }
            fExp(token, state, data);
            checkError(data);

            data->assignArrayIndex++;

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
        if(isFunction(data->list->last->rootPtr, token->value)){
            TNode * element2 = search(data->list->last->rootPtr, token->value);
            if(element2 == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru5\n");
                data->errorValue = 3;
                checkError(data);
            }

                //inicializacia pre semanticke kontroly
            data->leaf = element2;
            data->indexType = 0;

            if(strcmp(data->leaf->ID, "write")){
                data->checkDataType = false;
            }
            

                //TODO Zistit v symtable, ci je deklarovana, ak nie tak ERROR
                //Nacitanie '('
            data->errorValue = read_token(token);
            checkError(data);

            if(strcmp(token->name,"(")){
                fprintf(stderr, "Error in state %d, fAssign, missing \'(\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

                //Nacitanie argumentu funkcie
            data->errorValue = read_token(token);
            checkError(data);

                //generovanie kodu, createframe pre funkciu
            CREATEFRAME(&(data->string), data->whileDeep);

            fArg(token, state, data, element2->ID);
            data->errorCode = 4;
            checkError(data);
                //Netreba nacitat dalsi token, ked sa vynorim, a bude posledny token ')', tak sa nacita novy token

            if(data->leaf->func->param_length != data->indexType){
                fprintf(stderr, "ERROR - zly pocet parametrov volania funkcie10\n");
                data->errorValue = 5;
                checkError(data);
            }

            
                //kontrola spravneho poctu returnov pri priradeni vysledku funkcie; a = foo(3)
            //printf("assignLength: %d, Ret_length: %d\n", data->assignArrayLength,data->leaf->func->ret_length);
            if(data->assignArrayLength > data->leaf->func->ret_length){
                //TODO skontroluj chybu a jej chybovu hodnot, moze byt 7 alebo 4
                fprintf(stderr, "ERROR - zly pocet returnovych hodnot funkcie pri pridareni10\n");
                data->errorValue = 5;
                checkError(data);

            }

                //generovanie kodu call_func
            if(strcmp(element2->ID, "write")){    
                CALL_FUNC(&(data->string), data->whileDeep, data->leaf->ID);
            }
            //TODO POPS DO VOIDU AK funkcia vrati viac ako 1 return na zasobnik
            for(int i = data->leaf->func->ret_length; i > data->assignArrayLength; i--){
                POPS_INFINITE(&(data->string), data->whileDeep);
                //TODO POPS DO VOIDU
            }


                //TODO cyklus cez pole datovych typov assignarray a navrativych hodnto funkcie ret_types
                //kontrola spravneho typu pri priradeni vsledku funkcie do premennej; a:integer = foo(10):integer
            for(int i = 0; i < data->assignArrayLength; i++){
                if(data->assignArray[i].dataType != data->leaf->func->ret_types[i]){
                    fprintf(stderr, "ERROR - typova nekompatibilita pri priradeni returnu funkcie do premennej10\n");
                    data->errorValue = 4;
                    checkError(data);

                }
            }

               //vycistenie ukazatela na pomocny TNode
            data->indexType = 0;
            data->leaf = NULL;
       
       }
        else{
            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru5\n");
                data->errorValue = 3;
                checkError(data);
            }


                //viac priradzujem hodnot ako ocakavam na lavej strane

            data->dataType = data->assignArray[data->assignArrayIndex].dataType;
                //priradenie do data->dataType pre potrebyn fexp
            //data->dataType = data->assignArray[data->assignArrayIndex].dataType;
                // ide o ID premennej
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            data->assignArrayIndex++;


                //Inkrementacia indexu assignArray, pre potreby fExp
            //data->assignArrayIndex++;
                //nemusim nacitavat dalsi token, lebo mi to precedencna analyza vrati v ukazatali a premennej 'token'
                //precedencna analyza sa musi zastavit v momente, kedy narazi na ',' alebo EPSILON PRECHOD, v tomto pripade <st-list>
                //Az vo funkcii fAssings() zistim, ci sa jednalo o EPSILON prechod alebo o ',' a teda dalsie hodnoty do priradenia
            fAssigns(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


            //printf("index: %d, length: %d\n", data->assignArrayIndex, data->assignArrayLength );
                //TODO asi kontrola ak je data->assignArrayIndex < data->assignArraylength tak error
            if(data->assignArrayIndex < data->assignArrayLength){
                fprintf(stderr, "\nERROR - Nizky pocet priradeni k identifikatorom\n");
                data->errorValue = 7;
                checkError(data);


            }
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"#") || !strcmp(token->name,"(") || (!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){


        
        data->dataType = data->assignArray[data->assignArrayIndex].dataType;
            //priradenie do data->dataType pre potrebyn fexp
        //data->dataType = data->assignArray[data->assignArrayIndex].dataType;
            //fprintf(stderr, "\n\ntoken pred fExp: %s\n\n\n", token->value);
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            //fprintf(stderr, "\n\ntoken po fExp: %s\n\n\n", token->value);

            //Inkrementacia indexu assignArray, pre potreby fExp
        data->assignArrayIndex++;

            //nemusim nacitavat dalsi token, lebo mi to precedencna analyza vrati v ukazatali a premennej 'token'
            //precedencna analyza sa musi zastavit v momente, kedy narazi na ',' alebo EPSILON PRECHOD, v tomto pripade <st-list>
            //Az vo funkcii fAssings() zistim, ci sa jednalo o EPSILON prechod alebo o ',' a teda dalsie hodnoty do priradenia
        fAssigns(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        //printf("index: %d, length: %d\n", data->assignArrayIndex, data->assignArrayLength );
            //TODO asi kontrola ak je data->assignArrayIndex < data->assignArraylength tak error
        if(data->assignArrayIndex < data->assignArrayLength){
            fprintf(stderr, "\nERROR - Nizky pocet priradeni k identifikatorom\n");
            data->errorValue = 7;
            checkError(data);
        }
    }
    else{
        fprintf(stderr, "Error in state %d, fAssign\n", *state);
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
            if(!isFunction(data->list->last->rootPtr, token->value)){
                //fprintf(stderr, "\ntoken->value: %s\n", token->value);
                    //kontrola ci je token->value v symtable
                TNode * element = searchFrames(data->list, token->value);
                if(element == NULL){
                    fprintf(stderr, "\nERROR - volanie neexistujucej funkcie6\n");
                    data->errorValue = 3;
                    checkError(data);
                }

                 //TODO alokovat data->assignArray[].name
                    //Priradenie datoveho typu do pola pre identifikatory, element je hladany z ID pracovaneho predtym
                data->assignArray[data->assignArrayLength].dataType = element->var->data_type;
                data->assignArrayLength++;
                //printf("element->ID3: %s\n", element->ID);



                    //ocakavam ',' alebo '=' a teda prechod od <item-n>
                data->errorValue = read_token(token);
                checkError(data);
    
                fItem_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);


                //TODO POPS pre n-tu premennu pri viacnasobnom priradeni, kde jej hodnota je na zasobniku uz pushnuta
                POPS(&(data->string), data->whileDeep, element->ID, INT2STRING(element->var->specialID));
            }
            else{
                fprintf(stderr, "Error in state %d, fItem_n, function instead of ID of variable\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            fprintf(stderr, "Error in state %d, fItem_n, expect ID but token is not ID\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"=")){

            //Ocakavam <assign>
        data->errorValue = read_token(token);
        checkError(data);
        data->checkDataType = true;


        fAssign(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        fprintf(stderr, "Error in state %d, fItem_n\n", *state);
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
        TNode * element = search(data->list->last->rootPtr, data->tokenValue);
        if(element == NULL){
            fprintf(stderr, "\nERROR - volanie neexistujucej funkcie1\n");
            data->errorValue = 3;
            checkError(data);
        }

        data->leaf = element;
        data->indexType = 0;
        data->isFunctionCalled = true;
	//		fprintf(stderr, "\nSOM vo FITEM \n\n");
		
            //Ide argumnet funkcie, dany identifikator by mal patrit funkcii

            //TODO treba skontrolovat, ci je funkcia aspon deklarovana
        
            //Ocakavam token argumentu
        data->errorValue = read_token(token);
        checkError(data);

            //generovanie kodu, createframe pre funkciu
        CREATEFRAME(&(data->string), data->whileDeep);

        fArg(token, state, data, element->ID);
        data->errorCode = 4;
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        if(data->leaf->func->param_length != data->indexType){
            fprintf( stderr,"ERROR - zly pocet parametrov volania funkcie\n");
            data->errorValue = 5;
            checkError(data);
        }


            //generovanie kodu call_func
        if(strcmp(element->ID, "write")){
            CALL_FUNC(&(data->string), data->whileDeep, data->leaf->ID);
        }
        //TODO POPS returnov funkcie do VOID premennej

        for(int i = 0; i < data->leaf->func->ret_length; i++){
            POPS_INFINITE(&(data->string), data->whileDeep);
        }


        data->leaf = NULL;
            //Som v stave, kedy mam nacitanu ')' argumentu a musim prejst do <st-list>
       // data->errorValue = read_token(token);
       // checkError(data);
            //Teraz som nacital dalsi token, v ktorom ocakavam <st-list>, spravil som to preto tu, pretoze musim pocitat situaciu spojenu s pravidlo 16. kde priradzujem a musim rozpoznat EPSILON prechod
    }
    else if(!strcmp(token->name,"=")){
        TNode * element = searchFrames(data->list, data->tokenValue);
        if(element == NULL){
            fprintf(stderr, "\nERROR - volanie nedefinovanej premennej\n");
            data->errorValue = 3;
            checkError(data);
        }

            //tvorba pola pre identifikatorov a ich datove typy
        data->checkDataType = true;
        data->errorCode = 4;
        data->assignArrayIndex = 0;
        data->assignArrayLength = 0;
        data->assignArray = malloc(sizeof(AssignToken_t) * 15);
        if(data->assignArray == NULL){
            data->errorValue = 99;
            checkError(data);
        }

            //TODO alokovat data->assignArray[].name
            //Priradenie datoveho typu do pola pre identifikatory, element je hladany z ID pracovaneho predtym
        data->assignArray[data->assignArrayLength].dataType = element->var->data_type;
        data->assignArrayLength++;


            //Prikaz priradenia, dany identifikator by mal byt premenna

            //Ocakavam bud ID funkcie alebo <exp>(<exp> moze byt aj nazov premennej, treba zistit v symtable)
            //TODO zistit v symtable
        data->errorValue = read_token(token);
        checkError(data);
        //fprintf(stderr, "\n\nin ITEM\n\n");
        fAssign(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        data->assignArrayIndex = 0;
        data->assignArrayLength = 0;
        free(data->assignArray);

            //Token so <st-list> som nacital vo fAssign()
    }
    else if(!strcmp(token->name,",")){
        TNode * element = searchFrames(data->list, data->tokenValue);
        if(element == NULL){
            fprintf(stderr, "\nERROR - volanie nedefinovanej premennej\n");
            data->errorValue = 3;
            checkError(data);
        }

            //tvorba pola pre identifikatorov a ich datove typy
        data->checkDataType = true;
        data->errorCode = 4;
        data->assignArrayIndex = 0;
        data->assignArrayLength = 0;
        data->assignArray = malloc(sizeof(AssignToken_t) * 15);
        if(data->assignArray == NULL){
            data->errorValue = 99;
            checkError(data);
        }
            //TODO alokovat data->assignArray[].name
            //Priradenie datoveho typu do pola pre identifikatory, element je hladany z ID pracovaneho predtym
        data->assignArray[data->assignArrayLength].dataType = element->var->data_type;
        data->assignArrayLength++;
        //printf("element->ID1: %s\n", element->ID);

            //prikaz priradenia, viacnasobne priradenie
            //ocakavam ID premennej
        data->errorValue = read_token(token);
        checkError(data);

            //Musim sa spytat, ci je TOKEN ID, pretoze budem cez funkciu isFunction(NULL, token->value) zistovat v symtable, ci je to ID funkcie alebo premennej a mohol by nastat problem
        if(!strcmp(token->name,"identifier")){
            if(!isFunction(data->list->last->rootPtr, token->value)){
                    //test ci je premenna v symtable
                element = searchFrames(data->list, token->value);
                if(element == NULL){
                    fprintf(stderr, "\nERROR - volanie nedefinovanej premennej7\n");
                    data->errorValue = 3;
                    checkError(data);
                }

                
                    //TODO alokovat data->assignArray[].name
                    //Priradenie datoveho typu do pola pre identifikatory, element je hladany z ID pracovaneho predtym
                data->assignArray[data->assignArrayLength].dataType = element->var->data_type;
                data->assignArrayLength++;
                //printf("element->ID2: %s\n", element->ID);


                    //ocakavam ',' alebo '=' a teda prechod od <item-n>
                data->errorValue = read_token(token);
                checkError(data);

                fItem_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);

                    //TODO POPS() pre druhu premennu ktora je vo viacnasobnom priradeni a ma hodnotu pushnutu na zasobniku
                POPS(&(data->string), data->whileDeep, element->ID, INT2STRING(element->var->specialID));


                    //Vynolovanie pola pre datove typy po vynoreni
                data->assignArrayIndex = 0;
                data->assignArrayLength = 0;
                free(data->assignArray);
            }
            else{
                fprintf(stderr, "Error in state %d, fItem_n, function instead of ID of variable\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            fprintf(stderr, "Error in state %d, fItem_n, expect ID but token is not ID\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else{
        fprintf(stderr, "Error in state %d, fItem1\n", *state);
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
        
    }else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"else") && data->isIf){
            //Narazil som na EPSILON prechod
            data->isIf--;


    }else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"if")){
        data->specialIDNumber++;

            //Ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);
        
            //Ak je nacitany token identifikator a je to ID funkcie, tak Error
        if(!strcmp(token->name,"identifier")){
            if(isFunction(data->list->last->rootPtr, token->value)){
                fprintf(stderr, "Error in state %d, fSt_list, ID of function in if statement as a condition\n", *state);
                data->errorValue = 2;
                checkError(data);
            }    
            
            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru8\n");
                data->errorValue = 3;
                checkError(data);
            }
        }
            //create frame
        TNode *rootPtr = NULL;
        insertFirst(data->list, false, rootPtr);

            //generovanie kodu, zaciatok IFU, tvorba premennych
        CONDITION_VARS(INT2STRING(data->specialIDNumber));
        data->relation_operator_in_condition = false;

            //V podmienkde Ifu sa nemozu skontrolovat datove typy, nemaju sa s cim
        data->checkDataType = false;
            //precedencna analyza by sa mala zastavit po nacitany klucoveho slova 'then', netreba to teda potom nacitavat
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        data->checkDataType = false;
        
        
            //generovanie podmienky skoku if
        IF_CONDITION(&(data->string), data->whileDeep, INT2STRING(data->specialIDNumber), data->relation_operator_in_condition);
        int IDOfIf = data->specialIDNumber;

            //Nemusim nacitavat dalsi token, lebo precedencna analyza nacita do premennje token klucove slovo 'then'
        if(!strcmp(token->name,"keyword") && !strcmp(token->value,"then")){
            
                //TODO zmena framu v symtable, tabulke symbolov

                //Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);

            if(strcmp(token->name,"keyword") ||(!strcmp(token->name,"keyword") && strcmp(token->value,"else"))){
                    //priznak zanorenia v ife
                data->isIf++;
                //fprintf(stderr, "\nSom pred st_list\n\n");
                fSt_list(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
                //fprintf(stderr, "\nSom za st_list\n\n");
            

            }            

            //fprintf(stderr, "\nSom hend pred elsom\n\n");
            
                //Teraz by sa v tokene mal nachadza 'else', otestujem to a pokracujem v behu
            if(!strcmp(token->name,"keyword") && !strcmp(token->value,"else")){
                data->specialIDNumber++;

                    //generovanie kodu else branch
                ELSE_BRANCH(&(data->string), data->whileDeep, INT2STRING(IDOfIf));


                    //vymazanie if framu z tabulky symbolov
                deleteFirst(data->list);
                    //tabulka frame v tabulke symbolov pre else
                TNode *rootPtr = NULL;
                insertFirst(data->list, false, rootPtr);


                    //Ocakavam <st-list>
                //fprintf(stderr, "\nSom v else\n\n");
                data->errorValue = read_token(token);
                checkError(data);

                fSt_list(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);    

                    //v Tokene by sa mal nachadza 'end', idem to otestovat a pokracujem v behu programu uz mimo if statement
                if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
                        //nacitam dalsi token a idem do stavu <st-list>, pokracujem v behu pogramu uz mimo if statement
                   
                        //generovnie kodu end if
                    IF_END(&(data->string), data->whileDeep, INT2STRING(IDOfIf));
                    
                    data->specialIDNumber++;
                        //odstranenie vrchneho framu v symtable
                    deleteFirst(data->list);
                        //Ocakavam <st-list>
                    data->errorValue = read_token(token);
                    checkError(data);


                    fSt_list(token, state, data);
                        //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                    checkError(data);
                }
                else{
                    fprintf(stderr, "Error in state %d, fSt_list, missing keyword \'end\'\n", *state);
                    data->errorValue = 2;
                    checkError(data);
                }
            }
            else{
                fprintf(stderr, "Error in state %d, fSt_list, missing od keyword \'else\' in if statement \n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            fprintf(stderr, "Error in state %d, fSt_list, missing od keyword \'then\' in if statement \n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"while")){

        data->whileDeep++;
        data->specialIDNumber++;

            //generovanie kodu inicializacia while
        CONDITION_VARS(INT2STRING(data->specialIDNumber));
        WHILE_START(&(data->string), data->whileDeep, INT2STRING(data->specialIDNumber));
        
            //Ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);
        
            //Ak je nacitany token identifikator a je to ID funkcie, tak Error
        if(!strcmp(token->name,"identifier")){
            if(isFunction(data->list->last->rootPtr, token->value)){
                fprintf(stderr, "Error in state %d, fSt_list, ID of function in while cycle as a condition\n", *state);
                data->errorValue = 2;
                checkError(data);
            }

            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru9\n");
                data->errorValue = 3;
                checkError(data);
            }
        }

        
            //tabulka frame v tabulke symbolov pre WHILE
            //bude jeden frame ale treba osetrit v generovani kodu definiciu funkcii
        TNode *rootPtr = NULL;
        insertFirst(data->list, false, rootPtr);
        data->relation_operator_in_condition = false;

            //vo While podmienke sa nemozu kontroloval datovy typy, nastal by problem
        data->checkDataType = false;
            //precedencna analyza nacitava dovtedy, kym nenarazi na klucove slovo 'do'
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        data->checkDataType = false;
        int whileID = data->specialIDNumber;

    

            //generovanie kodu while condition
        WHILE_CONDITION(&(data->string), data->whileDeep, INT2STRING(data->specialIDNumber), data->relation_operator_in_condition);

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
                
                    //generovanie kodu ukoncenia while
                WHILE_END(&(data->string), data->whileDeep, INT2STRING(whileID));
                
                data->whileDeep--;

                if(data->whileDeep == 0){
                    printf("%s",data->string);
                    data->string = realloc(data->string, sizeof(char));
                    data->string[0] = '\0';
                }
                data->specialIDNumber++;


                deleteFirst(data->list);
                    //Ocakavam <st-list>
                data->errorValue = read_token(token);
                checkError(data);

                fSt_list(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);
            }
            else{
                fprintf(stderr, "Error in state %d, fSt_list, missing keyword \'end\'\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            fprintf(stderr, "Error in state %d, fSt_list, missing keyword \'do\'\n", *state);
                data->errorValue = 2;
                checkError(data);
        }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"local")){
        //fprintf(stderr, "\nHERE in local\n\n");
            //Ocakavam ID
        data->errorValue = read_token(token);
        checkError(data);
        data->errorCode = 4;

            //test, ci je dany token ID, ak nie tak ERROR
        if(strcmp(token->name,"identifier")){
            fprintf(stderr, "Error in state %d, fSt_list->local, missing ID of variable\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

        TNode * element = search(data->list->first->rootPtr, token->value);
        if(element != NULL){
            data->errorValue = 3;
            fprintf(stderr, "Redefinicia premennej\n");
            checkError(data);
        }

        element = search(data->list->last->rootPtr, token->value);
        if(element != NULL){
            data->errorValue = 3;
            fprintf(stderr, "Redefinicia premennej\n");
            checkError(data);
        }

        

        Variable_t variable;
        data->premenna = &variable;
        data->premenna->ID = token->value;

            //generovanie kodu DEFVAR premennej
        DEFVAR_AND_INIT(token->value, INT2STRING(data->specialIDNumber));

            //TODO zistit ci sa dane ID vyskytuje v tomto frame v symtable, ak ano tak error, ak nie tak treba nasledne vlozit do symtable tuto premennu

            //Ocakavam ':'
        data->errorValue = read_token(token);
        checkError(data);

            //Ak chyba ':' tak ERROR inak pokracujeme
        if(strcmp(token->name,":")){
            fprintf(stderr, "Error in state %d, fSt_list->local, missing \':\'\n", *state);
            data->errorValue = 2;
            checkError(data);
        }

            //Ocakavam <type>
        data->errorValue = read_token(token);
        checkError(data);

        //ZMYSLE TO MA TU
        enum STATE helpState = *state;
        *state = params;
        fType(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        state = &helpState;


            //insert do symtable
        char pole[]="";
        //printf("name; %s, specialID: %d\n", data->premenna->ID, data->specialIDNumber);
        insert(&(data->list->first->rootPtr), createVarNode(data->premenna->ID, data->premenna->dataType, pole, &(data->errorValue), data->specialIDNumber));
        checkError(data);
        data->checkDataType = true;


            //Ocakavam <init>
        data->errorValue = read_token(token);
        checkError(data);

        fInit(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        data->checkDataType = false;


        
        
        data->premenna = NULL;
            //v tokene sa nachadza <st-list>,treba sa rekurzivne zanorit do fSt-list a skontrolovat nacitany token
            //Nacitanie som spravil v fInit() v epsilon prechode alebo vo <init-value>

        //fprintf(stderr, "\n\n\ntoken: %s\n\n\n\n", token->value);
        
        *state = st_list;
        fSt_list(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"return")){
            //Ocakavam <ret-val> a rovno <value>
        data->errorValue = read_token(token);
        checkError(data);

        data->checkDataType = true;
        fValue(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        data->checkDataType = false;


        //ak bude navratovych typov malo, bude za ne dosadeny nil, TOTO zabezpeci generovanie kodu, ktore hned pri
        //tvorbe a skoku funkcie inicializuje premenne na return a priradi im nil
        
            //V EPSILON prechode mam rovno nacitany dalsi token
    }
    else if(!strcmp(token->name,"identifier")){

        data->tokenValue = token->value;
        TNode * element = searchFrames(data->list, token->value);
            //Ocakavam <item>
        data->errorValue = read_token(token);
        checkError(data);

   //     fprintf(stderr, "token: %s\n", token->name);
			data->isFunctionCalled = false;
        

        fItem(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        

        

            //Ak som mal ID funkcie, tak v tokene je ')', musim  teda nacitat za tejto podmienky dalsi token a prejst do <st-list>
        if(data->isFunctionCalled){
         //	fprintf(stderr, "\nv prvje podmineke\n");
			//Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);
        }
        else if(!strcmp(token->name,")") && !data->isFunctionCalled){
       // 	 fprintf(stderr, "\nv druhej podmineke, %s\n", data->tokenValue);
		  	//Ocakavam <st-list>
            data->errorValue = read_token(token);
            checkError(data);
            POPS(&(data->string), data->whileDeep, data->tokenValue, INT2STRING(element->var->specialID));
        }
        else{
         //   fprintf(stderr,"\nIM am in if condition\n\n");
            // Ak sa jedna o priradenie, budem potrebovat POPS pre hodnotu zo zasobnika pre tuto premennu, ktoru som na zaciatku spracoval
            POPS(&(data->string), data->whileDeep, data->tokenValue, INT2STRING(element->var->specialID));
        }

        data->isFunctionCalled = false;

        data->tokenValue = NULL;
        data->checkDataType = false;
        data->indexType = 0;
       // fprintf(stderr, "\n\ntoken identif: %s\n\n\n", token->value);
    //docasne
        //data->errorValue = read_token(token);
        //checkError(data);
    //docasne
            //v tokene sa nachadza <st-list>,treba sa rekurzivne zanorit do fSt-list a skontrolovat nacitany token
            //Token som nacital preto dopredu, lebo pri pravidle 16. musim rozpoznat EPSILON prechod a to tak, ze tam nacitam token, vynorim sa az sem a v 
            //dalsom zanoreni skontrolujem ci je tancitany token <st-list>
        fSt_list(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        fprintf(stderr, "Error in state %d, fSt_list1231\n", *state);
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
            TNode * element = searchFrames(data->list, token->value);
            if(element != NULL){
                fprintf(stderr, "Redefinicia premennej2\n");
                data->errorValue = 3;
                checkError(data);
            }

            //search ci sa nenachadza v symtable
            char pole[] = "";
            TNode *variable = createVarNode(token->value, 0, pole, &(data->errorValue), data->specialIDNumber);
            //printf("name; %s, specialID: %d\n", variable->ID, variable->var->specialID);
            checkError(data);

                //generovanie kodu parametrov definicie funkcie
            PARAMETERS(data->funkcia->ID, token->value, data->funkcia->param_length, INT2STRING(data->specialIDNumber));

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

                //fprintf(stderr, "datovy typ: %d\n", variable->var->data_type);

                    //Vlozenie do symtable
                insert(&(data->list->first->rootPtr), variable);
                //free(variable);



                    //ocakavam argument <params_n>
                data->errorValue = read_token(token);
                checkError(data);


                fParams_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);            
            }
            else{
                fprintf(stderr, "Error in state %d, fParams_n\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
        }
        else{
            fprintf(stderr, "Error in state %d, fParams_n\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else {
        fprintf(stderr, "Error in state %d, fParams_n\n", *state);
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
        TNode *variable = createVarNode(token->value, 0, pole, &(data->errorValue), data->specialIDNumber);
        //printf("name; %s, specialID: %d\n", variable->ID, variable->var->specialID);
        checkError(data);

        data->funkcia->param_types = malloc(sizeof(int)*15);
        if(data->funkcia->param_types == NULL){
            data->errorValue = 99;
            checkError(data);
        }
        data->funkcia->param_length = 0;

            //generovanie kodu pre parametre definicie funkcie
        PARAMETERS(data->funkcia->ID, token->value, 0, INT2STRING(data->specialIDNumber));
        

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
            //free(variable);


                //ocakavam argument <params_n>
            data->errorValue = read_token(token);
            checkError(data);

            fParams_n(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            data->premenna = NULL;

        }else{
            fprintf(stderr, "Error in state %d, fParams\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else{
        fprintf(stderr, "Error in state %d, fParams\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}

void fArgs(Token *token, enum STATE *state, Data_t *data, char *functionName){
    
    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
    }
    else if(!strcmp(token->name,",")){

            //ocakavam argument <arg>
        data->errorValue = read_token(token);
        checkError(data);

        //priprava na typovu kontrolu a pocet parametrov
        if(strcmp(data->leaf->ID, "write")){
            data->checkDataType = true;
            if(data->leaf->func->param_length == data->indexType){
                fprintf(stderr, "ERROR - nadmerny pocet parametrov funkcie\n");
                data->errorValue = 5;
                checkError(data);
            }
            data->dataType = data->leaf->func->param_types[data->indexType];
        }else{
            data->checkDataType = false;
        }

        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //generovanie kodu pre argumenty funkcie
        if(strcmp(functionName, "write")){    
            DEFINE_ARG(&(data->string),data->leaf->ID, INT2STRING(data->indexType), data->whileDeep);
            INIT_ARG(&(data->string), data->whileDeep, data->leaf->ID, INT2STRING(data->indexType));
        }
        else{
            CALL_FUNC_WRITE(&(data->string), data->whileDeep);

        }


        if(strcmp(data->leaf->ID, "write")){
            data->indexType++;
        }
        data->checkDataType = false;

            //Nesmusim nacitat dalsi token, pretoze precedencna analyza v <exp> fExp nacita token, a podla neho sa rozhodne ci ma prestat nacitavat vyraz
            // Ak nacita ')', znaci to EPSILON PRECHOD v <args>, ak nacita ',' tak to znaci dalsie argumenty
            //Token vrati precedencna analyza v premennej 'token'
        data->errorCode = 5;
        fArgs(token, state, data, functionName);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        fprintf(stderr, "Error in state %d, fArgs\n", *state);
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

void fArg(Token *token, enum STATE *state, Data_t *data, char *functionName){

    if(!strcmp(token->name,")")){
        //nacitali sme EPSILON
        //Nacitane: ID ()
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#") || !strcmp(token->name,"(") || (!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){

        if(!strcmp(token->name,"identifier")){
            if(isFunction(data->list->last->rootPtr, token->value)){
                fprintf(stderr, "Error in state %d, fArg, ID of function in <arg>\n", *state);
                data->errorValue = 2;
                checkError(data);

            }

            TNode * element = searchFrames(data->list, token->value);
            if(element == NULL){
                fprintf(stderr, "\nERROR - volanie neexistujuceho identifikatoru10\n");
                data->errorValue = 3;
                checkError(data);
            }
        }

            //priprava na typovu kontrolu a pocet parametrov
            //pripad, kedy sa ID != write
        if(strcmp(data->leaf->ID, "write")){
            data->checkDataType = true;
            if(data->leaf->func->param_length == data->indexType){
                fprintf(stderr, "ERROR - nadmerny pocet parametrov funkcie\n");
                data->errorValue = 5;
                checkError(data);
            }
            data->dataType = data->leaf->func->param_types[data->indexType];
        }else{
            data->checkDataType = false;
        }

        data->errorCode = 5;

            //Ocakavam argument <arg>
        fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            //inkrementacia indexu, kt sa pouziva ako index v poli datovych typov funkcie

            //generovanie kodu pre argumenty funkcie
        if(strcmp(functionName, "write")){
            DEFINE_ARG(&(data->string),data->leaf->ID, INT2STRING(0), data->whileDeep);
            INIT_ARG(&(data->string), data->whileDeep, data->leaf->ID, INT2STRING(0));
        }
        else{
            CALL_FUNC_WRITE(&(data->string), data->whileDeep);
        }



        if(strcmp(data->leaf->ID, "write")){
            data->indexType++;
        }
        data->checkDataType = false;


            //Nesmusim nacitat dalsi token, pretoze precedencna analyza v <exp> fExp nacita token, a podla neho sa rozhodne ci ma prestat nacitavat vyraz
            // Ak nacita ')', znaci to EPSILON PRECHOD v <args>, ak nacita ',' tak to znaci dalsie argumenty
            //Token vrati precedencna analyza v premennej 'token'
        data->errorCode = 5;
        fArgs(token, state, data, functionName);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data); 
    }
    else{
        fprintf(stderr, "Error in state %d, fArg\n", *state);
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
        //free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;

        
    }
    else if(!strcmp(token->name,"-1") && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 2. 
        //free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;
        
    }
    else if(*state == params_n && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
        //Znaci EPSILON prechod do <st-list>, pravidlo 4.
        //free(data->funkcia->ret_types);
        data->funkcia->ret_types = NULL;
        data->funkcia->ret_length = 0;
        
    }
    else{
        fprintf(stderr, "Error in state %d, fRet_type\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
}


/**
 * @brief Function for reallocating array of types
 * 
 * @param data 
 * @param array 
 */
void reallocArray(Data_t *data, int *array){
    int *tmp = realloc (array, 25*sizeof(int));
    if(tmp == NULL){
        data->errorValue = 99;
        checkError(data);
    }
    array = tmp;
}


/**
 * @brief Function for nondeterminal Type in LL gramar
 * 
 * @param token Pointer to token
 * @param state Pointer to Enum of states
 * @param data Pointer to data structure
 */

void fType(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number") || !strcmp(token->value,"nil")){
            if(*state == par_type){
                if(!strcmp(token->value,"integer"))
                    data->funkcia->param_types[data->funkcia->param_length] = 0;
                else if (!strcmp(token->value,"number"))
                    data->funkcia->param_types[data->funkcia->param_length] = 1;
                else if (!strcmp(token->value,"string"))
                    data->funkcia->param_types[data->funkcia->param_length] = 2;
                else if (!strcmp(token->value,"nil"))
                    data->funkcia->param_types[data->funkcia->param_length] = 3;
                data->funkcia->param_length++;
                if(data->funkcia->param_length == 15){
                    reallocArray(data, data->funkcia->param_types);
                    data->funkcia->param_length = 25;
                }
                //TODO realloc
            }else if(*state == ret_type || *state == params_n ){
                if(!strcmp(token->value,"integer"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 0;
                else if (!strcmp(token->value,"number"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 1;
                else if (!strcmp(token->value,"string"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 2;
                else if (!strcmp(token->value,"nil"))
                    data->funkcia->ret_types[data->funkcia->ret_length] = 3;
                data->funkcia->ret_length++;

                if(data->funkcia->ret_length == 15){
                    reallocArray(data, data->funkcia->ret_types);
                    data->funkcia->ret_length = 25;
                }
                //TODO realloc
            }else if(*state == params){
                if(!strcmp(token->value,"integer"))
                    data->premenna->dataType = 0;
                else if (!strcmp(token->value,"number"))
                    data->premenna->dataType = 1;
                else if (!strcmp(token->value,"string"))
                    data->premenna->dataType = 2;
                else if (!strcmp(token->value,"nil"))
                    data->premenna->dataType = 3;

            }
    }
    else{
        fprintf(stderr, "Error in state %d, fType\n", *state);
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
            // fprintf(stderr, "name : %s\n", token->name);
            // fprintf(stderr, "value : %s\n", token->value);

            

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
            fprintf(stderr, "Error in state %d, fTypes\n", *state);
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
   // fprintf(stderr, "name : %s\n", token->name);
   // fprintf(stderr, "value : %s\n", token->value);

     if(!strcmp(token->name,")")){
            //Nacitane: global ID : function ()
            //parameter funkcie je prazdny, nie je tam nic 
            //free(data->funkcia->param_types);
            data->funkcia->param_types = NULL;
            data->funkcia->param_length = 0;

            
    }
    else if(!strcmp(token->name,"keyword") && (!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number") || !strcmp(token->value,"nil")) ){
                //parameter je jeden z datovych typov
            if(!strcmp(token->value,"integer"))
                data->funkcia->param_types[data->funkcia->param_length] = 0;
            else if (!strcmp(token->value,"number"))
                data->funkcia->param_types[data->funkcia->param_length] = 1;
            else if (!strcmp(token->value,"string"))
                data->funkcia->param_types[data->funkcia->param_length] = 2;
            else if (!strcmp(token->value,"nil"))
                data->funkcia->param_types[data->funkcia->param_length] = 3;


            data->funkcia->param_length++;
            //TODO realloc
            if(data->funkcia->param_length == 15){
                reallocArray(data, data->funkcia->param_types);
                data->funkcia->param_length = 25;
            }
            

            //if(funkcia->param_length == LENGTH(funkcia->param_types)){
             //   fprintf(stderr, "HELLO\n");
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
            fprintf(stderr, "Error in state %d, fPar_type\n", *state);
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
                
                


             //fprintf(stderr, "name : %s\n", token->name);
             //fprintf(stderr, "value : %s\n", token->value);
            
            if(strcmp(token->name,"identifier")){
                fprintf(stderr, "Error in state %d, ID not included\n", *state);
                data->errorValue = 2;
                checkError(data);
                
            }

                //zistenie, ci sa dane ID uz vyskytuje v tabulke alebo nie
            if (search(data->list->last->rootPtr, token->value) != NULL){
                data->errorValue = 3;
                fprintf(stderr, "ERROR - Rovnake meno funkcie\n");
                checkError(data);
            }
                //nacitane: global ID

            Function_t *funkcia = malloc(sizeof(Function_t));
            data->funkcia = funkcia;
            data->funkcia->param_length = 0;
            data->funkcia->ret_length = 0;
            /*funkcia->ID = malloc(sizeof(char)*strlen(token->value));
            if(funkcia->ID == NULL){
                data->errorValue = 99;
                checkError(data);
            }
            memset(funkcia->ID, '\0',strlen(token->value));*/
            funkcia->ID = token->value;
            //fprintf(stderr, "token: %s\n", token->value);
            //fprintf(stderr, "funkcia: %s\n", funkcia->ID);
            


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
                    //data->specialIDNumber = 0;
                        //Ocakavam '('
                    data->errorValue = read_token(token);
                    checkError(data);

                    if(!strcmp(token->name,"(")){
                        //Nacitane: global ID : function (
                        
                        funkcia->param_types = malloc(sizeof(int)*15);
                        if(funkcia->param_types == NULL){
                            //free(funkcia->ID);
                            //free(funkcia);
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
                            //free(funkcia->param_types);
                            //free(funkcia->ID);
                            //free(funkcia);
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
                        //free(funkcia->ID);
                        //free(funkcia->param_types);
                        //free(funkcia->ret_types);
                        //free(funkcia);
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
                        fprintf(stderr, "Error in state %d, \'(\' not included\n", *state);
                        data->errorValue = 2;
                        checkError(data);
                    }
                }
                else{
                    fprintf(stderr, "Error in state %d, function keyword not included\n", *state);
                    data->errorValue = 2;
                    checkError(data);                   
                }
            }
            else{
                fprintf(stderr, "Error in state %d, : not included\n", *state);
                data->errorValue = 2;
                checkError(data);
            }
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"function")){
        //data->specialIDNumber = 0;
        //Nacitane: function, pravidlo 4.

            //Ocakavam ID
        data->errorValue = read_token(token);
        checkError(data);

            //nacitane: function ID
        if(strcmp(token->name,"identifier")){
            fprintf(stderr, "Error in state %d, ID not included\n", *state);
            data->errorValue = 2;
            checkError(data);    
        }


        TNode * element = search(data->list->last->rootPtr, token->value);
        if (element != NULL){
            if(!(element->function)){
                fprintf(stderr, "ERROR - Existujuca ina premenna\n");
                data->errorValue = 3;
                checkError(data);
            }
            else if((element->func->defined)){
                fprintf(stderr, "ERROR - Funkcia je uz definovana\n");
                data->errorValue = 3;
                checkError(data);
            }
        }

            //generovanie zaciatku funkcie
        FUNC_START(token->value);


        Function_t *funkcia = malloc(sizeof(Function_t));
        data->funkcia = funkcia;
        data->funkcia->param_length = 0;
        data->funkcia->ret_length = 0;
        /*data->funkcia->ID = malloc(sizeof(char)*strlen(token->value));
        if(data->funkcia->ID == NULL){
            data->errorValue = 99;
            checkError(data);
        }*/

        data->funkcia->ID = token->value;

    

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
                //free(data->funkcia->param_types);
                //free(data->funkcia->ID);
                //free(data->funkcia);
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

                //ulozenie returnovych typov do pomocneho pola, ktory v returne budem kontrolova
            data->arrayTypeLength = data->funkcia->ret_length;
            data->arrayType = malloc(sizeof(int)*(data->arrayTypeLength+1));
            if(data->arrayType == NULL){
                data->errorValue = 9;
                checkError(data);
            }
            data->arrayType = data->funkcia->ret_types;

                //generovanie returnov funkcie
            DEF_RETVALS(data->funkcia->ret_length);



            //Vkladanie Function_t do symtable


                //ZOZNAM RETURN TYPOV
           
            *state = st_list;
                //Token mam nacitany z fRet_type, na zaklane neho som urcoval EPSILON prechod
             fSt_list(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            
            deleteFirst(data->list);

            //TODO chyba mi tu PUSH returnovych hodnot
                //generovanie kodu ukoncenie funkcie
            FUNC_END(data->funkcia->ID,data->funkcia->ret_length );
            
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
            fprintf(stderr, "Error in state %d, \'(\' not included\n", *state);
            data->errorValue = 2;
            checkError(data);   
        }
    }
    else if(!strcmp(token->name,"identifier")){
        //Nacitane: ID, pravidlo 5.
        //TODO zistit ci je funkcia aspon deklarovana
        //fprintf(stderr, "\ntoken->name: %s, token->value: %s\n", token->name, token->value);


        TNode * element = search(data->list->last->rootPtr, token->value);
        if(element == NULL){
            fprintf(stderr, "\nERROR - volanie neexistujucej funkcie2\n");
            data->errorValue = 3;
            checkError(data);
        }

            //generovanie volania funkcie
        CREATEFRAME(&(data->string), data->whileDeep);

            //Ocakavam '('
        data->errorValue = read_token(token);
        checkError(data);
        
        if(!strcmp(token->name,"(")){
            //Nacitane: ID (
                //predanie elementu do data->leaf pre typovu kompatibilitu
            data->leaf = element;
            data->indexType = 0;
            //printf("\nDLZKA RETAZCKA PARAMETROV: %d\n",data->leaf->func->param_length);

            data->errorValue = read_token(token);
            checkError(data);
            
            *state = arg;
                //Ocakavam argument

            fArg(token, state, data, element->ID);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            data->errorCode = 4;

            if(data->leaf->func->param_length != data->indexType){
                fprintf(stderr, "ERROR - zly pocet parametrov volania funkcie\n");
                data->errorValue = 5;
                checkError(data);
            }

                //generovanie volania funkcie
            if(strcmp(element->ID, "write")){
                CALL_FUNC(&(data->string), data->whileDeep, element->ID);
            }
                //generovanie navratovych hodnot funkcie
                //TODO generovanie kodu POPS do nejakej Void premennej
            for(int i = 0; i < data->leaf->func->ret_length; i++){
                POPS_INFINITE(&(data->string), data->whileDeep);
            }
            
            
                // pokracovanie do prog_con
            *state = prog_con;    
            data->errorValue = read_token(token);
            checkError(data);
                //vycistenie ukazatela na pomocny TNode
            data->indexType = 0;
            data->leaf = NULL;

            fProg_con(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);        
        }
        else{
            fprintf(stderr, "Error in state %d, \'(\' not included\n", *state);
            data->errorValue = 2;
            checkError(data);
        }
    }
    else if(!strcmp(token->name,"-1")){
        //Token je to EOF, znaeci EPSILON
        //Nacitane: EPSILON, pravidlo 2.   
    }
    else{
        fprintf(stderr, "Error in state %d, fProg_con\n", *state);
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
            fprintf(stderr, "Error in state %d, fExp\n", *state);
            data->errorValue = 7;
            checkError(data);   
        }
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"number") || !strcmp(token->name,"identifier") || !strcmp(token->name,"#")  || !strcmp(token->name,"(") || (!strcmp(token->name,"keyword") && !strcmp(token->value,"nil"))){
        //TODO ALL
            //TODO treba do podmienky zahrnut NIL
            //Check if is Expression
            //if Expression and *state = arg then ERROR;
            //if Function ID and *state = arg then ERROR;
            //Call precedence analysis
            
            //TODO treba sa dohodnut na returnoch, precedencna analyza by mala nacitat dalsi token a podla abecedy usudit, kedy treba prestat nacitavat
            //TODO Parser uz nenacitava dalsi token, funkcie pocitaju s tym, ze sa z precedencnej analyzi vrati v premennej 'token' dalsi nacitany token
        //printf("checkDataType: %d, dataType: %d\n", data->checkDataType, data->dataType);
        exp_analysator(data);
    }
    else if(*state == arg && !strcmp(token->name,")")){
            //situacia, ak by som v argumetne dostal nedokonceny argument, takze napr: (x,5,), to znamena ze by to koncilo ciarkou co je semanticka chyba
        fprintf(stderr, "Error in state %d, fExp\n", *state);
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
        fprintf(stderr, "Error in state %d, keyword require not included\n", *state);
        data->errorValue = 2;
        checkError(data);   
    }  

}   




int main(){

    
    Data_t *data = malloc(sizeof(Data_t));
    //osetrenie chyby mallocu
    data->isIf = 0;
    data->errorCode = 4;
    data->specialIDNumber = 0;
    data->whileDeep = 0;
    data->errorValue = 0;
    data->leaf = NULL;
    data->labelCounter = 0;
    data->string = (char *)malloc(sizeof(char));
    if(data->string == NULL){
        data->errorValue = 99;
        checkError(data);
    }

    data->dataType = 0;
    data->checkDataType = false;
    data->indexType = 0;

    Tframe_list *frames = (Tframe_list*)malloc(sizeof(Tframe_list));
    if(frames == NULL){
        data->errorValue = 99;
        checkError(data);
    }
    initList(frames);
    TNode *rootPtr = NULL;
    insertFirst(frames, true, rootPtr);

    data->list = frames;

    //insertFirst(frames, true, rootPtr);
    //deleteFirst(data->list);

    
        //Idem vytvarat a vkladat vestavene funkce
    data->errorValue = createInbuildFunctions(data);
    checkError(data);
    
    
    enum STATE state = prog;

        //generovanie vestavenych funkcii
    START_AND_BUILTIN_FUNCTIONS();


    Token *token = malloc(sizeof(Token));
    if(token == NULL){
        data->errorValue = 99;
        checkError(data);
    }
    
    data->token = token;

    data->errorValue = read_token(token);
    checkError(data);


    synAnalys(token, &state, data);
    checkError(data);
    
    fprintf(stderr, "Syn analys: %d\n", data->errorValue);  
    free(data->string);

    free(token);
    free(data);


    return 0;
}
