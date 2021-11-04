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


typedef struct sData{
    
    bool isError;
    int errorValue;

} Data_t;

analysRet fSt_list(Token *token, enum STATE *state, Data_t *data);
analysRet fParams_n(Token *token, enum STATE *state, Data_t *data);
analysRet fParams(Token *token, enum STATE *state, Data_t *data);
analysRet fArgs(Token *token, enum STATE *state, Data_t *data);
analysRet fArg(Token *token, enum STATE *state, Data_t *data);
analysRet fRet_type(Token *token, enum STATE *state, Data_t *data);
analysRet fType(Token *token, enum STATE *state, Data_t *data);
analysRet fTypes(Token *token, enum STATE *state, Data_t *data);
analysRet fPar_type(Token *token, enum STATE *state, Data_t *data);
analysRet fProg_con(Token *token, enum STATE *state, Data_t *data);
analysRet fExp(Token *token, enum STATE *state, Data_t *data);
analysRet synAnalys(Token *token, enum STATE *state, Data_t *data);




int checkError(Data_t *data){
    if(data->errorValue == 1){
        fprintf(stderr, "Lexical analysis Error\n");
        return LEX_ERROR;
    }
    else if(data->errorValue == 2){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 3){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 4){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 5){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 6){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 7){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 8){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if(data->errorValue == 9){
        fprintf(stderr, "Syntax Error\n");
        return SYNTAX_ERROR;
    }
    else if (data->errorValue == 99){
        fprintf(stderr, "Internal Error\n");
        return INTERNAL_ERROR;
    }else
        return 0;
}



analysRet fSt_list(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    

    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
        //Narazil som na EPSILON prechod
        return returnValue;
    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"if")){
        
       


    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"while")){
        
       //TODO


    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"local")){
        
       //TODO


    }
    else if(!strcmp(token->name,"keyword") && !strcmp(token->value,"return")){
        
       //TODO


    }
    else if(!strcmp(token->name,"identifier")){
        
       //TODO

    }
    else{
        printf("Error in state %d, fSt_list\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
    




    return returnValue;
}





analysRet fParams_n(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    

    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        return returnValue;
    }
    else if(!strcmp(token->name,",")){
            //Ocakavam ID
       data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,"identifier")){
            //Ocakavam ':'
           data->errorValue = read_token(token);
            checkError(data);


            if(!strcmp(token->name,":")){
                    //ocakavam argument <type>
               data->errorValue = read_token(token);
                checkError(data);

                returnValue = fType(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);


                    //ocakavam argument <params_n>
               data->errorValue = read_token(token);
                checkError(data);

                returnValue = fParams_n(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);

                return returnValue;

            }
            else{
                printf("Error in state %d, fParams_n\n", *state);
                returnValue.SynCorrect = 2;
                return returnValue;
            }
        }
        else{
            printf("Error in state %d, fParams_n\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }
        return returnValue;
    }
    else {
        printf("Error in state %d, fParams_n\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }

    return returnValue;
}



analysRet fParams(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        return returnValue;
    }
    else if(!strcmp(token->name,"identifier")){
        //ocakavam argument ':'
       data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,":")){
                //ocakavam argument <type>
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fType(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);



                //ocakavam argument <params_n>
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fParams_n(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


            return returnValue;

        }else{
            printf("Error in state %d, fParams\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }

        return returnValue;
    }
    else{
        printf("Error in state %d, fParams\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }


return returnValue;
}

analysRet fArgs(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;


    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        return returnValue;
    }
    else if(!strcmp(token->name,",")){

        //ocakavam argument <arg>
       data->errorValue = read_token(token);
        checkError(data);

        returnValue = fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);


        //ocakavam <args>
        //WARNING, tu by som nevoval read_token, lebo mi precedencna analyza vrati uz ciarku
       data->errorValue = read_token(token);
        checkError(data);

        returnValue = fArgs(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, fArgs\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }

    return returnValue;


}


analysRet fArg(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;


    if(!strcmp(token->name,")")){
        //nacitali sme EPSILON
        //Nacitane: ID ()
        return returnValue;
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"float") || !strcmp(token->name,"identifier")){

        //Ocakavam argument <arg>
        returnValue = fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        //ocakavam <args>
       data->errorValue = read_token(token);
        checkError(data);

        returnValue = fArgs(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);


        return returnValue;
    }
    else{
        printf("Error in state %d, fArg\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }

    return returnValue;
}

analysRet fRet_type(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    
    if(!strcmp(token->name,":")){
    //Nacitane: global ID : function(<par-type>) : 
       
        //ocakavam <type>
       data->errorValue = read_token(token);
        checkError(data);
        //Zanorenie sa do fType

        returnValue = fType(token, state, data);
         //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
        //Nacitane: global ID : function(<par-type>) : integer
        

         //ocakavam <types>
       data->errorValue = read_token(token);
        checkError(data);
        
        //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
        returnValue = fTypes(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

        //Nacitane: global ID : function(<par-type>) : integer, string
    
    }
    else if(((!strcmp(token->name,"keyword") && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))) || !strcmp(token->name,"identifier")) && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 3., 4. a 5. 
        

        return returnValue;
    }
    else if(!strcmp(token->name,"-1") && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 2. 
        return returnValue;
    }
    else if(*state == params && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
        //Znaci EPSILON prechod do <st-list>, pravidlo 4.
        return returnValue;
    }
    else{
        printf("Error in state %d, fRet_type\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
    
    return returnValue;
}


analysRet fType(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    if(!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")){
            return returnValue;
    }
    else{
        printf("Error in state %d, fType\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
}



analysRet fTypes(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

        if(!strcmp(token->name,")") && *state == par_type){
            //Nacitane: global ID : function (string,integer) 

            //parameter funkcie je prazdny, nie je tam nic 
            //riesim parameter funkcie a momentalne je token v parmetri brany ako EPSILON
            return returnValue;
        }
        else if(!strcmp(token->name,",")){
            //Nacitane: global ID : function (string, 
             //ocakavam <type>
           data->errorValue = read_token(token);
            checkError(data);

            //Zanorenie sa do fType
            returnValue = fType(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            //Nacitane: global ID : function (string, integer  / global ID : function (string,integer) : integer, integer



             //ocakavam <types>
           data->errorValue = read_token(token);
            checkError(data);

            
            //Zanorenie do stavu fTypes, rekurzivne volanie sameho seba
            //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
            returnValue = fTypes(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            //Nacitane: global ID : function (string, integer,number, / global ID : function (string,integer) : integer, integer, string, 
        }
        else if((*state == ret_type && !strcmp(token->name,"keyword")) && (!strcmp(token->value,"global") || !strcmp(token->value,"function"))){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 3. a 4.
            // printf("name : %s\n", token->name);
            // printf("value : %s\n", token->value);

             //TODO vratit TOKEN, treba nejako

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
        else if(*state == params && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
            //Znaci EPSILON prechod od <st-list>, pravidlo 4.
            return returnValue;
        }
        else{
            printf("Error in state %d, fTypes\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    return returnValue;
}



analysRet fPar_type(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    

   // printf("name : %s\n", token->name);
   // printf("value : %s\n", token->value);

     if(!strcmp(token->name,")")){
            //Nacitane: global ID : function ()
            //parameter funkcie je prazdny, nie je tam nic 
            return returnValue;
        }
        else if(!strcmp(token->name,"keyword") && (!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")) ){
            //parameter je jeden z datovych typov

            //ocakavam <types>
           data->errorValue = read_token(token);
            checkError(data);

            //Zanorenie sa do funkcie fTypes, kde budem riesit datove typy
            returnValue = fTypes(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
            //Nacitane: global ID : function (string, integer)
        }
        else{
            printf("Error in state %d, fPar_type\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    return returnValue;
}


analysRet fProg_con(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"global")){
        //Riesime pravidlo 3. kedy ideme inizializovat globalnu funkciu
        //nacitane: global, pravidlo 3.
              
            //nacitanie ID funkcie
            //TODO pridaj do tabulky symbolov
           data->errorValue = read_token(token);
            checkError(data);
            //nacitane: global ID

             //printf("name : %s\n", token->name);
             //printf("value : %s\n", token->value);
            
            if(strcmp(token->name,"identifier")){
                printf("Error in state %d, ID not included\n", *state);
                returnValue.SynCorrect = 2;
                return returnValue;
            }


            
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
                        
                        //Ocakavam <par-type>
                       data->errorValue = read_token(token);
                        checkError(data);
                        
                        //Zmena stavu
                        *state = par_type;
                        returnValue = fPar_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(data);
                        //Nacitane: global ID : function(<par-type>)


                        //Ocakavam <ret-type>
                       data->errorValue = read_token(token);
                        checkError(data);
                        
                        //Zmena stavu
                        *state = ret_type;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
                        returnValue = fRet_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(data);
                        //Nacitane: global ID : function(<par-type>)<ret-type>


                        //Ocakavam <prog_con>                        
                        //Zmena stavu
                        *state = prog_con;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x returnValue = synAnalys(token, state)
                        returnValue = fProg_con(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(data);
                        //Nacitane: global ID : function(<par-type>)<ret-type><prog-con>
                        
                    }
                    else{
                        printf("Error in state %d, \'(\' not included\n", *state);
                        returnValue.SynCorrect = 2;
                        return returnValue;
                    }

                }
                else{
                    printf("Error in state %d, function keyword not included\n", *state);
                    returnValue.SynCorrect = 2;
                    return returnValue;
                }

            }
            else{
                printf("Error in state %d, : not included\n", *state);
                returnValue.SynCorrect = 2;
                return returnValue;
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
            returnValue.SynCorrect = 2;
            return returnValue;
        }



            //Ocakavam '('
       data->errorValue = read_token(token);
        checkError(data);
            //nacitane: function ID (
        if(!strcmp(token->name,"(")){
                
                //*state = params;

                //Ocakavam <params>
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fParams(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            //TU JE ZOZNAM PARAMETROV

            //Tento stav simuluje pravidlo 4., teda definiciu funkcie aj s telom
            //Stav je tu preto, aby som v <ret-type> dokazal rozoznat EPSILON prechod do <st-list>
            *state = params;

                //Ocakavam <ret-type>
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fRet_type(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


            //ZOZNAME RETURN TYPOV
            
            *state = st_list;
            //Token mam nacitany z fRet_type, na zaklane neho som urcoval EPSILON prechod
            returnValue = fSt_list(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);











                //Zaver
            *state = prog_con;

            //Ocakavam <prog_con>, musim nacitat token lebo <st-list> konicl v EPSILON prechode a tym bol keyword 'end' danej funkcie
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fProg_con(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);



            return returnValue;
        }
        else{
            printf("Error in state %d, \'(\' not included\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }

        return returnValue;

    }
    else if(!strcmp(token->name,"identifier")){
        //Nacitane: ID, pravidlo 5.

        //Ocakavam '('
       data->errorValue = read_token(token);
        checkError(data);
        
        if(!strcmp(token->name,"(")){
        //Nacitane: ID (

           data->errorValue = read_token(token);
            checkError(data);


            *state = arg;
            //Ocakavam argument

            returnValue = fArg(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


            //TODO pokracovanie do prog_con

            *state = prog_con;    
           data->errorValue = read_token(token);
            checkError(data);

            returnValue = fProg_con(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);        
        }
        else{
            printf("Error in state %d, \'(\' not included\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }
    }
    else if(!strcmp(token->name,"-1")){
        //Token je to EOF, znaeci EPSILON
        //Nacitane: EPSILON, pravidlo 2.
        return returnValue;
    }
    else{
        printf("Error in state %d, fProg_con\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
    return returnValue;
}



analysRet fExp(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;

    //TODO CALL precedencnu analyzu
    //TODO check token in symtable
        
    

    if(*state == prog){
        if(!strcmp(token->name,"string") && !strcmp(token->value,"ifj21")){
            returnValue.SynCorrect = 0;
            return returnValue;
        }
        else{
            printf("Error in state %d, fExp\n", *state);
            returnValue.SynCorrect = 2;
            return returnValue;
        }

    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"float") || !strcmp(token->name,"identifier")){
        //TODO ALL
            //TODO treba do podmienky zahrnut NIL
            //Check if is Expression
            //if Expression and *state = arg then ERROR;
            //if Function ID and *state = arg then ERROR;
            //Call precedence analysis
        return returnValue;

    }
    //TODO SKONTROLUJ, nesedi mi to
    else if(*state == arg && !strcmp(token->name,")")){
        //situacia, ak by som v argumetne dostal nedokonceny argument, takze napr: (x,5,), to znamena ze by to koncilo ciarkou co je semanticka chyba
        printf("Error in state %d, fExp\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
    
    //TODO poriesit ostatne znaky ako napriklad operatory 
    returnValue;
}


analysRet synAnalys(Token *token, enum STATE *state, Data_t *data){
    
    analysRet returnValue;
    returnValue.SynCorrect = 0;
    
    //STRCMP -> ak sa stringy rovnaju, tak je return 0, preto v podmienkach !
    //Inizializovany stav, state->prog
    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"require")){
        //nacitanie dalsieho tokenu
       data->errorValue = read_token(token);
        data->isError = checkError(data);

            

        
        returnValue = fExp(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
            

        //Natahanie dalsieho tokenu
       data->errorValue = read_token(token);
        checkError(data);

        //Zmena stavu a rekurzovne zanorenie
        *state = prog_con;
        returnValue = fProg_con(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);
    }
    else{
        printf("Error in state %d, keyword require not included\n", *state);
        returnValue.SynCorrect = 2;
        return returnValue;
    }
        
    return returnValue;
}   




int main(){

    enum STATE state = prog;
    //Osetrenie chyby mallocu

    Data_t *data = malloc(sizeof(Data_t));
    //osetrenie chyby mallocu
    
    data->errorValue = 0;
    data->isError = false;

    //Sluzi na nacitanie
    


    Token *token = malloc(sizeof(Token));
    //TODO osetri malloc error

    data->errorValue = read_token(token);
    data->isError = checkError(data);


    analysRet returnValue = synAnalys(token, &state, data);
    data->isError = checkError(data);
    
    printf("Syn analys: %d", data->errorValue);  

    free(token);
    free(data);


    return 0;
}