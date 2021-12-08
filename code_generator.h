/**
 * Project: IFJ21
 * @file code_generator.c
 * 
 * @brief Function for code generation
 * @author Patrik Sehnoutek, xsehno01
 * @author Ivo Procházka, xproch0h
 */

#ifndef _CODE_GENERATOR_H_
#define _CODE_GENERATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "scanner.h"

// not user functions
int compute_digits(int n);
char *INT2STRING(int number);
int generate_code(char **string, char *code, bool flag);
void str2_codestr(char *dst, char *old_str);
void str2hex(char *value, char *buf);
char *create_special_name(char *name, char *number);
char *symbol_generator(Token *token, char *number);

// start
void START_AND_BUILTIN_FUNCTIONS();

// variable definition and initialization
void DEFVAR_AND_INIT(char *var_name, char *number);
int POPS_INFINITE(char **string, bool flag);
int POPS(char **string, bool flag, char *var_name, char *number);

// exppresions
int PUSHS(char **string, bool flag, Token *token, char *number, bool nill_oc);
int ADDS(char **string, bool flag);
int SUBS(char **string, bool flag);
int MULS(char **string, bool flag);
int DIVS(char **string, bool flag);
int IDIVS(char **string, bool flag);
int LTS(char **string, bool flag);
int GTS(char **string, bool flag);
int EQS(char **string, bool flag);
int ANDS(char **string, bool flag);
int ORS(char **string, bool flag);
int NOTS(char **string, bool flag);
int CONCAT(char **string, bool flag);
int STRLEN(char **string, bool flag);
int TOP_I2F(char **string, bool flag, char *number);
int BEFORE_TOP_I2F(char **string, bool flag, char *number);

// call function
int CREATEFRAME(char **string, bool flag);
int DEFINE_ARG(char **string, char *func_name, char *number, bool flag);
int INIT_ARG(char **string, bool flag, char *func_name, char *number);
int CALL_FUNC_WRITE(char **string, bool flag);
int CALL_FUNC(char **string, bool flag, char *func_name);

// function definition
void FUNC_START(char *func_name);
void PARAMETERS(char *func_name, char *param_name, int number, char *IDcislo);
void DEF_RETVALS( int count);
int RETURN_RETVALS(char **string, bool flag, char *number);
int FUNC_RETURN(char** string, int count, int flag);
void FUNC_END(char *func_name, int count);

// while
int WHILE_START(char **string, bool flag, char *number);
int WHILE_CONDITION(char **string, bool flag, char *number, bool n_comp);
int WHILE_END(char **string, bool flag, char *number);

// if
int IF_CONDITION(char **string, bool flag, char *number, bool n_comp);
int ELSE_BRANCH(char **string, bool flag, char *number);
int IF_END(char **string, bool flag, char *number);

// condition
void CONDITION_VARS(char *number);
int  CONDITION_POPS(char **string, bool flag, char *number);
int CONDITION_PUSHS(char **string, bool flag, char *number);

#endif
