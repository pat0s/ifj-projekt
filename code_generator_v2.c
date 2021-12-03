#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "error.h"
#include "code_generator_v2.h"

#define ending_0 1

int generate_code(char *string, char *code, bool flag)
{
    if (flag){
        string = (char *)realloc(string, sizeof(char) * (strlen(string) + strlen(code) + ending_0));
        if(string == NULL){
            return INTERNAL_ERROR;            
        }
        strcat(string, code);
    }
    else{
        printf("%s", code);
    }

    return 0;
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

int PUSHS(char *string, bool flag, Token *token)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("PUSHS ") +
                                                  strlen(symbol_generator(token)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS [symbol_generator(token)]
    sprintf(buffer, "PUSHS %s\n", symbol_generator(token));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int POPS(char *string, bool flag, Token *token)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS ") +
                                                  strlen(symbol_generator(token)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // POPS [symbol_generator(token)]
    sprintf(buffer, "POPS %s\n", symbol_generator(token));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

void ADDS(char *string, bool flag)
{
    // ADDS
    generate_code(string, "ADDS\n", flag);
}

void SUBS(char *string, bool flag)
{
    // SUBS
    generate_code(string, "SUBS\n", flag);
}

void MULS(char *string, bool flag)
{
    // MULS
    generate_code(string, "MULS\n", flag);
}

int DIVS(char *string, bool flag, Token *token)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("PUSHS ") +
                                                  strlen(symbol_generator(token)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS [symbol_generator(token)]
    sprintf(buffer, "PUSHS %s\n", symbol_generator(token));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS int@0
    generate_code(string, "PUSHS int@0", flag);    

    // JUMPIFEQS divisionByZero
    generate_code(string, "JUMPIFEQS divisionByZero", flag);

    // DIVS
    generate_code(string, "DIVS\n", flag);

    free(buffer);
    return 0;
}

int IDIVS(char *string, bool flag, Token *token)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("PUSHS ") +
                                                  strlen(symbol_generator(token)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS [symbol_generator(token)]
    sprintf(buffer, "PUSHS %s\n", symbol_generator(token));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS int@0
    generate_code(string, "PUSHS int@0", flag);

    // JUMPIFEQS divisionByZero
    generate_code(string, "JUMPIFEQS divisionByZero", flag);

    // IDIVS
    generate_code(string, "IDIVS\n", flag);

    free(buffer);
    return 0;    
}

void LTS(char *string, bool flag)
{
    // LTS
    generate_code(string, "LTS\n", flag);
}

void GTS(char *string, bool flag)
{
    // GTS
    generate_code(string, "GTS\n", flag);
}

void EQS(char *string, bool flag)
{
    // EQS
    generate_code(string, "EQS\n", flag);
}

void ANDS(char *string, bool flag)
{
    // ANDS
    generate_code(string, "ANDS\n", flag);
}

void ORS(char *string, bool flag)
{
    // ORS
    generate_code(string, "ORS\n", flag);
}

void NOTS(char *string, bool flag)
{
    // NOTS
    generate_code(string, "NOTS\n", flag);
}

int CONCAT(char *string, bool flag, char *number, Token *token_symb1, Token *token_symb2)
{
    // DEFVAR LF@T-[number]c
    printf("DEFVAR LF@T-%dc", number);

    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("CONCAT ") +
                                                  strlen("LF @T-") +
                                                  strlen(number) +
                                                  strlen("c") + 
                                                  strlen(" ") +
                                                  strlen(symbol_generator(token_symb1)) +
                                                  strlen(" ") +
                                                  strlen(symbol_generator(token_symb2)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // CONCAT LF@T-[number]c [symbol_generator(token_symb1)] [symbol_generator(token_symb2)]
    sprintf(buffer, "CONCAT LF@T-%dc %s %s\n", number, symbol_generator(token_symb1), symbol_generator(token_symb2));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    buffer = (char *)realloc(sizeof(char) * (strlen("PUSHS ") +
                                             strlen("LF @T-") +
                                             strlen(number) +
                                             strlen("c") +
                                             strlen("\n") +
                                             ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS LF@T-[number]c
    sprintf(buffer, "LABEL end_while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int STRLEN(char *string, bool flag, char *number, Token *token_symb)
{
    // DEFVAR LF@T-[number]c
    printf("DEFVAR LF@T-%dc", number);

    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("STRLEN ") +
                                                  strlen("LF@T-") +
                                                  strlen(number) +
                                                  strlen("c") +
                                                  strlen(" ") +
                                                  strlen(symbol_generator(token_symb)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // STRLEN LF@T-[number]c [symbol_generator(token_symb)]
    sprintf(buffer, "STRLEN LF@T-%sc %s\n", number, symbol_generator(token_symb));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    buffer = (char *)realloc(sizeof(char) * (strlen("PUSHS ") +
                                             strlen("LF @T-") +
                                             strlen(number) +
                                             strlen("c") +
                                             strlen("\n") +
                                             ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS LF@T-[number]c
    sprintf(buffer, "LABEL end_while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

void CREATEFRAME(char *string, bool flag)
{
    generate_code(string, "CREATEFRAME", flag);
}

int ARGUMENTS(char *string, bool flag, char *func_name, char *number, Token *token)
{
    // DEFVAR TF@[func_name]_arg[number]
    printf("DEFVAR TF@%s_arg%d\n", func_name, number);

    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("MOVE TF@") +
                                                  strlen(func_name) +
                                                  strlen("_arg") +
                                                  strlen(" ") +
                                                  strlen(symbol_generator(token)) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // MOVE TF@[func_name]_arg[number] [symbol_generator(token)]
    sprintf(buffer, "MOVE TF@%s_arg%d %s\n", func_name, number, symbol_generator(token));
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;    
}

int CALL_FUNC(char *string, bool flag, char *func_name)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("CALL ") +
                                                  strlen(func_name) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // CALL [func_name]
    sprintf(buffer, "CALL %s\n", func_name);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;    
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
    for (int i = 0; i <= count; i++)
    {
        printf("DEFVAR LF@%s_retval%d\n", func_name, i);
        printf("MOVE LF@%s_retval%d nil@nil\n", func_name, i);
    }
}

void RETURN_RETVALS(char *func_name, int number)
{
    printf("POPS LF@%s_retval%d\n", func_name, number);
}

void FUNC_END(char *func_name, int count)
{
    for (int i = 0; i <= count; i++)
    {
        printf("PUSHS LF@%s_retval%d\n", func_name, i);        
    }

    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL %s_end\n", func_name);
}

int WHILE_START(char *string, bool flag, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("LABEL while_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // LABEL while_[number]
    sprintf(buffer, "LABEL while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }       

    free(buffer);
    return 0;
}

int WHILE_CONDITION(char *string, bool flag, char *number)
{
    int ie;

    // PUSHS bool@false
    ie = generate_code(string, "PUSHS bool@false", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMPIFEQS end_while_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // JUMPIFEQS end_while_[number]
    sprintf(buffer, "JUMPIFEQS end_while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int WHILE_END(char *string, bool flag, int number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMP while_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // JUMP while_[number]
    sprintf(buffer, "JUMP while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    buffer = (char *)realloc(sizeof(char) * (strlen("LABEL end_while_") +
                                             strlen(number) +
                                             strlen("\n") +
                                             ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // LABEL end_while_[number]
    sprintf(buffer, "LABEL end_while_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    free(buffer);
    return 0;
}

int IF_CONDITION(char *string, bool flag, char *number)
{
    int ie;

    // PUSHS bool@false
    ie = generate_code(string, "PUSHS bool@false", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMPIFEQS else_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }    

    // JUMPIFEQS else_[number]
    sprintf(buffer, "JUMPIFEQS else_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int ELSE_BRANCH(char *string, bool flag, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMP end_if_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // JUMP end_if_[number]
    sprintf(buffer, "JUMP end_if_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    buffer = (char *)realloc(sizeof(char) * (strlen("LABEL else_") +
                                             strlen(number) +
                                             strlen("\n") +
                                             ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // LABEL else_[number]
    sprintf(buffer, "LABEL else_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    free(buffer);
    return 0;
}

int IF_END(char *string, bool flag, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("LABEL end_if_") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // LABEL end_if_[number]
    sprintf(buffer, "LABEL end_if_%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }   

    free(str_n);
    return 0;
}

int CONDITION_VARS(char *string, bool flag, char *number)
{
    printf("DEFVAR LF@T-%sl\n", number);
    printf("DEFVAR LF@T-%sr\n", number);    
    return 0;
}

int CONDITION_POPS(char *string, bool flag, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS LF@T-") +
                                                  strlen(number) +
                                                  strlen("r\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // POPS LF@T-[number]r
    sprintf(buffer, "POPS LF@T-%sr\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // POPS LF@T-[number]l
    sprintf(buffer, "POPS LF@T-%sl\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    free(buffer);
    return 0;
}

int CONDITION_PUSHS(char *string, bool flag, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("PUSHS LF@T-") +
                                                  strlen(number) +
                                                  strlen("l\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS LF@T-[number]l
    sprintf(buffer, "PUSHS LF@T-%sl\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS LF@T-[number]r
    sprintf(buffer, "PUSHS LF@T-%sr\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    free(buffer);
    return 0;
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

    /*
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
    free(while_string);*/  
}