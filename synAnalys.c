#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "scanner.c"
#include "error.h"




enum STATE {assign, assigns, arg, args, exp, item, item_n, init, init_value, prog, prog_con, par_type, ret_val, ret_type, st_list, type, types, value, values, params, params_n};



typedef struct sData{
    
    bool isError;
    int errorValue;
    Token *token;

} Data_t;


void fAssigns(Token *token, enum STATE *state, Data_t *data);
void fAssign(Token *token, enum STATE *state, Data_t *data);
void fItem(Token *token, enum STATE *state, Data_t *data);
void fSt_list(Token *token, enum STATE *state, Data_t *data);
void fParams_n(Token *token, enum STATE *state, Data_t *data);
void fParams(Token *token, enum STATE *state, Data_t *data);
void fArgs(Token *token, enum STATE *state, Data_t *data);
void fArg(Token *token, enum STATE *state, Data_t *data);
void fRet_type(Token *token, enum STATE *state, Data_t *data);
void fType(Token *token, enum STATE *state, Data_t *data);
void fTypes(Token *token, enum STATE *state, Data_t *data);
void fPar_type(Token *token, enum STATE *state, Data_t *data);
void fProg_con(Token *token, enum STATE *state, Data_t *data);
void fExp(Token *token, enum STATE *state, Data_t *data);
void synAnalys(Token *token, enum STATE *state, Data_t *data);




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


void fAssigns(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,",")){

        //nacitam dalsi token, ocakavam <exp>
        data->errorValue = read_token(token);
        checkError(data);

        //TODO treba zistit ci je to identifikator funkcie alebo premennej
        //Ak je ID funkcie, tak problem, lebo je vo viacnasobnom priradeni ID funkcia, ktora vracia hodnotu
        //Ak je ID premennej, idem do funkcie <exp>
        //Ak je to int, float alebo string, volame <exp>
        //fExp(token, state, data);



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

void fAssign(Token *token, enum STATE *state, Data_t *data){
    //Ocakavam bud ID funkcie alebo <exp>(<exp> moze byt aj nazov premennej, treba zistit v symtable)
    //TODO zistit v symtable

    if(!strcmp(token->name,"identifier")){
        //TODO treba zistit ci je to identifikator funkcie alebo premennej, ak funkcie tak riesim (<arg>), ak premennej tak idem to <exp>
        /*TODO if(isFunction()){
            //Nacitanie '('
            data->errorValue = read_token(token);
            checkError(data);

            //Nacitanie 
            data->errorValue = read_token(token);
            checkError(data);

            fArg(token, state, data);

        }
        else{
            
            fExp(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            //nemusim nacitavat dalsi token, lebo mi to precedencna analyza vrati v ukazatali a premennej 'token'
            //precedencna analyza sa musi zastavit v momente, kedy narazi na ',' alebo EPSILON PRECHOD, v tomto pripade <st-list>
            //Az vo funkcii fAssings() zistim, ci sa jednalo o EPSILON prechod alebo o ',' a teda dalsie hodnoty do priradenia
            fAssigns(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);
        }*/

    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"float")){

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
        printf("Error in state %d, fSt_list\n", *state);
        data->errorValue = 2;
        checkError(data);


    }


}


void fItem(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"(")){
        //Ide argumnet funkcie, dany identifikator by mal patrit funkcii
        
        //Ocakavam token argumentu
        data->errorValue = read_token(token);
        checkError(data);

        fArg(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);

            //Som v stave, kedy mam nacitanu ')' argumentu a musim prejst do <st-list>
        data->errorValue = read_token(token);
        checkError(data);
        //Teraz som naictal dalsi token, v ktorom ocakavam <st-list>, spravil som to preto tu, pretoze musim pocitat situaciu spojenu s pravidlo 16. kde priradzujem a musim rozpoznat EPSILON prechod
        
   
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



    }
    else if(!strcmp(token->name,",")){
        //prikaz priradenia, viacnasobne priradenie

    }
    else{
        printf("Error in state %d, fSt_list\n", *state);
        data->errorValue = 2;
        checkError(data);

    }


}


void fSt_list(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,"keyword") && !strcmp(token->value,"end")){
        //Narazil som na EPSILON prechod
        
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

        //Ocakavam <item>
        data->errorValue = read_token(token);
        checkError(data);

        fItem(token, state, data);
            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
        checkError(data);


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





void fParams_n(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        
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

                 fType(token, state, data);
                    //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                checkError(data);


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



void fParams(Token *token, enum STATE *state, Data_t *data){    

    if(!strcmp(token->name,")")){
        //Narazil som na EPSILON prechod
        
    }
    else if(!strcmp(token->name,"identifier")){
        //ocakavam argument ':'
       data->errorValue = read_token(token);
        checkError(data);

        if(!strcmp(token->name,":")){
                //ocakavam argument <type>
           data->errorValue = read_token(token);
            checkError(data);

             fType(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


                //ocakavam argument <params_n>
           data->errorValue = read_token(token);
            checkError(data);

             fParams_n(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

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


void fArg(Token *token, enum STATE *state, Data_t *data){

    if(!strcmp(token->name,")")){
        //nacitali sme EPSILON
        //Nacitane: ID ()
        
    }
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"float") || !strcmp(token->name,"identifier")){

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
        

        
    }
    else if(!strcmp(token->name,"-1") && *state == ret_type){
        //Znaci EPSILON prechod do <prog_con>, pravidlo 2. 
        
    }
    else if(*state == params && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
        //Znaci EPSILON prechod do <st-list>, pravidlo 4.
        
    }
    else{
        printf("Error in state %d, fRet_type\n", *state);
        data->errorValue = 2;
        checkError(data);
        
    }
}


void fType(Token *token, enum STATE *state, Data_t *data){
    
    if(!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")){
            
    }
    else{
        printf("Error in state %d, fType\n", *state);
        data->errorValue = 2;
        checkError(data);
        
    }
}



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

             //TODO vratit TOKEN, treba nejako

            
        }
        else if(*state == ret_type && !strcmp(token->name,"identifier")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 5. 
            
        }
        else if(*state == ret_type && !strcmp(token->name,"-1")){
            //Znaci EPSILON prechod od <prog_con>, pravidlo 2.
            
        }
        else if(*state == params && (!strcmp(token->name,"identifier") || (!strcmp(token->name,"keyword") && (!strcmp(token->value,"if") || !strcmp(token->value,"while") || !strcmp(token->value,"local") || !strcmp(token->value,"return") || !strcmp(token->value,"end"))))){
            //Znaci EPSILON prechod od <st-list>, pravidlo 4.
            
        }
        else{
            printf("Error in state %d, fTypes\n", *state);
            data->errorValue = 2;
            checkError(data);   
        }
}



void fPar_type(Token *token, enum STATE *state, Data_t *data){
   // printf("name : %s\n", token->name);
   // printf("value : %s\n", token->value);

     if(!strcmp(token->name,")")){
            //Nacitane: global ID : function ()
            //parameter funkcie je prazdny, nie je tam nic 
            
        }
        else if(!strcmp(token->name,"keyword") && (!strcmp(token->value,"string") || !strcmp(token->value,"integer") || !strcmp(token->value,"number")) ){
            //parameter je jeden z datovych typov

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


void fProg_con(Token *token, enum STATE *state, Data_t *data){
    
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
                data->errorValue = 2;
                checkError(data);
                
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
                         fPar_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(data);
                        //Nacitane: global ID : function(<par-type>)


                        //Ocakavam <ret-type>
                       data->errorValue = read_token(token);
                        checkError(data);
                        
                        //Zmena stavu
                        *state = ret_type;
                        //TODO, treba fixnut prepisanie predcahdzajucim zanorenim, mam v tomto ife 2x  synAnalys(token, state)
                         fRet_type(token, state, data);
                            //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
                         checkError(data);
                        //Nacitane: global ID : function(<par-type>)<ret-type>


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

            //Ocakavam '('
        data->errorValue = read_token(token);
        checkError(data);
            //nacitane: function ID (
        if(!strcmp(token->name,"(")){
                
                //*state = params;

                //Ocakavam <params>
           data->errorValue = read_token(token);
            checkError(data);

             fParams(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);

            //TU JE ZOZNAM PARAMETROV

            //Tento stav simuluje pravidlo 4., teda definiciu funkcie aj s telom
            //Stav je tu preto, aby som v <ret-type> dokazal rozoznat EPSILON prechod do <st-list>
            *state = params;

                //Ocakavam <ret-type>
           data->errorValue = read_token(token);
            checkError(data);

             fRet_type(token, state, data);
                //kontrola, ci sa z rekurzie vratila chybova hodnota alebo nie
            checkError(data);


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
    else if(!strcmp(token->name,"string") || !strcmp(token->name,"int") || !strcmp(token->name,"float") || !strcmp(token->name,"identifier")){
        //TODO ALL
            //TODO treba do podmienky zahrnut NIL
            //Check if is Expression
            //if Expression and *state = arg then ERROR;
            //if Function ID and *state = arg then ERROR;
            //Call precedence analysis
            
            //TODO treba sa dohodnut na returnoch, precedencna analyza by mala nacitat dalsi token a podla abecedy usudit, kedy treba prestat nacitavat
            //TODO Parser uz nenacitava dalsi token, funkcie pocitaju s tym, ze sa z precedencnej analyzi vrati v premennej 'token' dalsi nacitany token

    }
    else if(*state == arg && !strcmp(token->name,")")){
        //situacia, ak by som v argumetne dostal nedokonceny argument, takze napr: (x,5,), to znamena ze by to koncilo ciarkou co je semanticka chyba
        printf("Error in state %d, fExp\n", *state);
        data->errorValue = 2;
        checkError(data);
    }
    
    //TODO poriesit ostatne znaky ako napriklad operatory 
    
}


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

    enum STATE state = prog;
    //Osetrenie chyby mallocu

    Data_t *data = malloc(sizeof(Data_t));
    //osetrenie chyby mallocu
    
    data->errorValue = 0;
    data->isError = false;  


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