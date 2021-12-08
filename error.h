/**
 * Project: IFJ21 
 * @file error.h
 * 
 * @brief Contains error types
 * @author Patrik Sehnoutek, xsehno01
 */

#ifndef ERROR_H
#define ERROR_H

/** Lexical error **/
#define LEX_ERROR 1
/** Syntax error **/
#define SYNTAX_ERROR 2
/** Undefined variable, function or re-declaration (Semantic error) **/
#define UNDEFINED_VAR 3
/** Incompatible types in assignment (Semantic error) **/
#define ASSIGNMENT_ERROR 4
/** Wrong types or number of function parameters or return values (Semantic error) **/
#define FUNCTION_ERROR 5
/** Incompatible types in expressions (Semantic error) **/
#define INCOMPATIBLE_TYPES 6
/** Other (Semantic error) **/
#define OTHER_SEM_ERROR 7
/** Unexpected nil value **/
#define UNEXPECTED_NIL_VALUE 8
/** Division by zero error **/
#define DIVISION_BY_ZERO 9
/** Malloc erorr, ... **/
#define INTERNAL_ERROR 99

#endif

/* End of header file error.h */
