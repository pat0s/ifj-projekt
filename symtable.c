#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "error.h"

#define LENGTH(a) (sizeof(a) / sizeof(*a))

typedef struct tvar
{
    int data_type;
    char *value;
} TVar;

typedef struct tfunc
{
    bool defined;
    int *param_types;
    int *ret_types;
} TFunc;

typedef struct tnode
{
    bool function;
    char *ID;

    TVar *var;
    TFunc *func;

    struct tnode *lPtr;
    struct tnode *rPtr;
} TNode;

TNode *createVarNode(char *given_id, int given_dt, char *given_val, int *error_occur)
{
    TNode *newPtr = (TNode *)malloc(sizeof(TNode));
    if (newPtr != NULL)
    {
        *error_occur = 0;
    }

    newPtr->function = false;

    char *newID = (char *)malloc(sizeof(char) * strlen(given_id));
    if (newID != NULL)
    {
        *error_occur = 0;
    }

    for (int i = 0; i < strlen(given_id);i++){
        newID[i] = given_id[i];
    }
    newPtr->ID = newID;

    TVar *newVar = (TVar *)malloc(sizeof(TVar));
    if (newVar != NULL)
    {
        *error_occur = 0;
    }

    newVar->data_type = given_dt;

    char *newVal = (char *)malloc(sizeof(char)*strlen(given_val));
    if (newVal != NULL)
    {
        *error_occur = 0;
    }

    for (int i = 0; i < strlen(given_val);i++){
        newVal[i] = given_val[i];
    }
    newVar->value = newVal;

    newPtr->var = newVar;
    newPtr->func = NULL;

    newPtr->lPtr = NULL;
    newPtr->rPtr = NULL;

    return newPtr;
}

TNode *createFuncNode(char *given_id, bool given_def, int *given_pt, int pt_length, int *given_rt, int rt_length, int *error_occur)
{
    TNode *newPtr = (TNode *)malloc(sizeof(TNode));
    if (newPtr != NULL)
    {
        *error_occur = 0;
    }

    newPtr->function = true;

    char *newID = (char *)malloc(sizeof(char) * strlen(given_id));
    if (newID != NULL)
    {
        *error_occur = 0;
    }

    for (int i = 0; i < strlen(given_id); i++)
    {
        newID[i] = given_id[i];
    }
    newPtr->ID = newID;

    TFunc *newFunc = (TFunc *)malloc(sizeof(TFunc));
    if (newFunc != NULL)
    {
        *error_occur = 0;
    }

    newFunc->defined = given_def;
    
    int *newPt = (int *)malloc(sizeof(int) * pt_length);
    if (newPt != NULL)
    {
        *error_occur = 0;
    }

    for (int i = 0; i < pt_length; i++)
    {
        newPt[i] = given_pt[i];
    }
    newFunc->param_types = newPt;
    
    int *newRt = (int *)malloc(sizeof(int) * rt_length);
    if (newRt != NULL)
    {
        *error_occur = 0;
    }

    for (int i = 0; i < rt_length; i++)
    {
        newRt[i] = given_rt[i];
    }
    newFunc->ret_types = newRt;

    newPtr->var = NULL;
    newPtr->func = newFunc;

    newPtr->lPtr = NULL;
    newPtr->rPtr = NULL;

    return newPtr;
}

TNode *inner_insert(TNode *rootPtr, char *k, TNode *d, int *error_occur){
    if (rootPtr == NULL)
    {
        return d;
    }
    else if (strcmp(rootPtr->ID, k))
    {
        rootPtr->lPtr = inner_insert(rootPtr->lPtr, k, d, error_occur);
    }
    else if (strcmp(k, rootPtr->ID))
    {
        rootPtr->rPtr = inner_insert(rootPtr->rPtr, k, d, error_occur);
    }
    else
    {
        *error_occur = 1; // INTERNAL_ERROR
    }
    return rootPtr;
}

// NECO NEJEDE
int insert(TNode **rootPtr, TNode *newNode)
{
    int error_occur = 1; // INTERNAL_ERRORS
    *rootPtr = inner_insert(*rootPtr, newNode->ID, newNode, &error_occur);
    return error_occur;
}

void inOrder(TNode *rootPtr)
{
    if (rootPtr != NULL)
    {
        inOrder(rootPtr->lPtr);
        printf("|%s|", rootPtr->ID);
        inOrder(rootPtr->rPtr);
    }
    else
    {
        printf("|N|");
    }
}

int main()
{
    TNode *rootPtr = NULL;    
    int error;
    int array_pt[] = {1, 2, 3, 4};
    int array_rt[] = {1, 2, 3};    
    error = insert(&rootPtr, createFuncNode("func", true, array_pt, LENGTH(array_pt), array_rt, LENGTH(array_rt), &error));
    error = insert(&rootPtr, createVarNode("prom", 0, "69", &error));
    error = insert(&rootPtr, createFuncNode("a", true, array_pt, LENGTH(array_pt), array_rt, LENGTH(array_rt), &error));
    error = insert(&rootPtr, createVarNode("b", 0, "69", &error));
    error = insert(&rootPtr, createFuncNode("c", true, array_pt, LENGTH(array_pt), array_rt, LENGTH(array_rt), &error));
    error = insert(&rootPtr, createVarNode("d", 0, "69", &error));
    error = insert(&rootPtr, createFuncNode("akat", true, array_pt, LENGTH(array_pt), array_rt, LENGTH(array_rt), &error));
    error = insert(&rootPtr, createVarNode("hovno", 0, "69", &error));
    error = insert(&rootPtr, createFuncNode("vut", true, array_pt, LENGTH(array_pt), array_rt, LENGTH(array_rt), &error));

    inOrder(rootPtr);
    puts("");

    return 0;
}