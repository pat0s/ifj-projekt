#ifndef SYNANALYS_H
#define SYNANALYS_H

#include"scanner.h"


enum STATE {assign, assigns, arg, args, exp, ifStatement, item, item_n, init, init_value, prog, prog_con, par_type, ret_val, ret_type, st_list, type, types, value, values, params, params_n};


typedef struct sData{
    
    bool isError;
    int errorValue;
    Token *token;

} Data_t;



void fValues(Token *token, enum STATE *state, Data_t *data);
void fValue(Token *token, enum STATE *state, Data_t *data);
void fInit_value(Token *token, enum STATE *state, Data_t *data);
void fInit(Token *token, enum STATE *state, Data_t *data);
void fItem_n(Token *token, enum STATE *state, Data_t *data);
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



#endif