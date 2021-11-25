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

typedef struct sData{
    
    bool isError;
    int errorValue;
    Token *token;
    Tframe_list *list;
    
    int indexType;
    int arrayType[20];
    bool checkDataType;

    Function_t *funkcia;
    Variable_t *premenna;
    TNode *leaf;
    char *tokenValue;
    int isIf;

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
int do_reduc(Stack *s);
void *exp_analysator(Data_t *data);

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