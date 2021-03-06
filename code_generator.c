/**
 * Project: IFJ21
 * @file code_generator.c
 * 
 * @brief Function for code generation
 * @author Patrik Sehnoutek, xsehno01
 * @author Ivo Procházka, xproch0h
 */

#include "code_generator.h"

#define ending_0 1


int compute_digits(int n)
{
    int r = 1;
    while(n > 9){
        n /= 10;
        r++;
    }
    return r;
}

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
            switch (old_str[i])
            {
                // '\t', '\n'
                case 't':
                    dst[j++] = '\\';
                    dst[j++] = '0';
                    dst[j++] = '0';
                    dst[j++] = '9';
					break;
                case 'n':
                    dst[j++] = '\\';
                    dst[j++] = '0';
                    dst[j++] = '1';
                    dst[j++] = '0';
                    
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
 * @brief Convert a variable name to a unique variable name
 * 
 * @param name Variable name
 * @param number Special variable ID
 * 
 * @return Returns pointer to the unique variable name
 */
char *create_special_name(char *name, char *number)
{
    char *special_name;
    char prefix[7] = "LF@C-";

    special_name = (char *)malloc((strlen(number) + strlen(name) + 7)*(sizeof(char)));
    
    if (special_name == NULL) exit(INTERNAL_ERROR);

    sprintf(special_name, "%s%s%s", prefix, number, name);
    return special_name;
}

/**
 * @brief Converts constant and variable name to a unique code string 
 * 
 * @param token Struct containg information about constant or identifier
 * @param number Special variable ID
 * 
 * @return Returns pointer to the unique code string
 */
char *symbol_generator(Token *token, char* number)
{
    char *symbol;
    if(strcmp(token->name, "identifier") == 0)
    {
        symbol = create_special_name(token->value, number);
    }
    else if ((strcmp(token->name, "nil") == 0) && (strcmp(token->value, "nil") == 0))
    {
        symbol = (char *)malloc(sizeof(char) * 8);
        sprintf(symbol, "nil@nil");
    }
    
    else
    {
        if (strcmp(token->name, "string") == 0)
        {
            char *buf;
            buf = (char *)malloc(sizeof(char) * 1000);
            if (buf == NULL) exit(INTERNAL_ERROR);
            str2_codestr(buf, token->value);

            symbol = (char *)malloc((8 + strlen(buf))*(sizeof(char)));
            if (symbol == NULL) exit(INTERNAL_ERROR); 
            strcpy(symbol, "string@");
            strcat(symbol, buf);
            free(buf);
        }
        else if(strcmp(token->name, "int") == 0)
        {
            symbol = (char *)malloc((token->value_len + 5)*(sizeof(char)));
            if (symbol == NULL) exit(INTERNAL_ERROR);
            strcpy(symbol, "int@");
            strcat(symbol, token->value);

            return symbol;
        }
        else if(strcmp(token->name, "number") == 0)
        {    
            char buf[500];
            str2hex(token->value, buf);

            symbol = (char*)malloc((7 + strlen(buf))*sizeof(char));
            if (symbol == NULL) exit(INTERNAL_ERROR);
            strcpy(symbol, "float@");
            strcat(symbol, buf);
        }

    }

    return symbol;
}

void START_AND_BUILTIN_FUNCTIONS()
{
    printf(".IFJcode21\n");

    printf("DEFVAR GF@T-Nvar\n");
    printf("MOVE GF@T-Nvar nil@nil\n");
    printf("DEFVAR GF@T-Nsymb1\n");
    printf("MOVE GF@T-Nsymb1 nil@nil\n");
    printf("DEFVAR GF@T-Nsymb2\n");
    printf("MOVE GF@T-Nsymb2 nil@nil\n");
	printf("DEFVAR GF@T-write\n");
	printf("MOVE GF@T-write nil@nil\n");
    printf("DEFVAR GF@infinite_void_space\n\n");

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
        "MOVE LF@f LF@tointeger_arg0\n" \
        "DEFVAR LF@tointeger_retval0\n" \
        "MOVE LF@tointeger_retval0 nil@nil\n" \
        "PUSHS string@nil\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@f\n" \
        "PUSHS LF@tmp \n" \
        "JUMPIFEQS tointeger_nil\n" \
        "FLOAT2INT LF@tointeger_retval0 LF@f\n" \
        "LABEL tointeger_nil\n" \
        "PUSHS LF@tointeger_retval0\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // ord
    printf(
        "LABEL ord\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@s\n" \
        "MOVE LF@s LF@ord_arg0\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@ord_arg1\n" \
        "DEFVAR LF@ord_retval0\n" \
        "MOVE LF@ord_retval0 nil@nil\n" \
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
        "PUSHS int@1\n" \
        "SUBS\n"\
        "STRI2INTS\n" \
        "POPS LF@ord_retval0\n" \
        "LABEL ord_end\n" \
        "PUSHS LF@ord_retval0\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // chr
    printf(
        "LABEL chr\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@chr_arg0\n" \
        "DEFVAR LF@chr_retval0\n" \
        "MOVE LF@chr_retval0 nil@nil\n" \
        "PUSHS string@nil\n" \
        "DEFVAR LF@tmp\n" \
        "TYPE LF@tmp LF@i\n" \
        "PUSHS LF@tmp\n" \
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
        "JUMPIFEQS chr_end_err\n" \
        "PUSHS LF@i\n" \
        "INT2CHARS\n" \
        // toto obidvoje as vymazat
        "POPS LF@chr_retval0\n" \
        "PUSHS LF@chr_retval0\n" \
        "JUMP chr_end\n"\
        "LABEL chr_end_err\n" \
        "PUSHS nil@nil\n"\
        "LABEL chr_end\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // readn
    printf( \
        "LABEL readn\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@readn_retval0\n" \
        "MOVE LF@readn_retval0 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp float\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@float\n" \
        "JUMPIFNEQS readn_end\n" \
        "MOVE LF@readn_retval0 LF@tmp\n" \
        "LABEL readn_end\n" \
        "PUSHS LF@readn_retval0\n" \
        "POPFRAME\n" \
        "RETURN\n\n" \
    );

    // readi
     printf( \
        "LABEL readi\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@readi_retval0\n" \
        "MOVE LF@readi_retval0 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp int\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@int\n" \
        "JUMPIFNEQS readi_end\n" \
        "MOVE LF@readi_retval0 LF@tmp\n" \
        "LABEL readi_end\n" \
        "PUSHS LF@readi_retval0\n" \
        "POPFRAME\n" \
        "RETURN\n\n" \
    );
    
    // reads
    printf( \
        "LABEL reads\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@reads_retval0\n" \
        "MOVE LF@reads_retval0 nil@nil\n" \
        "DEFVAR LF@tmp\n" \
        "DEFVAR LF@type_check\n" \
        "READ LF@tmp string\n" \
        "TYPE LF@type_check LF@tmp\n" \
        "PUSHS LF@type_check\n" \
        "PUSHS string@string\n" \
        "JUMPIFNEQS reads_end\n" \
        "MOVE LF@reads_retval0 LF@tmp\n" \
        "LABEL reads_end\n" \
        "PUSHS LF@reads_retval0\n" \
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
        "MOVE LF@s LF@substr_arg0\n" \
        "DEFVAR LF@i\n" \
        "MOVE LF@i LF@substr_arg1\n" \
        "DEFVAR LF@j\n" \
        "MOVE LF@j LF@substr_arg2\n" \
        "DEFVAR LF@substr_retval0\n" \
        "MOVE LF@substr_retval0 string@\n" \

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
    	  "INT2FLOATS\n" \
	 	  "LTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS substr_end\n" \

        "DEFVAR LF@tmp\n" \
        "STRLEN LF@tmp LF@s\n" \
        "PUSHS LF@j\n" \
        "PUSHS LF@tmp\n" \
        "INT2FLOATS\n" \
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS substr_end\n" \
        
		"PUSHS LF@j\n" \
		"FLOAT2INTS\n" \
		"PUSHS int@1\n" \
		"SUBS\n" \
		"POPS LF@j\n" \
		"PUSHS LF@i\n" \
		"FLOAT2INTS\n" \
		"PUSHS int@1\n" \
		"SUBS\n" \
		"POPS LF@i\n" \
		"GETCHAR LF@substr_retval0 LF@s LF@i\n" \
        "PUSHS int@1\n" \
        "PUSHS LF@i\n" \
        "ADDS\n" \
        "POPS LF@i\n" \

        "LABEL while\n" \
        "PUSHS LF@i\n" \
        "PUSHS LF@j\n" \
        "GTS\n" \
        "PUSHS bool@true\n" \
        "JUMPIFEQS end_while\n" \
        "GETCHAR LF@tmp LF@s LF@i\n" \
        "CONCAT LF@substr_retval0 LF@substr_retval0 LF@tmp\n" \
        "PUSHS int@1\n" \
        "PUSHS LF@i\n" \
        "ADDS\n" \
        "POPS LF@i\n" \
        "JUMP while\n" \

        "LABEL end_while\n" \
        "LABEL substr_end\n" \
        "PUSHS LF@substr_retval0\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    printf(
        "LABEL %%write\n" \
        "PUSHFRAME\n" \
        "DEFVAR LF@print\n" \
        "MOVE LF@print LF@%%write_arg0\n" \
        "DEFVAR LF@type-check\n" \
        "TYPE LF@type-check LF@print\n" \
        "PUSHS string@nil\n" \
        "PUSHS LF@type-check\n" \
        "JUMPIFNEQS not-nil\n" \
        "MOVE LF@print string@nil\n" \
        "LABEL not-nil\n" \
        "WRITE LF@print\n" \
        "POPFRAME\n" \
        "RETURN\n\n");

    // -- write function
    // write(a, 10)
    // "WRITE nazov_premennej_a\n"
    // "WRITE int@10\n"

    // koniec vstavanych funkcii
    printf("LABEL startOfCode\n");
}

void DEFVAR_AND_INIT(char *var_name, char *number)
{
    char *unique_symbol = create_special_name(var_name, number);
    
    printf("DEFVAR %s\n", unique_symbol);
    // MOVE [var_name] nil@nil
    printf("MOVE %s nil@nil\n", unique_symbol);
    
    free(unique_symbol);
}

int PUSHS(char **string, bool flag, Token *token, char *number, bool nill_oc)
{
    int ie;
    char *buffer = NULL;
    char *symbol_gen = symbol_generator(token, number);

	//fprintf(stderr, "tokenvalue: %s\n", token->value);
	//fprintf(stderr, "tokenname: %s\n", token->name);

    if(nill_oc)
    {
        // PUSHS nil@nil
        ie = generate_code(string, "PUSHS string@nil\n", flag); // check if malloc failed in generate_codes
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        buffer = (char *)malloc(sizeof(char) * (strlen("TYPE GF@T-Nvar ") +
                                                      strlen(symbol_gen) +
                                                      strlen("\n") +
                                                      ending_0));
        if (buffer == NULL) // check if malloc failed in CONDITION_START
        {
            return INTERNAL_ERROR;
        }

        // TYPE LF@T-Nvar [symbol_generator(token)]
        sprintf(buffer, "TYPE GF@T-Nvar %s\n", symbol_gen);
        ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }

        // PUSHS GF@T-Nvar
        ie = generate_code(string, "PUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
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
       
    }    

    if (buffer == NULL)
    {
        buffer = (char *)malloc(sizeof(char) * (strlen("PUSHS ") +
                                                strlen(symbol_gen) +
                                                strlen("\n") +
                                                ending_0));
    }
    else
    {
        buffer = (char *)realloc(buffer, sizeof(char) * (strlen("PUSHS ") +
                                                         strlen(symbol_gen) +
                                                         strlen("\n") +
                                                         ending_0));
    }

    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // PUSHS [symbol_generator(token)]
    sprintf(buffer, "PUSHS %s\n", symbol_gen);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int POPS_INFINITE(char **string, bool flag)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * 30);
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    sprintf(buffer, "POPS GF@infinite_void_space\n");
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
}

int POPS(char **string, bool flag, char *var_name, char *number)
{
    char *unique_symbol = create_special_name(var_name, number);
    int len_s = strlen(unique_symbol);

    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS ") +
                                                  len_s +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // POPS [var_name]
    sprintf(buffer, "POPS %s\n", unique_symbol);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    free(unique_symbol);
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

int DIVS(char **string, bool flag)
{
    int ie;    

    // POPS GF@T-Nvar
    ie = generate_code(string, "POPS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSH GF@T-Nvar
    // PUSH GF@T-Nvar
    ie = generate_code(string, "PUSHS GF@T-Nvar\nPUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS int@0
    ie = generate_code(string, "PUSHS float@0x0p+0\n", flag); // check if malloc failed in generate_code
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

    return 0;
}

int IDIVS(char **string, bool flag)
{
    int ie;

    // POPS GF@T-Nvar
    ie = generate_code(string, "POPS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSH GF@T-Nvar
    // PUSH GF@T-Nvar
    ie = generate_code(string, "PUSHS GF@T-Nvar\nPUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
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

    // POPS GF@T-Nsymb2
    ie = generate_code(string, "POPS GF@T-Nsymb2\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // POPS GF@T-Nsymb1
    ie = generate_code(string, "POPS GF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // CONCAT GF@T-Nvar GF@T-Nsymb1 GF@T-Nsymb2
    ie = generate_code(string, "CONCAT GF@T-Nvar GF@T-Nsymb1 GF@T-Nsymb2\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS GF@T-Nvar
    ie = generate_code(string, "PUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    return 0;
}

int STRLEN(char **string, bool flag)
{
    int ie;

    // POPS GF@T-Nsymb1
    ie = generate_code(string, "POPS GF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // STRLEN GF@T-Nvar GF@T-Nsymb1
    ie = generate_code(string, "STRLEN GF@T-Nvar GF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // PUSHS GF@T-Nvar
    ie = generate_code(string, "PUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    return 0;
}

int TOP_I2F(char **string, bool flag, char *number)
{
    int ie;
    ie = generate_code(string, "POPS GF@T-Nsymb1\nPUSHS GF@T-Nsymb1\nTYPE GF@T-Nvar GF@T-Nsymb1\nPUSHS GF@T-Nvar\nPUSHS string@nil\n", flag);
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMPIFEQS var-nil") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed
    {
        return INTERNAL_ERROR;
    }

    sprintf(buffer, "JUMPIFEQS var-nil%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // POPS GF@T-Nsymb1
    // INT2FLOAT GF@T-Nvar GF@T-Nsymb1
    // PUSHS GF@T-Nvar
    ie = generate_code(string, "POPS GF@T-Nsymb1\nINT2FLOAT GF@T-Nvar GF@T-Nsymb1\nPUSHS GF@T-Nvar\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    buffer = (char *)malloc(sizeof(char) * (strlen("LABEL var-nil") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed
    {
        return INTERNAL_ERROR;
    }

    sprintf(buffer, "LABEL var-nil%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    return 0;
}

int BEFORE_TOP_I2F(char **string, bool flag, char *number)
{
    int ie;
    ie = generate_code(string, "POPS GF@T-Nsymb1\nPOPS GF@T-Nsymb2\nPUSHS GF@T-Nsymb2\nPUSHS GF@T-Nsymb1\nTYPE GF@T-Nvar GF@T-Nsymb2\nPUSHS GF@T-Nvar\nPUSHS string@nil\n", flag);
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }
    
    char *buffer = (char *)malloc(sizeof(char) * (strlen("JUMPIFEQS var-nil-2") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed
    {
        return INTERNAL_ERROR;
    }

    sprintf(buffer, "JUMPIFEQS var-nil-2%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    // POPS GF@T-Nsymb1
    // POPS GF@T-Nsymb2
    // INT2FLOAT GF@T-Nvar GF@T-Nsymb2
    // PUSHS GF@T-Nvar
    // PUSHS GF@T-Nsymb1
    ie = generate_code(string, "POPS GF@T-Nsymb1\nPOPS GF@T-Nsymb2\nINT2FLOAT GF@T-Nvar GF@T-Nsymb2\nPUSHS GF@T-Nvar\nPUSHS GF@T-Nsymb1\n", flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    buffer = (char *)malloc(sizeof(char) * (strlen("LABEL var-nil-2") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed
    {
        return INTERNAL_ERROR;
    }

    sprintf(buffer, "LABEL var-nil-2%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    return 0;
}

int CREATEFRAME(char **string, bool flag)
{
    // CREATEFRAME    
    return generate_code(string, "CREATEFRAME\n", flag);
}

int DEFINE_ARG(char **string, char *func_name, char *number, bool flag)
{
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("DEFVAR TF@") +
                                                  strlen(func_name) +
                                                  strlen("_arg") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // DEFVAR TF@[func_name]_arg[number]
    sprintf(buffer, "DEFVAR TF@%s_arg%s\n", func_name, number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }

    free(buffer);
    return 0;
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

int CALL_FUNC_WRITE(char **string, bool flag)
{
	int ie;
	char *buffer = (char *)malloc(sizeof(char)* 100);
	if (buffer == NULL)
	{
		return INTERNAL_ERROR;	
	}
	
	sprintf(buffer, "CREATEFRAME\nDEFVAR TF@%%write_arg0\nPOPS TF@%%write_arg0\nCALL %%write\n");
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
}

void PARAMETERS(char *func_name, char *param_name, int number, char *IDcislo)
{
    printf("DEFVAR LF@C-%s%s\n",IDcislo, param_name);
    printf("MOVE LF@C-%s%s LF@%s_arg%d\n", IDcislo, param_name, func_name, number);
}

void DEF_RETVALS( int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("DEFVAR LF@retval%d\n", i);
        printf("MOVE LF@retval%d nil@nil\n", i);
    }
}

int RETURN_RETVALS(char **string, bool flag, char *number)
{
    //printf("POPS LF@retval%d\n", number);
    int ie;
    char *buffer = (char *)malloc(sizeof(char) * (strlen("POPS LF@retval") +
                                                  strlen(number) +
                                                  strlen("\n") +
                                                  ending_0));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    // LABEL while_[number]
    sprintf(buffer, "POPS LF@retval%s\n", number);
    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }       

    free(buffer);
    return 0;
}

int FUNC_RETURN(char** string, int count, int flag)
{
    int ie;
    int base_len = strlen("POPFRAME\n") + strlen("RETURN\n") + 1;
    char *buffer = (char *)malloc(sizeof(char) * base_len);
    buffer[0] = '\0';
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }

    buffer = (char *)realloc(buffer, sizeof(char) * (base_len + strlen(buffer) + 25));
    if (buffer == NULL) // check if malloc failed in CONDITION_START
    {
        return INTERNAL_ERROR;
    }
    
    for (int i = 0; i < count; i++)
    {
        sprintf(buffer, "PUSHS LF@retval%d\n", i);
		generate_code(string, buffer, flag);
    }

    sprintf(buffer, "POPFRAME\nRETURN\n");

    ie = generate_code(string, buffer, flag); // check if malloc failed in generate_code
    if (ie == INTERNAL_ERROR)
    {
        return ie;
    }       

    free(buffer);
    return 0;
}

void FUNC_END(char *func_name, int count)
{
	for (int i = 0; i < count; i++)
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

int WHILE_CONDITION(char **string, bool flag, char *number, bool n_comp)
{
    int ie;

    if (!n_comp)
    {
        // POPS GF@T-Nsymb1
        // TYPE GF@T-Nvar GF@T-Nsymb1
        // PUSH GF@T-Nvar
        // PUSH string@nil
        // EQS
        // NOTS
        ie = generate_code(string, "POPS GF@T-Nsymb1\nTYPE GF@T-Nvar GF@T-Nsymb1\nPUSHS GF@T-Nvar\nPUSHS string@nil\nEQS\nNOTS\n", flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }
    }

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

int IF_CONDITION(char **string, bool flag, char *number, bool n_comp)
{
    int ie;

    if(!n_comp)
    {
        // POPS GF@T-Nsymb1
        // TYPE GF@T-Nvar GF@T-Nsymb1
        // PUSH GF@T-Nvar
        // PUSH string@nil
        // EQS
        // NOTS
        ie = generate_code(string, "POPS GF@T-Nsymb1\nTYPE GF@T-Nvar GF@T-Nsymb1\nPUSHS GF@T-Nvar\nPUSHS string@nil\nEQS\nNOTS\n", flag); // check if malloc failed in generate_code
        if (ie == INTERNAL_ERROR)
        {
            return ie;
        }
    }    

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

/* End of file code_generator.c */