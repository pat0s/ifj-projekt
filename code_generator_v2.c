#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "code_generator_v2.h"

#define ending_0 1

void generate_code(char *string, char *code, bool flag)
{
    if (flag){
        string = (char *)realloc(string, sizeof(char) * (strlen(string) + strlen(code) + ending_0));
        if(string == NULL){
            // return INTERNAL_ERROR
            exit(1);
        }
        strcat(string, code);
    }
    else{
        printf("%s", code);
    }
}

int compute_digits(int n)
{
    int r = 1;
    while(n > 9){
        n /= 10;
        r++;
    }
    return r;
}

/**
 * @brief Edits string literals
 * 
 * @param dst Input string
 * @param old_str Output string in format for .ifjcode21
 */
void str2_codestr(char *dst, char *old_str)
{
    bool is_escaped = false;
    int j = 0;

    for (int i = 0; i < strlen(old_str); i++)
    {
        if ((old_str[i] >= 0 && old_str[i] <= 32) || old_str[i] == 35 || old_str[i] == 92)
        {
            if (old_str[i] == 92)
            {
                is_escaped = !is_escaped;
            }

            if (is_escaped) continue;

            char tmp[3]; // mozu sa tu ulozit iba cisla 0-32, 35 alebo 92
            dst[j++] = '\\';
            dst[j++] = '0';

            sprintf(tmp, "%d", old_str[i]);
            if (strlen(tmp) == 1) dst[j++] = '0';
            dst[j++] = tmp[0];
            if (strlen(tmp) > 1) dst[j++] = tmp[1];
        }
        else if(is_escaped)
        {
            char tmp[3]; // mozu sa tu ulozit iba cisla 0-32, 35 alebo 92
            switch (old_str[i])
            {
                // '\t', '\n'
                case 't':
                case 'n':
                    dst[j++] = '\\';
                    dst[j++] = '0';

                    sprintf(tmp, "%d", old_str[i]);
                    if (strlen(tmp) == 1) dst[j++] = '0';
                    dst[j++] = tmp[0];
                    if (strlen(tmp) > 1) dst[j++] = tmp[1];
                    
                    break;
                // '\"'  
                case '\"':
                    dst[j++] = '\"';
                    break;
                // '\xyz' -> 000-255  
                case '0':
                case '1':
                case '2':
                    dst[j++] = '\\';

                    dst[j++] = old_str[i++];
                    dst[j++] = old_str[i++];
                    dst[j++] = old_str[i];

                    break;
                default:
                    break;
            }
            is_escaped = false;
        }
        else
        {
            dst[j++] = old_str[i];
        }

    }

    dst[j] = '\0';
}

/**
 * @brief Converts string representation of float number to hex format
 * 
 * @param value String representation of float number
 * @param buf Hex format
 */
void str2hex(char *value, char *buf)
{
    char *eptr;
    double result = strtod(value, &eptr);
    sprintf(buf, "%a", result);
}

/**
 * @brief 
 * 
 * @param token 
 * @return char 
 */
char *symbol_generator(Token *token)
{
    char *symbol;
    if(strcmp(token->name, "identifier") == 0)
    {
        char prefix[4] = "LF@";

        symbol = (char *)malloc((token->value_len + 4)*(sizeof(char)));
        // TODO: osetrenie mallocu
        strcpy(symbol, prefix);
        strcat(symbol, token->value);
    }
    else
    {
        if (strcmp(token->name, "string") == 0)
        {
            // TODO mozno pomocou reallocu
            char *buf;
            buf = (char *)malloc(sizeof(char) * 500);
            // TODO: osetrenie mallocu
            str2_codestr(buf, token->value);

            symbol = (char *)malloc((8 + strlen(buf))*(sizeof(char)));
            // TODO: osetrenie mallocu
            strcpy(symbol, "string@");
            strcat(symbol, buf);
            free(buf);
        }
        else if(strcmp(token->name, "int") == 0)
        {
            symbol = (char *)malloc((token->value_len + 5)*(sizeof(char)));
            // TODO: osetrenie mallocu
            strcpy(symbol, "int@");
            strcat(symbol, token->value);

            return symbol;
        }
        else if(strcmp(token->name, "number") == 0)
        {    
            char buf[500];
            str2hex(token->value, buf);

            symbol = (char*)malloc((7 + strlen(buf))*sizeof(char));
            // TODO osetrenie mallocu
            strcpy(symbol, "float@");
            strcat(symbol, buf);
        }

    }

    return symbol;
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
    printf(
        "LABEL tointeger\n"
        "PUSHFRAME\n"
        "DEFVAR LF@f\n"
        "MOVE LF@f LF@tointeger_arg1\n"
        "DEFVAR LF@tointeger_retval1\n"
        "MOVE LF@tointeger_retval1 nil@nil\n"
        "PUSHS LF@tointeger_retval1\n"
        "DEFVAR LF@tmp\n"
        "TYPE LF@tmp LF@f\n"
        "PUSHS LF@tmp \n"
        "JUMPIFEQS tointeger_nil\n"
        "FLOAT2INT LF@tointeger_retval1 LF@f\n"
        "LABEL tointeger_nil\n"
        "POPFRAME\n"
        "RETURN\n");

    // ord
    printf(
        "LABEL ord\n"
        "PUSHFRAME\n"
        "DEFVAR LF@s\n"
        "MOVE LF@s LF@ord_arg1\n"
        "DEFVAR LF@i\n"
        "MOVE LF@i LF@ord_arg2\n"
        "DEFVAR LF@ord_retval1\n"
        "MOVE LF@ord_retval1 nil@nil\n"
        "PUSHS nil@nil\n"
        "DEFVAR LF@tmp\n"
        "TYPE LF@tmp LF@s\n"
        "PUSHS LF@tmp\n"
        "JUMPIFEQS unexpectedNil\n"
        "PUSHS nil@nil\n"
        "TYPE LF@tmp LF@i\n"
        "PUSHS LF@tmp\n"
        "JUMPIFEQS unexpectedNil\n"
        "PUSHS LF@i\n"
        "PUSHS int@1\n"
        "LTS\n"
        "PUSHS bool@true \n"
        "JUMPIFEQS ord_end\n"
        "STRLEN LF@tmp LF@s\n"
        "PUSHS LF@i\n"
        "PUSHS LF@tmp\n"
        "GTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS ord_end\n"
        "PUSHS LF@s\n"
        "PUSHS LF@i\n"
        "STRI2INTS\n"
        "POPS LF@ord_retval1\n"
        "LABEL ord_end\n"
        "POPFRAME\n"
        "RETURN\n");

    // chr
    printf(
        "LABEL chr\n"
        "PUSHFRAME\n"
        "DEFVAR LF@i\n"
        "MOVE LF@i LF@chr_arg1\n"
        "DEFVAR LF@chr_retval1\n"
        "MOVE LF@chr_retval1 nil@nil\n"
        "PUSHS nil@nil\n"
        "PUSHS LF@i\n"
        "JUMPIFEQS unexpectedNil\n"
        "PUSHS LF@i\n"
        "PUSHS int@0\n"
        "LTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS chr_end\n"
        "PUSHS LF@i\n"
        "PUSHS int@255\n"
        "GTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS chr_end\n"
        "PUSHS LF@i\n"
        "INT2CHARS\n"
        "POPS LF@chr_retval1\n"
        "LABEL chr_end\n"
        "POPFRAME\n"
        "RETURN\n");

    // readn
    // readi
    // reads

    // substr
    // ak je i < j
    // * staci skontrolovat ci je i < 1, ak je mensie, tak sa vrati nil ak nie, tak sa pokracuje
    // * staci skontrolovat ci je j > strlen(s), ak je vacsie, vrati sa nil ak nie, tak sa pokracuje
    printf(
        "LABEL substr\n"
        "PUSHFRAME\n"
        "DEFVAR LF@s\n"
        "MOVE LF@s LF@substr_arg1\n"
        "DEFVAR LF@i\n"
        "MOVE LF@i LF@substr_arg1\n"
        "DEFVAR LF@j\n"
        "MOVE LF@j LF@substr_arg1\n"
        "DEFVAR LF@substr_retval1\n"
        "MOVE LF@substr_retval1 nil@nil\n"

        "PUSHS nil@nil\n"
        "PUSHS LF@s\n"
        "JUMPIFEQS unexpectedNil\n"

        "PUSHS nil@nil\n"
        "PUSHS LF@i\n"
        "JUMPIFEQS unexpectedNil\n"

        "PUSHS nil@nil\n"
        "PUSHS LF@j\n"
        "JUMPIFEQS unexpectedNil\n"

        "PUSHS LF@j\n"
        "PUSHS LF@i\n"
        "LTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS substr_end\n"

        "PUSHS LF@i\n"
        "PUSHS int@1\n"
        "LTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS substr_end\n"

        "DEFVAR LF@tmp\n"
        "STRLEN LF@tmp LF@s\n"
        "PUSHS LF@j\n"
        "PUSHS LF@tmp\n"
        "GTS\n"
        "PUSHS bool@true\n"
        "JUMPIFEQS substr_end\n"

        "GETCHAR LF@substr_retval1 LF@s LF@i\n"
        "PUSHS int@1\n"
        "PUSHS LF@i\n"
        "ADDS\n"
        "POPS LF@i\n"

        "LABEL while\n"
        "PUSHS LF@i\n"
        "PUSHS LF@j\n"
        "GTS\n"
        "PUSHS bool@true\n"
        "JUMIFEQS end_while\n"
        "GETCHAR LF@tmp LF@s LF@i\n"
        "CONCAT LF@substr_retval1 LF@substr_retval1 LF@tmp\n"
        "PUSHS int@1\n"
        "PUSHS LF@i\n"
        "ADDS\n"
        "POPS LF@i\n"
        "JUMP while\n"

        "LABEL end_while\n"
        "POPFRAME\n"
        "RETURN\n");

    // -- write function
    // write(a, 10)
    // "WRITE nazov_premennej_a\n"
    // "WRITE int@10\n"

    // koniec vstavanych funkcii
    printf("LABEL startOfCode");
}

void CREATEFRAME(char *string, bool flag)
{
    generate_code(string, "CREATEFRAME", flag);
}

void ARGUMENTS(char *string, bool flag, char *func_name, int number, char *symb)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    generate_code(string, "DEFVAR TF@", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "_arg", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    generate_code(string, "MOVE TF@", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "_arg", flag);
    generate_code(string, str_n, flag);
    generate_code(string, " ", flag);
    generate_code(string, symb, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void CALL_FUNC(char *string, bool flag, char *func_name)
{
    generate_code(string, "CALL ", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "\n", flag);    
}

void RETURNS(char *string, bool flag, char *func_name, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    generate_code(string, "DEFVAR LF@", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "_return", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    generate_code(string, "MOVE LF@", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "_return", flag);
    generate_code(string, str_n, flag);
    generate_code(string, " TF@", flag);
    generate_code(string, func_name, flag);
    generate_code(string, "_retval", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
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

void DEF_RETVALS(char *func_name, int count)
{
    for (int i = 1; i <= count; i++)
    {
        printf("DEFVAR LF@%s_retval%d\n", func_name, i);
        printf("MOVE LF@%s_retval%d nil@nil\n", func_name, i);
    }
}

void RETURN_RETVALS(char *func_name, int number, char *symb) // pozor na jmena promennych v symb, potreba pridavat LF@
{
    printf("MOVE LF@%s_retval%d %s\n", func_name, number, symb);
}

void FUNC_END(char *func_name)
{
    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL %s_end\n", func_name);
}

void WHILE_START(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    // 1. DEFVAR
    generate_code(string, "DEFVAR LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "l\n", flag);

    // 2. DEFVAR
    generate_code(string, "DEFVAR LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "r\n", flag);

    // LABEL whilu
    generate_code(string, "LABEL while_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void WHILE_CONDITION(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    generate_code(string, "PUSHS bool@false", flag);
    generate_code(string, "JUMPIFEQS end_while_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void WHILE_END(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    // jump back
    generate_code(string, "JUMP while_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    // end cycle
    generate_code(string, "LABEL end_while_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void IF_CONDITION(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    generate_code(string, "PUSHS bool@false", flag);
    generate_code(string, "JUMPIFEQS else_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void ELSE_BRANCH(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);
    
    generate_code(string, "JUMP end_if_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    generate_code(string, "LABEL else_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void IF_END(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    generate_code(string, "LABEL end_if_", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "\n", flag);

    free(str_n);
}

void CONDITION_POPS(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    // 1. POPS
    generate_code(string, "POPS LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "r\n", flag);

    // 2. POPS
    generate_code(string, "POPS LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "l\n", flag);

    free(str_n);
}

void CONDITION_PUSHS(char *string, bool flag, int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);

    // 1. PUSHS
    generate_code(string, "PUSHS LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "l\n", flag);

    // 2. PUSHS
    generate_code(string, "PUSHS LF@T-", flag);
    generate_code(string, str_n, flag);
    generate_code(string, "r\n", flag);

    free(str_n);
}

// testovani
int main()
{
    char *while_string = (char *)malloc(sizeof(char));
    while_string[0] = '\0';
    generate_code(while_string, "ADDS\n", true);
    generate_code(while_string, "POPS\n", true);
    generate_code(while_string, "CONCAT\n", true);
    generate_code(while_string, "STRLEN\n", true);
    generate_code(while_string, "PUSHS\n", true);
    generate_code(while_string, "CREATEFRAME\n", true);
    generate_code(while_string, "PUSHFRAME\n", true);
    generate_code(while_string, "RETURN\n", true);

    // Testovanie funkcie generate symbol
    Token *token;
    //token_initialisation(token);
    strcpy(token->name, "identifier");
    token->value_len = 10;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "ahoj");

    printf("%s\n", symbol_generator(token));

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "string");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "ahoj ako\t sa mas#");

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "string");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "znak noveho riadku: ahoj\n ako sa mas#");

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "string");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "uvodzoka a backslash: ahoj\\ ako sa mas\"");

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "string");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "dalsie escape: ako\\035 ako\\009 ako\\215");
    printf("original:%s\n", token->value);

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "string");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "ahoj");

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "int");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "-5");

    printf("%s\n", symbol_generator(token));

    strcpy(token->name, "number");
    token->value_len = 100;
    token->value = (char *)malloc(token->value_len*sizeof(char));
    strcpy(token->value, "10.5");

    printf("%s\n", symbol_generator(token));


    printf("%s", while_string);
    free(while_string);


   
}