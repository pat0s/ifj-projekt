/**
 * Project: IFJ21
 * @file expressions.h
 * 
 * @brief Precedence analysis
 * @author Dovhalenko Dmytro, xdovha00
 */


#include "expressions.h"
#include <string.h>
#include "error.h"
#include "code_generator.h"

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
};                                                                       //zasobnik

/**
 * @brief Rozpoznani znaku 
 * 
 * @returns 0 pro +-, 1 pro * / //, 2 pro .., 3 pro #, 4 pro identifikator cislo nebo retezec, 5 pro relacni operator
 * 6 pro (, 7 pro ),8 jiny znak
 */
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
 * @returns druhy index precendencni tabulky nebo -1 pri znaku se kterym nepracuje precendencna analyza
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
                        while(data->list->first != data->list->last){
                            deleteFirst(frames);
                        }
                        deleteFirst(frames);                  
                        fprintf(stderr, "ERROR - undef var\n");
                        free(token);
                        free(data);
                        exit(UNDEFINED_VAR);
            }
            int idtype = node->var->data_type;
            if(idtype==0){
                type="int"; 
            }
            else if(idtype==1){
                type="number"; 
            }
            else if(idtype==2){
                type="string";
            }
            else {
                type="nil";
            }
        }
        else{
            type=token->name;
            if(!strcmp(token->value,"0")||!strcmp(token->value,"0.0")||!strncmp(token->value,"0e",2)||!strncmp(token->value,"0E",2)){
                if (!is_empty(s)){

                    if(!strcmp(top(s),"/")||!strcmp(top(s),"//")){
                        //chyba deleni nulou;
                        while(data->list->first != data->list->last){
                            deleteFirst(data->list);
                        }
                            deleteFirst(data->list);                 
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
 * @returns 0 pri uspechu, -1 pri chybe
 */
int kontrola_typu(Stack *s,Data_t* data){
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
        if(!is_empty(s)){
            if(!strcmp(top_type(s),"int")){
                strcpy(type,"int");
                change_top_type(s,type);
                return 0;
            }
            else if(!strcmp(top_type(s),"number")){
                //zmenit typ posledniho vlozeneho na number
                TOP_I2F(&(data->string),data->whileDeep, INT2STRING(data->labelCounter));
                data->labelCounter++;
                strcpy(type,"number");
                change_top_type(s,type);
                return 0;
            }
            else{
                return -1;
            }
        }
        else {
            return -1;
        }
    }
    else if(!strcmp(top_type(s),"nil")){
        return -1;
    }
    else {
        pop(s);
        pop(s);
        if(!is_empty(s)){
            if(!strcmp(top_type(s),"number")){
                strcpy(type,"number");
                change_top_type(s,type);
                return 0;
            }
            else if(!strcmp(top_type(s),"int")){
                //zmenit typ predposledniho na number
                BEFORE_TOP_I2F(&(data->string),data->whileDeep, INT2STRING(data->labelCounter));
                data->labelCounter++;
                strcpy(type,"number");
                change_top_type(s,type);
                return 0;
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

/**
 * @brief Provede porovnani typu vysledku a ocekavaneho typu vyrazu
 * 
 * @returns chyba pri spatnem typu vysledku
 */
void kontrola_typu_vysledku(Stack* s,Data_t* data,Token* token){
    if(data->checkDataType==true){
        int typ_vyrazu;
        if(!strcmp(top_type(s),"int")){
            typ_vyrazu=0;
        }
        else if(!strcmp(top_type(s),"number")){
            typ_vyrazu=1;
        }
        else if(!strcmp(top_type(s),"string")){
            typ_vyrazu=2;
        }
        else if(!strcmp(top_type(s),"nil")){
            typ_vyrazu=3;
        }
        if(typ_vyrazu==3||typ_vyrazu==data->dataType){
            destroy(s);
            return;
        }
        else if(typ_vyrazu==0 && data->dataType==1){
            //pretypovat na number
            TOP_I2F(&(data->string),data->whileDeep, INT2STRING(data->labelCounter));
            data->labelCounter++;
            destroy(s);
            return;
        }
        else{
            fprintf(stderr, "ERROR - Chyba syntaktickeho analyzatoru zdola nahoru, nekompatybilita typu vyrazu\n");
            destroy(s);
            while(data->list->first != data->list->last){
                deleteFirst(data->list);
            }
            deleteFirst(data->list);
            free(token);
            free(data);
            exit(data->errorCode);
        }
    }
    else{
        destroy(s);
        return;
    }
}

/**
 * @brief Provede zmenu zasobniku podle pravidel
 * 
 * @returns 0 pri uspechu, -1 pri chybe;
 */
int do_reduc(Stack*s,Token* token,Token* generator_token,Data_t* data){
    if(!strcmp(top(s),"string")){                           //E -> string
        pop(s);
        push(s,"E","string");
        PUSHS(&data->string,data->whileDeep,generator_token,NULL,false);
    }
    else if(!strcmp(top(s),"int")){                         //E -> int
        pop(s);     
        push(s,"E","int");
        PUSHS(&data->string,data->whileDeep,generator_token,NULL,false);
    }
    else if(!strcmp(top(s),"number")){                      //E -> number
        pop(s);
        push(s,"E","number");
        PUSHS(&data->string,data->whileDeep,generator_token,NULL,false);
    }
    else if(!strcmp(top(s),"nil")){                         //E -> nil
        pop(s);
        push(s,"E","nil");
        PUSHS(&data->string,data->whileDeep,generator_token,NULL,false);
    }
    else if(!strcmp(top(s),"identifier")){                  //E -> id
        char type[7];
        strcpy(type,top_type(s));
        pop(s);
        bool kontrola_op_za=(!strcmp(token->name,"==")||!strcmp(token->name,"~="))&&is_empty(s);
        bool kontrola_op_pred=false;
        if(!is_empty(s)){
            kontrola_op_pred=(!strcmp(top(s),"==")||!strcmp(top(s),"~="))&&(strcmp(token->name,"+")&&strcmp(token->name,"-")&&strcmp(token->name,"*")&&strcmp(token->name,"/")&&strcmp(token->name,"//")&&strcmp(token->name,".."));
        }
        TNode *node=searchFrames(data->list,generator_token->value);
        if(node!=NULL){
            if(kontrola_op_za||kontrola_op_pred){
                //generovani bez osetreni nil
                PUSHS(&data->string,data->whileDeep,generator_token,INT2STRING(node->var->specialID),false);
            }
            else{
                //generovat s osetrenim nil
                kontrola_op_pred=false;
                if(!is_empty(s)){
                    kontrola_op_pred=!strcmp(top_type(s),"op");
                }
                int k=(rozpoznani_znaku(token->name));
                kontrola_op_za = (k==0||k==1||k==2||k==5||k==7);
                if(kontrola_op_pred||kontrola_op_za){
                  PUSHS(&data->string,data->whileDeep,generator_token,INT2STRING(node->var->specialID),true);  
                } 
                else{
                    PUSHS(&data->string,data->whileDeep,generator_token,INT2STRING(node->var->specialID),false);
                }
            }
        }
        else{
            return -1;
        }
        push(s,"E",type);
    }
    else if(!strcmp(top(s),"E")){                           //E -> #E
        if(!strcmp(top1(s),"#")){
            if(!strcmp(top_type(s),"string")){      //semanticka kontrola
                pop(s);
                pop(s);
                push(s,"E","int");
                STRLEN(&data->string,data->whileDeep);
            }
            else{
                return -1;                         //semanticka chyba
            }
        }
        else if(!strcmp(top1(s),"+")){                      //E -> E + E
            if(kontrola_typu(s,data)==0){
            //zavolat generovani +
            ADDS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
            
        }
        else if(!strcmp(top1(s),"-")){                       //E -> E - E
            int kontrol=kontrola_typu(s,data);                    
            if(kontrol==0){
            //zavolat generovani -
            SUBS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"*")){                      //E -> E * E
            if(kontrola_typu(s,data)==0){
            //zavolat generovani *
            MULS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"/")){                      //E -> E / E
            if(kontrola_typu(s,data)==0){
            //zavolat generovani /
            DIVS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"//")){                     //E -> E // E
            if(!strcmp(top_type(s),"int")){
                pop(s);
                pop(s);
                if(!strcmp(top_type(s),"int")){
                    //zavolat generovani //
                    IDIVS(&data->string,data->whileDeep);
                }
                else{
                    return -1;
                }
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"<")){                      //E -> E > E
            data->relation_operator_in_condition=true;
            if(kontrola_typu(s,data)==0){
            change_top_type(s,"bool");
            //zavolat generovani >
            LTS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),">")){                      //E -> E < E
            data->relation_operator_in_condition=true;
            if(kontrola_typu(s,data)==0){
            change_top_type(s,"bool");
            //zavolat generovani <
            GTS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"<=")){                     //E -> E <= E
            data->relation_operator_in_condition=true;
            if(kontrola_typu(s,data)==0){
            change_top_type(s,"bool");
            //zavolat generovani <=
            CONDITION_POPS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            CONDITION_PUSHS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            EQS(&data->string,data->whileDeep);
            CONDITION_PUSHS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            LTS(&data->string,data->whileDeep);
            ORS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),">=")){                     //E -> E >= E
            data->relation_operator_in_condition=true;
            if(kontrola_typu(s,data)==0){
            change_top_type(s,"bool");
            //zavolat generovani >=
            CONDITION_POPS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            CONDITION_PUSHS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            EQS(&data->string,data->whileDeep);
            CONDITION_PUSHS(&data->string,data->whileDeep,INT2STRING(data->specialIDNumber));
            GTS(&data->string,data->whileDeep);
            ORS(&data->string,data->whileDeep);
            }
            else{
                return -1;
            }
        }
        else if(!strcmp(top1(s),"==")){                     //E -> E == E
            data->relation_operator_in_condition=true;
            if(strcmp(top_type(s),"nil")){
                if(kontrola_typu(s,data)==-1){
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
            EQS(&data->string,data->whileDeep);
        }
        else if(!strcmp(top1(s),"~=")){                     //E -> E ~= E
            data->relation_operator_in_condition=true;
            if(strcmp(top_type(s),"nil")){
                if(kontrola_typu(s,data)==-1){
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
            EQS(&data->string,data->whileDeep);
            NOTS(&data->string,data->whileDeep);
        }
        else if(!strcmp(top1(s),"..")){                     //E -> E..E
            if(!strcmp(top_type(s),"string")){
                pop(s);
                pop(s);
                if(!strcmp(top_type(s),"string")){
                    change_top_type(s,"string");
                    //zavolat generovani ..
                    CONCAT(&data->string,data->whileDeep);
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

void exp_analysator(Data_t *data){
    Stack * s=(Stack *)malloc(sizeof(Stack));
    init_stack(s);

    Token *token = data->token;
    Token *generator_token = malloc(sizeof(Token));
    generator_token->value=(char*)malloc(token->value_len*sizeof(char));
    Tframe_list *frames= data->list;

    data->relation_operator_in_condition = false;
    int error=0;
    int i,j;
    i=zasobnikovy_znak(s);
    j=vstupni_znak(token);
    while(i!=8 || j!=8){
        i=zasobnikovy_znak(s);
        j=vstupni_znak(token);    
        if(j==4 && top1(s)!=NULL && !strcmp(top(s),"E")){
            i=4;
        }
        if(precence_table[i][j]==0&&error!=-1){         //SHIFT
                if(i==8&&j==4&&!is_empty(s)){
                    kontrola_typu_vysledku(s,data,token);
                    free(generator_token->value);
                    free(generator_token);         
                    return;
                }
                if(j==4){
                strcpy(generator_token->name,token->name);
                generator_token->value = (char*)realloc(generator_token->value,token->value_len*sizeof(char)+1);
                strcpy(generator_token->value,token->value);
                generator_token->value_len=token->value_len;
                }
                do_shift(s,data,token,j,frames);
                read_token(token);
            }                                           
        else if(precence_table[i][j]==1&&error!=-1){    //EQUAL
                do_equal(s);
                read_token(token);
            }                                           
        else if(precence_table[i][j]==2&&error!=-1){    //REDUCE
                error = do_reduc(s,token,generator_token,data);
            }                                           
        else if(precence_table[i][j]==3||error==-1){    //Prazdny zasobnik a vstup je prazdny nebo ')'
                if(error!=-1){
                   if((i==8 && (j==7||j==8)) ||(i==4&&j==4) ){ 
                    if((i==4&&j==4)) {
                        while((top1(s)!=NULL||strcmp(top(s),"E"))&&error!=-1){
                            error=do_reduc(s,token,generator_token,data);
                        }
                    } 
                    if(error!=-1){
                        kontrola_typu_vysledku(s,data,token);
                        free(generator_token->value);
                        free(generator_token);
                        return;
                        }
                    }
                }
                if(precence_table[i][j]==3||error==-1){
                    fprintf(stderr, "ERROR - Chyba syntaktickeho analyzatoru zdola nahoru\n");
                    destroy(s);
                    while(data->list->first != data->list->last){
                            deleteFirst(data->list);
                        }
                            deleteFirst(data->list);
                    free(token);
                    free(data);
                    free(generator_token->value);
                    free(generator_token);
                    exit(INCOMPATIBLE_TYPES);//chyba
                }
            }                                           
    }
    kontrola_typu_vysledku(s,data,token);
    free(generator_token->value);
    free(generator_token);
    return;
}
/* End of file expressions.c */