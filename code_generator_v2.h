#ifndef _CODE_GENERATOR_H_V2_
#define _CODE_GENERATOR_H_V2_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "scanner.h"

// not user functions
int generate_code(char **string, char *code, bool flag);
void str2_codestr(char *dst, char *old_str);
void str2hex(char *value, char *buf);
char *symbol_generator(Token *token);

// start
void START_AND_BUILTIN_FUNCTIONS();

// exppresions and POPS
int PUSHS(char **string, bool flag, Token *token);
int POPS(char **string, bool flag, Token *token);
int ADDS(char **string, bool flag);
int SUBS(char **string, bool flag);
int MULS(char **string, bool flag);
int DIVS(char **string, bool flag, Token *token);
int IDIVS(char **string, bool flag, Token *token);
int LTS(char **string, bool flag);
int GTS(char **string, bool flag);
int EQS(char **string, bool flag);
int ANDS(char **string, bool flag);
int ORS(char **string, bool flag);
int NOTS(char **string, bool flag);
int CONCAT(char **string, bool flag);
int STRLEN(char **string, bool flag);

// call function
int CREATEFRAME(char **string, bool flag);
int ARGUMENTS(char **string, bool flag, char *func_name, char *number, Token *token);
int CALL_FUNC(char **string, bool flag, char *func_name);

// function definition
void FUNC_START(char *func_name);
void PARAMETERS(char *func_name, char *param_name, int number);
void DEF_RETVALS(char *func_name, int count);
void RETURN_RETVALS(char *func_name, int number);
void FUNC_END(char *func_name, int count);

// while
int WHILE_START(char **string, bool flag, char *number);
int WHILE_CONDITION(char **string, bool flag, char *number);
int WHILE_END(char **string, bool flag, char *number);

// if
int IF_CONDITION(char **string, bool flag, char *number);
int ELSE_BRANCH(char **string, bool flag, char *number);
int IF_END(char **string, bool flag, char *number);

// condition
void CONDITION_VARS(char **string, bool flag, char *number);
int CONDITION_POPS(char **string, bool flag, char *number);
int CONDITION_PUSHS(char **string, bool flag, char *number);

#endif