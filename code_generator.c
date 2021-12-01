#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "code_generator.h"
#include "error.h"

#define ending_0 2 // need to alocate space for \0

// reads, readi, readn -> READ
// write -> WRITE * n podla parametrov

// Start

// hlavicka funkcie

// return values
// return funkcie (prikaz return)

// priradenie hodnot z return funkcie (samotny prikaz return)

// volanie funkcie

// vkladanie parametrov do funckie

// if label

// if jump

// else jmp, label

// if end

// while - hlavicka, telo, end

// premenna vo while !!!!

// var definicia

// var priradenie

// konstanta

// operacie
// # -> STRLEN
// .. -> CONCAT

// kontrola delenia 0
// iba pri / a //

// kontrola neocakavanej hodnoty nil pri operaciach
// okrem == ~=

void dyn_string_init(TDynString *dyn_string)
{
    dyn_string->string = NULL;
    dyn_string->length = 0;
}

int dyn_string_realloc(TDynString *dyn_string, char *code)
{
    // First allocation
    if (dyn_string->length == 0)
    {
        dyn_string->string = (char *)malloc(sizeof(char));
        if (dyn_string == NULL) return INTERNAL_ERROR;

        dyn_string->string[0] = '\0';
    }
    
    dyn_string->length += strlen(code) + ending_0;
    dyn_string->string = (char *)realloc(dyn_string->string, dyn_string->length * sizeof(char));
       
    if (dyn_string->string == NULL) return INTERNAL_ERROR; 
    
    return 0;
}



void generate_code(TDynString *dyn_string, char *code, bool flag)
{
    if (flag){
        // Reallocation
        int error = dyn_string_realloc(dyn_string, code);
        
        // Internal error during reallocation
        if (error == INTERNAL_ERROR)
        {
            // TODO nejako to poriesit
        }

        // Concatenation
        strcat(dyn_string->string, code);        
    }            
    else
    {
        printf("%s\n", code);
    }
}

void ADDS(TDynString *string, bool flag)
{
    generate_code(string, "ADDS\n", true);
}

void SUBS(TDynString *string, bool flag)
{
    generate_code(string, "SUBS\n", true);
}

void MULS(TDynString *string, bool flag)
{
    generate_code(string, "MULS\n", true);
}

void DIVS(TDynString *string, bool flag)
{
    generate_code(string, "DIVS\n", true);
}

void IDIVS(TDynString *string, bool flag)
{
    generate_code(string, "IDIVS\n", true);
}

void CONCAT(TDynString *dyn_string, bool flag, char *var, char *symb1, char *symb2)
{
    int concat_len = 6; // delka concat
    int var_len = strlen(var);
    int symb1_len = strlen(symb1);
    int symb2_len = strlen(symb2);
    int spaces_n_0 = 5; // 3 mezery, /n a /0
    int length = concat_len + var_len + symb1_len + symb2_len + spaces_n_0;
    char *buffer = (char *)malloc(sizeof(char) * length);
    snprintf(buffer, sizeof(char) * length, "CONCAT %s %s %s\n", var, symb1, symb2);
    printf("%s", buffer);
    generate_code(dyn_string, buffer, flag);
    free(buffer);
}

void STRLEN(TDynString *string, bool flag, char *var, char *symb)
{
    generate_code(string, "STRLEN ", flag);
    generate_code(string, var, flag);
    generate_code(string, " ", flag);
    generate_code(string, symb, flag);
    generate_code(string, "\n", flag);
}    

void START_AND_BUILTIN_FUNCTIONS()
{
    printf(".IFJcode21\n");
    // zbytek
}

void FUNC_START(char *func_name)
{
    printf("JUMP %s_end\n", func_name);    
    printf("LABEL %s\n", func_name);    
    printf("PUSHFRAME\n");
}

void PARAMETERS(char *func_name, char *param_name, int number)
{
    printf("DEFVAR LF@%s\n", param_name);
    printf("MOVE LF@%s LF@%s_arg%d\n", param_name, func_name, number);
}

void RETVALS(char *func_name, int number)
{
    printf("DEFVAR LF@%s_retval%d\n", func_name, number);
    printf("MOVE LF@%s_retval%d nil@nil\n", func_name, number);
}

void RETURNS(char *func_name, int number, char *symb)
{
    printf("MOVE LF@%s_retval%d %s\n", func_name, number, symb);
}

void FUNC_END(char *func_name)
{
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL %s_end\n", func_name);
}

int main()
{
    // Asi bude potrebna aj alokacia struktury, kedze sa to bude pouzivat vsade
    // to pridam zajtra ked tak
    TDynString dyn_string;
    dyn_string_init(&dyn_string);
    ADDS(&dyn_string, true);
    FUNC_START("foo");
    PARAMETERS("foo", "a", 1);
    PARAMETERS("foo", "b", 2);
    PARAMETERS("foo", "c", 3);
    RETVALS("foo", 1);
    RETURNS("foo", 1, "c");
    FUNC_END("foo");    

    CONCAT(&dyn_string, true, "ba", "bida", "oda");

    printf("%s", dyn_string.string);
    return 0;
}