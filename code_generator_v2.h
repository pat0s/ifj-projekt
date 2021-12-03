#include "scanner.h"

#ifndef _CODE_GENERATOR_H_V2_
#define _CODE_GENERATOR_H_V2_

// not user functions
void generate_code(char *string, char *code, bool flag);
int compute_digits(int n);
char *symbol_generator(Token *token);

//start
void START_AND_BUILTIN_FUNCTIONS();

// function calling
void CREATEFRAME(char *string, bool flag);
void ARGUMENTS(char *string, bool flag, char *func_name, int number, char *symb);
void CALL_FUNC(char *string, bool flag, char *func_name);
//void RETURNS(char *string, bool flag, char *func_name, int number);

//function definition
void FUNC_START(char *func_name);
void PARAMETERS(char *func_name, char *param_name, int number);
void RETVALS(char *func_name, int count);
//void RETURNS(char *func_name, int number, char *symb);
void FUNC_END(char *func_name);

//while
void WHILE_START(char *string, bool flag, int number);
void WHILE_CONDITION(char *string, bool flag, int number);
void WHILE_END(char *string, bool flag, int number);

//if
void IF_CONDITION(char *string, bool flag, int number);
void ELSE_BRANCH(char *string, bool flag, int number);
void IF_END(char *string, bool flag, int number);

//condition
void CONDITION_POPS(char *string, bool flag, int number);
void CONDITION_PUSHS(char *string, bool flag, int number);

#endif