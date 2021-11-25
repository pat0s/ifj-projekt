/**
 * @file scanner.c
 * 
 * @brief Implementation of Scanner
 * @author Patrik Sehnoutek, xsehno01
 */

#include "scanner.h"
#include "error.h"
#include <string.h>

const char keywords[][9] = {"do", "else", "end", "function", "global", "if", "local", "nil", "require", "return", "then", "while", "string", "integer", "number"};


/**
 * @brief Function for token initialisation
 * 
 * @param token Pointer to token struct
 */
void token_initialisation(Token *token)
{
    token->value = NULL;
    token->value_len = 0;
}


/**
 * @brief Function for token allocation
 * 
 * @param token Pointer to token struct
 */
void token_allocation(Token *token)
{
    if (token->value)
    {
        token->value_len++;
        token->value = realloc(token->value, (token->value_len)*sizeof(char));
    }
    else
    {
        token->value = (char*)malloc(2*sizeof(char));
        token->value_len = 2;
    }
}


/**
 * @brief Function to check if the given string literal is keyword
 * 
 * @param unknown Pointer to loaded string literal
 * @returns True/False
 */
bool check_keyword(const char *unknown)
{
    for (int i = 0; i < KEYWORDS_SIZE; i++)
    {
        if (!strcmp(unknown, keywords[i]))
        {
            return true;
        }
    }
    return false;
}


/**
 * @brief Function for adding new symbol to token value 
 * 
 * @param token Pointer to token struct
 * @param symbol Loaded character
 * @returns True/False
 */
bool add_symbol(Token *token, char symbol)
{
    token_allocation(token);
    if (token->value == NULL)
    {
        return false;
    }
    
    token->value[token->value_len-2] = symbol;
    token->value[token->value_len-1] = '\0';

    return true;
}

/**
 * @brief Implemented Finite State Machine (FSM)
 * 
 * @returns Error code
 */
int read_token(Token *token)
{
    token_initialisation(token);

    char state[4] = "s";
    int symbol;

    do
    {
        // Read char from stdin
        
        symbol = getchar();

        if (!strcmp(state, "s"))
        {
            if (symbol == '+')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '-')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                strcpy(state, "f2");
            }
            else if (symbol == '*')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '/')
            {
                strcpy(state, "f4");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if (symbol == '=')
            {
                strcpy(state, "f6");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if (symbol == ')')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '(')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == ':')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '.')
            {
                strcpy(state, "p1");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if (symbol == ',')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '#')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return 0;
            }
            else if (symbol == '<')
            {
                strcpy(state, "f13");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if (symbol == '>')
            {
                strcpy(state, "f15");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if (symbol == '~')
            {
                strcpy(state, "p2");
                token->name[0] = symbol;
                token->name[1] = '\0';
            }
            else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == '_')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "f19");
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "f21");
            }
            else if (symbol == '\"')
            {
                strcpy(state, "p6");
            }
            else if (symbol == ' ' || symbol == '\n' || symbol == '\t')
            {
                strcpy(state, "s");
            }
            else if (symbol == EOF)
            {
                strcpy(token->name, "-1"); 
                return 0;
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "f2"))
        {
            if (symbol == '-')
            {
                strcpy(state, "p10");
            }
            else
            {
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "p10"))
        {
            if (symbol == '[')
            {
                strcpy(state, "p12");
            }
            else if (symbol == '\n')
            {
                strcpy(state, "s");
            }
            else
            {
                strcpy(state, "p11");
            } 
        }
        else if (!strcmp(state, "p11"))
        {
            if (symbol == '\n')
            {
                strcpy(state, "s");
            }
        }
        else if (!strcmp(state, "p12"))
        {
            if (symbol == '[')
            {
                strcpy(state, "p13");
            }
            else if (symbol == '\n')
            {
                strcpy(state, "s");
            }
            else
            {
                strcpy(state, "p11");
            }
        }
        else if (!strcmp(state, "p13"))
        {
            if (symbol == ']')
            {
                strcpy(state, "p14");
            }
        }
        else if (!strcmp(state, "p14"))
        {
            if (symbol == ']')
            {
                strcpy(state, "s");
            }
            else
            {
                strcpy(state, "p13");
            }       
        }
        else if (!strcmp(state, "f4"))
        {
            if (symbol == '/')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f5");
                return 0;
            }
            else
            {
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "f6"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f17");
                return 0;
            }
            else
            {
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "p1"))
        {
            if (symbol == '.')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f10");
                return 0;
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "f13"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f14");
                return 0;
            }
            else
            {
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "f15"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f16");
                return 0;
            }
            else
            {
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "p2"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f18");
                return 0;
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "f19"))
        {
            if((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') || symbol == '_')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
            }
            else
            {
                ungetc(symbol, stdin);
                if (check_keyword(token->value))
                {
                    strcpy(token->name, "keyword");
                }
                else
                {
                    strcpy(token->name, "identifier");
                }
                return 0;
            }          
        }
        else if (!strcmp(state, "f21"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
            }
            else if (symbol == 'e' || symbol == 'E')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p4");
            }
            else if (symbol == '.')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p3");	
            }
            else
            {
                strcpy(token->name, "int");
                ungetc(symbol, stdin);
                return 0;
            }
        }
        else if (!strcmp(state, "p3"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "f22");	
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "p4"))
        {
            if (symbol == '+' || symbol == '-')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p5");
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "f23");
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "f22"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
            }
            else if(symbol == 'e' || symbol == 'E')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p4");
            }
            else
            {
                ungetc(symbol, stdin);
                strcpy(token->name, "number");
                return 0;
            }
        }
        else if (!strcmp(state, "p5"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "f23");
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "f23"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
            }
            else
            {
                ungetc(symbol, stdin);
                strcpy(token->name, "number");
                return 0;
            }
        }
        else if (!strcmp(state, "p6"))
        {
            if (symbol < 32)
            {
                return LEX_ERROR;
            }
            else if (symbol == '\"')
            {
                strcpy(state, "f24");
                strcpy(token->name, "string");
                return 0;
            }
            else if (symbol == '\\')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p7");
            }
            else
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
            }
        }
        else if (!strcmp(state, "p7"))
        {
            if (symbol == 'n' || symbol == 't' || symbol == '\"' || symbol == '\\')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p6");
            }
            else if (symbol >= '0' && symbol <= '2')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p8");
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "p8"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p9");
            }
            else
            {
                return LEX_ERROR;
            }
        }
        else if (!strcmp(state, "p9"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                if (!add_symbol(token, symbol))
                    return INTERNAL_ERROR;
                strcpy(state, "p6");
            }
            else
            {
                return LEX_ERROR;
            }
        }
    }  // end do-while
    while(symbol != EOF);

    return 0;
}

/* End of file scanner.c */
