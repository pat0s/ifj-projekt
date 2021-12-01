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
    generate_code(string, "ADDS\n", flag);
}

void SUBS(TDynString *string, bool flag)
{
    generate_code(string, "SUBS\n", flag);
}

void MULS(TDynString *string, bool flag)
{
    generate_code(string, "MULS\n", flag);
}

void DIVS(TDynString *string, bool flag)
{
    // TODO: kontrola delenia 0
    generate_code(string, "DIVS\n", flag);
}

void IDIVS(TDynString *string, bool flag)
{
    // TODO: kontrola delenia 0
    generate_code(string, "IDIVS\n", flag);
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

    printf("JUMP startOfCode\n");
    printf("LABEL unexpectedNil\n");
    printf("EXIT int@8\n");
    printf("LABEL divisionByZero\n");
    printf("EXIT int@9\n");
    
    // tointeger
    printf( \
        "LABEL tointeger\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@f\n" \
        "MOVE LF@f LF@tointeger_arg1\n" \
        "DEFVAR LF@tointeger_retval1\n" \
        "MOVE LF@tointeger_retval1 nil@nil\n" \
        "PUSHS LF@tointeger_retval1\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@f\n" \
        "PUSHS LF@tmp \n" \
        "JUMPIFEQS tointeger_nil\n" \
        "FLOAT2INT LF@tointeger_retval1 LF@f\n" \
        "LABEL tointeger_nil\n" \
        "POPFRAME\n" \
        "RETURN\n");
    
    // ord
    printf( \
        "LABEL ord\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@s\n" \
        "MOVE LF@s LF@ord_arg1\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@ord_arg2\n" \
        "DEFVAR LF@ord_retval1\n" \
        "MOVE LF@ord_retval1 nil@nil\n" \
        "PUSHS nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@s\n" \
        "PUSHS LF@tmp\n" \
        "JUMPIFEQS unexpectedNil\n" \
        "PUSHS nil@nil\n" \
        "TYPE LF@tmp LF@i\n" \
        "PUSHS LF@tmp\n" \
        "JUMPIFEQS unexpectedNil\n" \
        "PUSHS LF@i\n" \
        "PUSHS int@1\n" \
        "LTS\n" \
        "PUSHS bool@true \n" \
        "JUMPIFEQS ord_end\n" \
        "STRLEN LF@tmp LF@s\n" \
        "PUSHS LF@i\n" \
        "PUSHS LF@tmp\n" \
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS ord_end\n" \
        "PUSHS LF@s\n" \
        "PUSHS LF@i\n" \
        "STRI2INTS\n" \
        "POPS LF@ord_retval1\n" \
        "LABEL ord_end\n" \
        "POPFRAME\n" \
        "RETURN\n");

    // chr
    printf( \
        "LABEL chr\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@chr_arg1\n" \
        "DEFVAR LF@chr_retval1\n" \
        "MOVE LF@chr_retval1 nil@nil\n" \
        "PUSHS nil@nil\n" \
        "PUSHS LF@i\n" \
        "JUMPIFEQS unexpectedNil\n" \
        "PUSHS LF@i\n" \
        "PUSHS int@0\n" \
        "LTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS chr_end\n" \
        "PUSHS LF@i\n" \
        "PUSHS int@255\n" \
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS chr_end\n" \
        "PUSHS LF@i\n" \
        "INT2CHARS\n" \
        "POPS LF@chr_retval1\n" \
        "LABEL chr_end\n" \
        "POPFRAME\n" \
        "RETURN\n");

    // readn
    // readi
    // reads
    
    // substr
    
    // chr
    // ak je i < j 
    // * staci skontrolovat ci je i < 1, ak je mensie, tak sa vrati nil ak nie, tak sa pokracuje
    // * staci skontrolovat ci je j > strlen(s), ak je vacsie, vrati sa nil ak nie, tak sa pokracuje
    printf( \
        "LABEL substr\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@s\n" \
        "MOVE LF@s LF@substr_arg1\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@substr_arg1\n" \
        "DEFVAR LF@j\n" \
        "MOVE LF@j LF@substr_arg1\n" \
        "DEFVAR LF@substr_retval1\n" \
        "MOVE LF@substr_retval1 nil@nil\n" \

        "PUSHS nil@nil\n" \
        "PUSHS LF@s\n" \
        "JUMPIFEQS unexpectedNil\n" \

        "PUSHS nil@nil\n" \
        "PUSHS LF@i\n" \
        "JUMPIFEQS unexpectedNil\n" \

        "PUSHS nil@nil\n" \
        "PUSHS LF@j\n" \
        "JUMPIFEQS unexpectedNil\n" \
        
        "PUSHS LF@j\n" \
        "PUSHS LF@i\n" \
        "LTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS substr_end\n" \


        "PUSHS LF@i\n" \
        "PUSHS int@1\n" \
        "LTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS substr_end\n" \
        
        "DEFVAR LF@tmp\n" \
        "STRLEN LF@tmp LF@s\n" \
        "PUSHS LF@j\n" \
        "PUSHS LF@tmp\n"\
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS substr_end\n" \

        "GETCHAR LF@substr_retval1 LF@s LF@i\n" \
        "PUSHS int@1\n" \
        "PUSHS LF@i\n" \
        "ADDS\n" \
        "POPS LF@i\n" \
        
        "LABEL while\n" \
        "PUSHS LF@i\n" \
        "PUSHS LF@j\n" \
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMIFEQS end_while\n" \
        "GETCHAR LF@tmp LF@s LF@i\n" \
        "CONCAT LF@substr_retval1 LF@substr_retval1 LF@tmp\n" \
        "PUSHS int@1\n" \
        "PUSHS LF@i\n" \
        "ADDS\n" \
        "POPS LF@i\n" \
        "JUMP while\n" \
        
        "LABEL end_while\n" \
        "POPFRAME\n" \
        "RETURN\n");

    // -- write function
    // write(a, 10)
    // "WRITE nazov_premennej_a\n" 
    // "WRITE int@10\n"

    // koniec vstavanych funkcii
    printf("LABEL startOfCode");
}

/**
 * @brief Generate function header
 * 
 * @param func_name Pointer to function's name
 */
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

/**
 * @brief Generate return values for function
 * 
 * @param func_name Pointer to function's name 
 * @param count Number of return values
 */
void RETVALS(char *func_name, int count)
{
    for (int i = 1; i <= count; i++)
    {
        printf("DEFVAR LF@%s_retval%d\n", func_name, i);
        printf("MOVE LF@%s_retval%d nil@nil\n", func_name, i);
    }   
}

void RETURNS(char *func_name, int number, char *symb)
{
    printf("MOVE LF@%s_retval%d %s\n", func_name, number, symb);
}

/**
 * @brief Generate function ending
 * 
 * @param func_name Pointer to function's name
 */
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