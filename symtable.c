/**
 * @file symtable.c
 * @author Ivo Procházka
 * @brief 
 * @version 0.1
 * @date 2021-11-13
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "symtable.h"

// list of symtable functions definition

/**
 * @brief Create a Var Node object, returns fully prepared node
 * 
 * @param given_id id of a new node 
 * @param given_dt data type of a new node
 * @param given_val value of a new node
 * @param error_occur stores 0 for 0 erorrs, stores 1 if an error occured
 * @return TNode* 
 */
TNode *createVarNode(char *given_id, int given_dt, char *given_val, int *error_occur)
{
    *error_occur = 0;

    TNode *newPtr = (TNode *)malloc(sizeof(TNode));
    if (newPtr == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    newPtr->function = false;

    char *newID = (char *)malloc(sizeof(char) * strlen(given_id));
    if (newID == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    for (unsigned int i = 0; i < strlen(given_id);i++){
        newID[i] = given_id[i];
    }
    newPtr->ID = newID;

    TVar *newVar = (TVar *)malloc(sizeof(TVar));
    if (newVar == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    newVar->data_type = given_dt;

    char *newVal = (char *)malloc(sizeof(char)*strlen(given_val));
    if (newVal == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    for (unsigned int i = 0; i < strlen(given_val);i++){
        newVal[i] = given_val[i];
    }
    newVar->value = newVal;

    newPtr->var = newVar;
    newPtr->func = NULL;

    newPtr->lPtr = NULL;
    newPtr->rPtr = NULL;

    return newPtr;
}

/**
 * @brief Create a Func Node object, returns fully prepared node   
 * 
 * @param given_id id of a new node
 * @param given_def if function was previously defined stores 1, otherwise 0
 * @param given_pt parameter types of a function stored as an array of ints
 * @param pt_length length of given_pt
 * @param given_rt return types of a function stored as an array of ints
 * @param rt_length length of given_rt
 * @param error_occur stores 0 for 0 erorrs, stores 1 if an error occured
 * @return TNode* 
 */
TNode *createFuncNode(char *given_id, bool given_def, int *given_pt, int pt_length, int *given_rt, int rt_length, int *error_occur)
{
    *error_occur = 0;

    TNode *newPtr = (TNode *)malloc(sizeof(TNode));
    if (newPtr == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    newPtr->function = true;

    char *newID = (char *)malloc(sizeof(char) * strlen(given_id));
    if (newID == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    for (unsigned int i = 0; i < strlen(given_id); i++)
    {
        newID[i] = given_id[i];
    }
    newPtr->ID = newID;

    TFunc *newFunc = (TFunc *)malloc(sizeof(TFunc));
    if (newFunc == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    newFunc->defined = given_def;
    
    int *newPt = (int *)malloc(sizeof(int) * pt_length);
    if (newPt == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
    }

    for (int i = 0; i < pt_length; i++)
    {
        newPt[i] = given_pt[i];
    }
    newFunc->param_types = newPt;
    
    int *newRt = (int *)malloc(sizeof(int) * rt_length);
    if (newRt == NULL)
    {
        *error_occur = INTERNAL_ERROR; 
        exit(1);
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

/**
 * @brief will put a node on the right place in a BST; if node already exists detects error
 * 
 * @param rootPtr pointer pointing on root of the BST  
 * @param k key that is used in finding the right spot
 * @param d node to be put on the right spot
 * @param error_occur stores 0 for 0 erorrs, stores 1 if an error occured
 * @return TNode* 
 */
TNode *inner_insert(TNode *rootPtr, char *k, TNode *d, int *error_occur)
{
    if (rootPtr == NULL)
    {
        return d;
    }
    else if (!strcmp(rootPtr->ID, k))
    {
        *error_occur = INTERNAL_ERROR; 
    }
    else if (strcmp(rootPtr->ID, k) > 0)
    {
        rootPtr->lPtr = inner_insert(rootPtr->lPtr, k, d, error_occur);
    }
    else
    {
        rootPtr->rPtr = inner_insert(rootPtr->rPtr, k, d, error_occur);       
    }
    return rootPtr;
}

/**
 * @brief this function exists due to a problem with returning pointers; 
 * calls inner_insert function; returns 0 for 0 erorrs, returns 1 if an error occured
 * 
 * @param rootPtr pointer on pointer of root of the BST
 * @param newNode pointer on a new node to be put in the tree
 * @return int 
 */
int insert(TNode **rootPtr, TNode *newNode)
{
    int error_occur = 0;
    *rootPtr = inner_insert(*rootPtr, newNode->ID, newNode, &error_occur);
    return error_occur;
}

/**
 * @brief prints the whole tree in inOrder form, function used for testing
 * 
 * @param rootPtr root of a BST
 */
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

/**
 * @brief finds a node in a BST with minimal ID
 * 
 * @param rootPtr root of a BST
 * @return TNode* 
 */
TNode *bvsMin(TNode *rootPtr)
{
    if (rootPtr->lPtr == NULL)
    {
        return rootPtr;
    }
    else
    {
        return bvsMin(rootPtr->lPtr);
    }
}

/**
 * @brief deletes a node with the right key
 * 
 * @param rootPtr root of a BST
 * @param k key
 * @return TNode* 
 */
TNode *bvsDelete(TNode *rootPtr, char *k)
{
    if (rootPtr == NULL)
    {
        return NULL;
    }
    else if(!strcmp(rootPtr->ID, k))
    {
        if (rootPtr->lPtr == NULL && rootPtr->rPtr == NULL)
        {
            free(rootPtr->ID);
            if (rootPtr->function)
            {
                free(rootPtr->func->param_types);
                free(rootPtr->func->ret_types);
            }else{
                free(rootPtr->var->value);
            }

            free(rootPtr);
            return NULL;
        }
        else if (rootPtr->lPtr != NULL && rootPtr->rPtr != NULL)
        {
            TNode *min = bvsMin(rootPtr->rPtr);
            rootPtr->function = min->function;
            rootPtr->ID = min->ID;

            rootPtr->var = min->var;
            rootPtr->func = min->func;

            rootPtr->rPtr = bvsDelete(rootPtr->rPtr, min->ID);
            return rootPtr;
        }
        else
        {
            TNode *onlyChild = NULL;
            if (rootPtr->lPtr == NULL)
            {
                onlyChild = rootPtr->rPtr;
            }
            else
            {
                onlyChild = rootPtr->lPtr;
            }

            free(rootPtr->ID);
            if (rootPtr->function)
            {
                free(rootPtr->func->param_types);
                free(rootPtr->func->ret_types);
            }
            else
            {
                free(rootPtr->var->value);
            }

            free(rootPtr);
            return onlyChild;
        }
    }
    else if (strcmp(rootPtr->ID, k) > 0)
    {
        rootPtr->lPtr = bvsDelete(rootPtr->lPtr, k);
        return rootPtr;
    }
    else
    {
        rootPtr->rPtr = bvsDelete(rootPtr->rPtr, k);
        return rootPtr;
    }
}

/**
 * @brief deletes/disposes whole BTS, calls bvsDelete function
 * 
 * @param rootPtr root of a BTS
 * @param error_occur stores 0 for 0 erorrs, stores 1 if an error occured
 * @return TNode* 
 */
TNode *inner_dispose(TNode *rootPtr, int *error_occur)
{
    while (rootPtr != NULL)
    {
        rootPtr = bvsDelete(rootPtr, rootPtr->ID);
    }
    *error_occur = 0;
    return rootPtr;
}

/**
 * @brief deletes/disposes whole BTS; stores 0 for 0 erorrs, stores 1 if an error occured
 * 
 * @param rootPtr root of a BTS
 * @return int 
 */
int dispose(TNode **rootPtr)
{
    int error_occur = INTERNAL_ERROR; 
    *rootPtr = inner_dispose(*rootPtr, &error_occur);
    return error_occur;
}

/**
 * @brief finds a node and returns it, if not returns NULL
 * 
 * @param rootPtr root of a BST
 * @param k ID of a node
 * @return TNode* 
 */
TNode *search(TNode *rootPtr, char *k)
{
    if (rootPtr == NULL)
    {
        return NULL;
    }
    else if (!strcmp(rootPtr->ID, k))
    {
        return rootPtr;
    }
    else if (strcmp(rootPtr->ID, k) > 0)
    {
        return search(rootPtr->lPtr, k);
    }
    else
    {
        return search(rootPtr->rPtr, k);
    }
}

/**
 * @brief returns true if node with ID k is function, for variable returns false
 * 
 * @param rootPtr root of a BST
 * @param k ID of a node
 * @return true 
 * @return false 
 */
bool isFunction(TNode *rootPtr, char *k)
{
    TNode *result;    
    result = search(rootPtr, k);
    return result->function;
}

// end of list of symtable functions definition

// list of symtable list functions definition

/**
 * @brief initialise the whole symtable list
 * 
 * @param l preferably pointing at NULL
 */
void initList(Tframe_list *l)
{
    l->first = NULL;
    l->last = NULL;
}

/**
 * @brief inserts symtable list node at first position
 * 
 * @param l symtable list
 * @param fb if this node belongs to a function
 * @param rootPtr pointer at root of a symtable
 * @return int 
 */
int insertFirst(Tframe_list *l, bool fb, TNode *rootPtr)
{
    Tframe *newElemPtr = (Tframe *)malloc(sizeof(Tframe));
    if (newElemPtr == NULL)
    {
        return INTERNAL_ERROR;
    }

    newElemPtr->func_body = fb;
    newElemPtr->rootPtr = rootPtr;
    newElemPtr->next = l->first;

    if (l->first == NULL)
    {
        l->last = newElemPtr;
    }
    l->first = newElemPtr;

    return 0;
}

/**
 * @brief searches the whole symtable list and finds, using ID, correct variable, returns TNode variable or NULL
 * 
 * @param l symtable list
 * @param k ID
 * @return TNode* 
 */
TNode *searchFrames(Tframe_list *l, char *k)
{
   TNode *result;
   Tframe *tmp = l->first;

   result = search(tmp->rootPtr, k);
   while (result == NULL && tmp->func_body == false)
   {
       tmp = tmp->next;
       result = search(tmp->rootPtr, k);
   }

   return result;
}

