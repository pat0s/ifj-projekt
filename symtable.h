/**
 * Project: IFJ21 
 * @file symtable.h
 *
 * @brief Declarations of functions for symtable and frames 
 * @author Ivo Procházka, xproch0h
 */

#ifndef SYMTABLE_H
#define SYMTABLE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "error.h"

#define LENGTH(a) (sizeof(a) / sizeof(*a)) // simple macro, counts length of an array

// enum of types

enum TYPES
{
    INTEGER = 0,
    NUMBER = 1,
    STRING = 2,
    NIL = 3
};

// symtable structures

/**
 * @brief holds information about node that is variable
 * , var data_type: data_type of a variable
 * , var value: value of a variable 
 */
typedef struct tvar
{
    int data_type;
    char *value;
    int specialID;
} TVar;

/**
 * @brief holds information about node that is function
 * , var defined: if function was previously defined
 * , var param_types: stores parameter types of a function
 * , var ret_types: stores return types of a function 
 */
typedef struct tfunc
{
    bool defined;
    int *param_types;
    int param_length;
    int *ret_types;
    int ret_length;
} TFunc;

/**
 * @brief holds information about node
 * , var function: if the node is function
 * , var ID: string that contains key of a node
 * , pointer var: points at structure tvar
 * , pointer func: points at structure tfunc
 * , pointer lPtr: points at left son
 * , pointer rPtr: points at right son
 */
typedef struct tnode
{
    bool function;
    char *ID;

    TVar *var;
    TFunc *func;

    struct tnode *lPtr;
    struct tnode *rPtr;
} TNode;

// frame list structures

/**
 * @brief list of symtables
 * , var func_body: if this node belongs to a function(it can belong to if while etc.)
 * , pointer rootPtr: points at symtable
 * , pointer next: points at symtable node list deeper in the code
 */
typedef struct tframe
{
    bool func_body;
    TNode *rootPtr;
    struct tframe *next;
} Tframe;

/**
 * @brief points at first and last symtable list node
 * , pointer first: points at first symtable list node
 * , pointer last: points at last symtable node
 */
typedef struct tframe_list
{
    Tframe *first;
    Tframe *last;
} Tframe_list;

// user functions for symtable

TNode *createVarNode(char *given_id, int given_dt, char *given_val, int *error_occur, int specialID);
TNode *createFuncNode(char *given_id, bool given_def, int *given_pt, int pt_length, int *given_rt, int rt_length, int *error_occur);
int insert(TNode **rootPtr, TNode *newNode);
int dispose(TNode **rootPtr);
TNode *search(TNode *rootPtr, char *k);
bool isFunction(TNode *rootPtr, char *k);

// other functions for symtable

TNode *inner_insert(TNode *rootPtr, char *k, TNode *d, int *error_occur);
TNode *bvsMin(TNode *rootPtr);
TNode *bvsDelete(TNode *rootPtr, char *k);
TNode *inner_dispose(TNode *rootPtr, int *error_occur);
TNode *deleteNode(TNode *rootPtr);

// testing functions for symtable

void inOrder(TNode *rootPtr);

// user functions for frame list

void initList(Tframe_list *l);
int insertFirst(Tframe_list *l, bool fb, TNode *rootPtr);
TNode *searchFrames(Tframe_list *l, char *k);
void deleteFirst(Tframe_list *frames);

#endif