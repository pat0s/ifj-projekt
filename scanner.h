/**
 * @file scanner.h
 * 
 * @brief Header file for scanner.c. Contains declarations of struct and functions.
 * @author Patrik Sehnoutek, xsehno01
 */

#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/** Max size of token name **/
#define MAX_SIZE 20

/** Array of keywords **/
const char keywords[][9] = {"do", "else", "end", "function", "global", "if", "local", "nil", "require", "return", "then", "while", "string", "integer", "number"};

/** Token **/
typedef struct Token
{
    char name[MAX_SIZE];
    char *value;
    int value_len;
} Token;

void token_initialisation( Token *token );

void token_allocation( Token *token );

bool check_keyword (const char *unknown );

bool add_symbol( Token *token, char symbol );

int read_token( Token *token );

#endif

/* End of header file scanner.h */
