#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "code_generator.h"
#include "error.h"

#define ending_0 2 // need to alocate space for \0

/*void dyn_string_init(TDynString *dyn_string)
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
}*/

void generate_code(TDynString *dyn_string, char *code, bool flag)
{
    if (flag){
        // Reallocation
        int error = dyn_string_realloc(dyn_string, code);       

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
    int concat_len = 6; // delka CONCAT
    int var_len = strlen(var);
    int symb1_len = strlen(symb1);
    int symb2_len = strlen(symb2);
    int spaces = 3;     // 3 mezery
    int n_0 = 2;        // 1x/n a 1x/0

    int length = concat_len + var_len + symb1_len + symb2_len + spaces + n_0;
    char *buffer = (char *)malloc(sizeof(char) * length);
    snprintf(buffer, sizeof(char) * length, "CONCAT %s %s %s\n", var, symb1, symb2);    
    generate_code(dyn_string, buffer, flag);
    free(buffer);
}

void STRLEN(TDynString *dyn_string, bool flag, char *var, char *symb)
{
    int concat_len = 6; // delka STRLEN
    int var_len = strlen(var);
    int symb_len = strlen(symb);    
    int spaces = 2;     // 2 mezery
    int n_0 = 2;        // 1x/n a 1x/0

    int length = concat_len + var_len + symb_len + spaces + n_0;
    char *buffer = (char *)malloc(sizeof(char) * length);
    snprintf(buffer, sizeof(char) * length, "STRLEN %s %s\n", var, symb);
    generate_code(dyn_string, buffer, flag);
    free(buffer);
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

int c_digits(int n)
{
    int r = 1;
    if(n < 9){
        n /= 10;
        r++;
    }
    return r;
}

void WHILE_START(TDynString *string, bool flag, int number)
{
    char *s_number = (char *)malloc(sizeof(char) * (c_digits(number) + 1));
    sprintf(s_number, "%d", number);

    generate_code(string, "DEFVAR LF@T", flag);   
    generate_code(string, s_number, flag);
    generate_code(string, "l\n", flag);

    generate_code(string, "DEFVAR LF@T", flag);
    generate_code(string, s_number, flag);
    generate_code(string, "r\n", flag);

    generate_code(string, "LABEL", flag);
    generate_code(string, s_number, flag);
    generate_code(string, "while\n", flag);
}

void WHILE_END(TDynString *string, bool flag, int number)
{
    char *s_number = (char *)malloc(sizeof(char) * (c_digits(number) + 1));
    sprintf(s_number, "%d", number);

    generate_code(string, "JUMP ", flag);
    generate_code(string, s_number, flag);
    generate_code(string, "while\n", flag);

    generate_code(string, "LABEL ", flag);
    generate_code(string, s_number, flag);
    generate_code(string, "end_while\n", flag);
}

int main()
{
    // Asi bude potrebna aj alokacia struktury, kedze sa to bude pouzivat vsade
    // to pridam zajtra ked tak
    TDynString dyn_string;
    dyn_string_init(&dyn_string);  

    STRLEN(&dyn_string, true, "baVVV", "biDADda");
    CONCAT(&dyn_string, true, "ba", "bida", "oda");

    printf("%s", dyn_string.string);
    return 0;
}