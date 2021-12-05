#include "code_generator_v2.h"

#define ending_0 1


char *INT2STRING(int number)
{
    char *str_n = (char *)malloc(sizeof(char) * (compute_digits(number) + ending_0));
    sprintf(str_n, "%d", number);
    return str_n;
}

int generate_code(char **string, char *code, bool flag)
{
    if (flag){
        *string = (char *)realloc(*string, sizeof(char) * (strlen(*string) + strlen(code) + ending_0));
        if(string == NULL){
            return INTERNAL_ERROR;            
        }
        strcat(*string, code);
    }
    else{
        printf("%s", code);
    }

    return 0;
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

    for (unsigned int i = 0; i < strlen(old_str); i++)
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
    printf("EXIT int@8\n\n");
    printf("LABEL divisionByZero\n");
    printf("EXIT int@9\n\n");

    // tointeger
    printf(
        "LABEL tointeger\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@f\n" \
        "MOVE LF@f LF@tointeger_arg1\n" \
        "DEFVAR LF@tointeger_retval1\n" \
        "MOVE LF@tointeger_retval1 nil@nil\n" \
        "PUSHS string@nil\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@f\n" \
        "PUSHS LF@tmp \n" \
        "JUMPIFEQS tointeger_nil\n" \
        "FLOAT2INT LF@tointeger_retval1 LF@f\n" \
        "LABEL tointeger_nil\n" \
        "PUSHS LF@tointeger_retval1\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // ord
    printf(
        "LABEL ord\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@s\n" \
        "MOVE LF@s LF@ord_arg1\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@ord_arg2\n" \
        "DEFVAR LF@ord_retval1\n" \
        "MOVE LF@ord_retval1 nil@nil\n" \
        "PUSHS string@nil\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@s\n" \
        "PUSHS LF@tmp\n" \
        "JUMPIFEQS unexpectedNil\n" \
        "PUSHS string@nil\n" \
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
        "PUSHS LF@ord_retval1\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // chr
    printf(
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
        // toto obidvoje as vymazat
        "POPS LF@chr_retval1\n" \
        "PUSHS LF@chr_retval1\n" \
        "LABEL chr_end\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // readn
    printf( \
        "LABEL readn\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@readn_retval1\n" \
        "MOVE LF@readn_retval1 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp float\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@float\n" \
        "JUMPIFNEQS readn_end\n" \
        "MOVE LF@readn_retval1 LF@tmp\n" \
        "LABEL readn_end\n" \
        "PUSHS LF@readn_retva1\n" \
        "POPFRAME\n" \
        "RETURN\n\n" \
    );

    // readi
     printf( \
        "LABEL readi\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@readi_retval1\n" \
        "MOVE LF@readi_retval1 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp int\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@int\n" \
        "JUMPIFNEQS readi_end\n" \
        "MOVE LF@readi_retval1 LF@tmp\n" \
        "LABEL readi_end\n" \
        "PUSHS LF@readi_retva1\n" \
        "POPFRAME\n" \
        "RETURN\n\n" \
    );
    
    // reads
    printf( \
        "LABEL readn\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@reads_retval1\n" \
        "MOVE LF@reads_retval1 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp string\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@string\n" \
        "JUMPIFNEQS reads_end\n" \
        "MOVE LF@reads_retval1 LF@tmp\n" \
        "LABEL reads_end\n" \
        "PUSHS LF@reads_retva1\n" \
        "POPFRAME\n" \
        "RETURN\n\n" \
    );

    // substr
    // ak je i < j
    // * staci skontrolovat ci je i < 1, ak je mensie, tak sa vrati nil ak nie, tak sa pokracuje
    // * staci skontrolovat ci je j > strlen(s), ak je vacsie, vrati sa nil ak nie, tak sa pokracuje
    printf(
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
        "PUSHS LF@tmp\n" \
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
        "PUSHS LF@substr_ret1\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // -- write function
    // write(a, 10)
    // "WRITE nazov_premennej_a\n"
    // "WRITE int@10\n"

    // koniec vstavanych funkcii
    printf("LABEL startOfCode");
}

void DEFVAR(char *var_name)
{
    printf("DEFVAR %s", var_name);
}

int DEFVAR_AND_INIT(char **string, bool flag, char *var_name)
{
    printf("DEFVAR %s", var_name);

    // MOVE [var_name] nil@nil
    return generate_code(string, "MOVE %s nil@nil", var_name);
}

int PUSHS(char **string, bool flag, Token *token, bool nill_oc)
{
    int ie;
    char *buffer;

    if(nill_oc)
    {
        // PUSHS nil@nil
        ie = generate_code(string, "PUSHS nil@nil\n", flag); // check if malloc failed in generate_codes
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        buffer = (char *)malloc(sizeof(char) * (strlen("TYPE LF@T-Nvar ") +
                                                      strlen(symbol_generator(token)) +
                                                      strlen("\n") +
                                                      ending_0));
        if (buffer == NULL) // check if malloc failed in CONDITION_START
        {
            return INTERNAL_ERROR;
        }

        // TYPE LF@T-Nvar [symbol_generator(token)]
        sprintf(buffer, "TYPE LF@T-Nvar %s\n", symbol_generator(token));
        ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        // PUSHS LF@T-Nvar
        ie = generate_code(string, "PUSHS LF@T-Nvar\n", flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        // JUMPIFEQS unexpectedNil
        ie = generate_code(string, "JUMPIFEQS unexpectedNil\n", flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        buffer = (char *)realloc(buffer, sizeof(char) * (strlen("PUSHS ") +
                                                         strlen(symbol_generator(token)) +
                                                         strlen("\n") +
                                                         ending_0));
        if (buffer == NULL) // check if malloc failed in CONDITION_START
        {
            return INTERNAL_ERROR;
        }
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

int POPS(char **string, bool flag, char *var_name)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS ") +
                                                  strlen(var_name) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // POPS [var_name]
    sprintf(buffer, "POPS %s\n", var_name);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int ADDS(char **string, bool flag)
{
    // ADDS
    return generate_code(string, "ADDS\n", flag); // check if malloc failed in generate_code    
}

int SUBS(char **string, bool flag)
{
    // SUBS
    return generate_code(string, "SUBS\n", flag); // check if malloc failed in generate_code    
}

int MULS(char **string, bool flag)
{
    // MULS
    return generate_code(string, "MULS\n", flag); // check if malloc failed in generate_code    
}

int DIVS(char **string, bool flag, Token *token)
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
    ie = generate_code(string, "PUSHS int@0\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    // JUMPIFEQS divisionByZero
    ie = generate_code(string, "JUMPIFEQS divisionByZero\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }    

    // DIVS
    ie = generate_code(string, "DIVS\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int IDIVS(char **string, bool flag, Token *token)
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
    ie = generate_code(string, "PUSHS int@0\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // JUMPIFEQS divisionByZero
    ie = generate_code(string, "JUMPIFEQS divisionByZero\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // IDIVS
    ie = generate_code(string, "IDIVS\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;    
}

int LTS(char **string, bool flag)
{
    // LTS
    return generate_code(string, "LTS\n", flag); // check if malloc failed in generate_code   
}

int GTS(char **string, bool flag)
{
    // GTS
    return generate_code(string, "GTS\n", flag); // check if malloc failed in generate_code    
}

int EQS(char **string, bool flag)
{
    // EQS
    return generate_code(string, "EQS\n", flag); // check if malloc failed in generate_code    
}

int ANDS(char **string, bool flag)
{
    // ANDS
    return generate_code(string, "ANDS\n", flag); // check if malloc failed in generate_code    
}

int ORS(char **string, bool flag)
{
    // ORS
    return generate_code(string, "ORS\n", flag); // check if malloc failed in generate_code    
}

int NOTS(char **string, bool flag)
{
    // NOTS
    return generate_code(string, "NOTS\n", flag); // check if malloc failed in generate_code    
}

int CONCAT(char **string, bool flag)
{
    int ie;

    // POPS LF@T-Nsymb2
    ie = generate_code(string, "POPS LF@T-Nsymb2\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // POPS LF@T-Nsymb1
    ie = generate_code(string, "POPS LF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // CONCAT LF@T-Nvar LF@T-Nsymb1 LF@T-Nsymb2
    ie = generate_code(string, "CONCAT LF@T-Nvar LF@T-Nsymb1 LF@T-Nsymb2\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS LF@T-Nvar
    ie = generate_code(string, "PUSHS LF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    return 0;
}

int STRLEN(char **string, bool flag)
{
    int ie;

    // POPS LF@T-Nsymb1
    ie = generate_code(string, "POPS LF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // STRLEN LF@T-Nvar LF@T-Nsymb1
    ie = generate_code(string, "STRLEN LF@T-Nvar LF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS LF@T-Nvar
    ie = generate_code(string, "PUSHS LF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    return 0;
}

void CREATEFRAME()
{
    // CREATEFRAME
    printf("CREATEFRAME\n");
}

int DEFINE_ARG(char *func_name, char *number)
{
    // DEFVAR TF@[func_name]_arg[number]
    printf("DEFVAR TF@%s_arg%s\n", func_name, number);    
}

int INIT_ARG(char **string, bool flag, char *func_name, char *number)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS TF@") +
                                                  strlen(func_name) +
                                                  strlen("_arg") +
                                                  strlen(number) + 
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // POPS TF@[func_name]_arg[number]
    sprintf(buffer, "POPS TF@%s_arg%s\n", func_name, number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int CALL_FUNC(char **string, bool flag, char *func_name)
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
    printf("DEFVAR LF@T-Nvar");
    printf("MOVE LF@T-Nvar nil@nil\n");
    printf("DEFVAR LF@T-Nsymb1");
    printf("MOVE LF@T-Nsymb1 nil@nil\n");
    printf("DEFVAR LF@T-Nsymb2");
    printf("MOVE LF@T-Nsymb2 nil@nil\n");
}

void PARAMETERS(char *func_name, char *param_name, int number, char *IDcislo)
{
    printf("DEFVAR LF@C-%s%s\n",IDcislo, param_name);
    printf("MOVE LF@%s LF@%s_arg%d\n", param_name, func_name, number);
}

void DEF_RETVALS( int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("DEFVAR LF@retval%d\n", i);
        printf("MOVE LF@retval%d nil@nil\n", i);
    }
}

void RETURN_RETVALS( int number)
{
    printf("POPS LF@retval%d\n", number);
}

void FUNC_END(char *func_name, int count)
{
    for (int i = 0; i <= count; i++)
    {
        printf("PUSHS LF@retval%d\n", i);        
    }

    printf("POPFRAME\n");
    printf("RETURN\n");
    printf("LABEL %s_end\n", func_name);
}

int WHILE_START(char **string, bool flag, char *number)
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

int WHILE_CONDITION(char **string, bool flag, char *number)
{
    int ie;

    // PUSHS bool@false
    ie = generate_code(string, "PUSHS bool@false\n", flag); // check if malloc failed in generate_code
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

int WHILE_END(char **string, bool flag, char *number)
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

    buffer = (char *)realloc(buffer, sizeof(char) * (strlen("LABEL end_while_") +
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

int IF_CONDITION(char **string, bool flag, char *number)
{
    int ie;

    // PUSHS bool@false
    ie = generate_code(string, "PUSHS bool@false\n", flag); // check if malloc failed in generate_code
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

int ELSE_BRANCH(char **string, bool flag, char *number)
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

    buffer = (char *)realloc(buffer, sizeof(char) * (strlen("LABEL else_") +
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

int IF_END(char **string, bool flag, char *number)
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

    free(buffer);
    return 0;
}

void CONDITION_VARS(char *number)
{
    printf("DEFVAR LF@T-%sl\n", number);
    printf("DEFVAR LF@T-%sr\n", number);    
}

int CONDITION_POPS(char **string, bool flag, char *number)
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

int CONDITION_PUSHS(char **string, bool flag, char *number)
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

/*
// testovani
int main()
{    
    // testovani funkci generovani
    char **f_string;
    char *while_string = (char *)malloc(sizeof(char));
    while_string[0] = '\0';
    f_string = &while_string;

    Token *token = malloc(sizeof(Token));
    //token_initialisation(token);
    strcpy(token->name, "identifier");
    token->value_len = 10;
    token->value = (char *)malloc(token->value_len * sizeof(char));
    strcpy(token->value, "ahoj");

    // out while
    puts("-----out while-----");
    PUSHS(f_string, false, token);
    POPS(f_string, false, token);
    ADDS(f_string, false);
    SUBS(f_string, false);
    MULS(f_string, false);
    DIVS(f_string, false, token);
    IDIVS(f_string, false, token);
    LTS(f_string, false);
    GTS(f_string, false);
    EQS(f_string, false);
    ANDS(f_string, false);
    ORS(f_string, false);
    NOTS(f_string, false);
    CONCAT(f_string, false);
    STRLEN(f_string, false);
    CREATEFRAME(f_string, false);
    ARGUMENTS(f_string, false, "fun_func", "14", token);
    CALL_FUNC(f_string, false, "fun_func");
    FUNC_START("fun_func");
    PARAMETERS("fun_func", "a", 3);
    DEF_RETVALS("fun_func", 3);
    RETURN_RETVALS("fun_func", 3);
    FUNC_END("fun_func", 3);
    WHILE_START(f_string, false, "15");
    WHILE_CONDITION(f_string, false, "16");
    WHILE_END(f_string, false, "17");
    IF_CONDITION(f_string, false, "18");
    ELSE_BRANCH(f_string, false, "19");
    IF_END(f_string, false, "20");
    CONDITION_VARS(f_string, false, "21");
    CONDITION_POPS(f_string, false, "22");
    CONDITION_PUSHS(f_string, false, "23");

    // in while
    puts("-----in while-----");
    PUSHS(f_string, true, token);
    POPS(f_string, true, token);
    ADDS(f_string, true);
    SUBS(f_string, true);
    MULS(f_string, true);
    DIVS(f_string, true, token);
    IDIVS(f_string, true, token);
    LTS(f_string, true);
    GTS(f_string, true);
    EQS(f_string, true);
    ANDS(f_string, true);
    ORS(f_string, true);
    NOTS(f_string, true);
    CONCAT(f_string, true);
    STRLEN(f_string, true);
    CREATEFRAME(f_string, true);
    ARGUMENTS(f_string, true, "fun_func", "14", token);
    CALL_FUNC(f_string, true, "fun_func");
    FUNC_START("fun_func");
    PARAMETERS("fun_func", "a", 3);
    DEF_RETVALS("fun_func", 3);
    RETURN_RETVALS("fun_func", 3);
    FUNC_END("fun_func", 3);
    WHILE_START(f_string, true, "15");
    WHILE_CONDITION(f_string, true, "16");
    WHILE_END(f_string, true, "17");
    IF_CONDITION(f_string, true, "18");
    ELSE_BRANCH(f_string, true, "19");
    IF_END(f_string, true, "20");
    CONDITION_VARS(f_string, true, "21");
    CONDITION_POPS(f_string, true, "22");
    CONDITION_PUSHS(f_string, true, "23");

    printf("%s", while_string);
    free(while_string);
    
    // Testovanie funkcie generate symbol    
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
}*/