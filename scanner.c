#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

const char keywords[][9] = {"do", "else", "end", "function", "global", "if", "local", "nil", "require", "return", "then", "while"};


typedef struct Token
{
    char name[20];
    char *value;
    int value_len;
} Token;


void* token_inicialization(Token *token)
{
    token->value = NULL;
    token->value_len = 0;
}


void* token_allocation(Token *token)
{
    if (token->value)
    {
        token->value_len++;
        token->value = realloc(token->value, (token->value_len)*sizeof(char));
        // TODO osetrenie
    }
    else
    {
        token->value = (char*)malloc(2*sizeof(char));
        token->value_len = 2;
        // TODO osetrenie
    }
}


bool check_keyword(const char *unknown)
{
    for (int i = 0; i < 12; i++)
    {
        if (!strcmp(unknown, keywords[i]))
        {
            return true;
        }
    }
    return false;
}


Token* read_token()
{
    Token *token = (Token*) malloc(sizeof(Token));
    // TODO osetrenie
    token_inicialization(token);

    char state[4] = "s";
    int symbol;

    while((symbol = getchar()) != EOF)
    {
        if (!strcmp(state, "s"))
        {
            if (symbol == '+')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return token;
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
                return token;
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
                return token;
            }
            else if (symbol == '(')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return token;
            }
            else if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || symbol == '_')
            {
                token_allocation(token);
                token->value[0] = symbol;
                token->value[1] = '\0';
                strcpy(state, "f19");
            }
        }
        else if (!strcmp(state, "f4"))
        {
            if (symbol == '/')
            {
                token_allocation(token);
                token->name[token->value_len-1] = symbol;
                token->name[token->value_len] = '\0';
                strcpy(state, "f5");    // ?
                return token;
            }
            else
            {
                ungetc(symbol, stdin);
                return token;
            }
        }
        else if (!strcmp(state, "f6"))
        {
            if (symbol == '=')
            {
                token_allocation(token);
                token->name[token->value_len-2] = symbol;
                token->name[token->value_len-1] = '\0';
                strcpy(state, "f17");    // ?
                return token;
            }
            else
            {
                ungetc(symbol, stdin);
                return token;
            }
        }
        else if (!strcmp(state, "f19"))
        {
            if((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z') || (symbol >= '0' && symbol <= '9') || symbol == '_')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
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
                return token;
            }          
        }
    }  // end while
}

// TODO: vymazat, iba na ucely testovania
int main()
{
    Token *token = read_token();
    if (token->name)
        printf("name: %s\n", token->name);
    if (token->value)
    {
        printf("value: ");
        for (int i = 0; i < token->value_len-1; i++)
            printf("%c", token->value[i]);
    }
        
    return 0;
}
