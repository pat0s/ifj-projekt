/**
 * @file expressions.h
 * 
 * @brief
 * @author Patrik Sehnoutek, xsehno01
 * @author Dovhalenko Dmytro, xdovha00
 */
#include "scanner.h"
#include "symtable.h"
#include "expressions_stack.h"

#ifndef _EXPRESSIONS_H_
#define _EXPRESSIONS_H_

#define TABLE_SIZE 9 

typedef struct sVariable{
    char *ID;
    int   dataType;
    char *value;

}Variable_t;


typedef struct sFunction{
    char *ID;
    int  *param_types;
    int  param_length;
    int  *ret_types;
    int  ret_length;

}Function_t;


typedef struct fAssignToken{
    char *name;
    int dataType;

}AssignToken_t;

typedef struct sData{
    
    int errorValue;
    Token *token;
    Tframe_list *list;

        //index v poli datovych typov
    int indexType;
        //Uchovava datovy typ premennej pri deklaracii, semanticke kontroly
    int dataType;
        //Premenna, ktora uchovava pole datovych typov. Pomoha pri semantickych kontrolach ruturnu funkcie
    int *arrayType;
        //Premenna, ktora uchovava dlzku int *arrayType
    int arrayTypeLength;
        //Premenna, ktora hovori precedencnej analyze kedy treba osetrovat datove typy
    bool checkDataType;


        //pomocna premenna pre createFuncNode a semanticke kontroli
    Function_t *funkcia;
        //Pomocna premenna pre creteVarNode a semanticke kontroli
    Variable_t *premenna;
        //Pomocna premenna pre semanticke kontroli
    TNode *leaf;
        //Pomocna premenna pre ulozenie token->value v divokych situaciach
    char *tokenValue;
        //Pomocna premenna pre osetrenie spravneho poctu elsov v ife
    int isIf;
        //Pole tokenov, ktore musim ulozit pre spravne skontrolovanie typov a pre generovanie kodu
    AssignToken_t *assignArray;
        //Index pre assignArray, ktory sluzi na tahanie datoveho typu z pola na zaklade poctu volani fexp;
    int assignArrayIndex;
        //pocet datovych typov v poli
    int assignArrayLength;

    int errorCode;
        //pocet zanoreni while cyklov
    int whileDeep;
        //cislo, ktore pridava inukatnost premennym pri generovani kodu
    int specialIDNumber;
} Data_t;



typedef enum 
{
    SHIFT,  // <
    EQUAL,  // = 
    REDUC,  // >
    EMPTY   // ERROR
} TableItem; 

int rozpoznani_znaku(char*znak);
int vstupni_znak(Token* token);
int zasobnikovy_znak(Stack *s);
void do_shift(Stack*s,Data_t * data,Token*token,int vstup,Tframe_list *frames);
void do_equal(Stack*s);
int kontrola_typu(Stack *s);
int do_reduc(Stack *s,Token* token);
void exp_analysator(Data_t *data);
void kontrola_typu_vysledku(Stack *s,Data_t* data,Token* token);


// Rules
/*
    E -> string
    E -> number
    E -> int
    E -> id
    E -> E + E
    E -> E - E
    E -> E * E
    E -> E / E
    E -> E // E
    E -> E > E
    E -> E < E
    E -> E >= E
    E -> E <= E
    E -> E ~= E
    E -> E == E
    E -> (E)
    E -> E..E
    E -> #E
*/

#endif

/* End of header file expressions.h */