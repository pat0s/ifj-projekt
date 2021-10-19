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
            else if (symbol == ':')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return token;
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
                return token;
            }
            else if (symbol == '#')
            {
                token->name[0] = symbol;
                token->name[1] = '\0';
                return token;
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
                token_allocation(token);
                token->value[0] = symbol;
                token->value[1] = '\0';
                strcpy(state, "f19");
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[0] = symbol;
                token->value[1] = '\0';
                strcpy(state, "f21");
            }
            else if (symbol == '\"')
            {
                strcpy(state, "p6");
            }
            else if (symbol == ' ' || symbol == '\n')
            {
                // iba navrat do s, nic sa nestane
            }
            else
            {
                // TODO return error
            }
        }
        else if (!strcmp(state, "f2"))
        {
            // TODO kontrola
            if (symbol == '-')
            {
                strcpy(state, "p10");
            }
            else
            {
                ungetc(symbol, stdin);
                return token;
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
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f17");    // ?
                return token;
            }
            else
            {
                ungetc(symbol, stdin);
                return token;
            }
        }
        else if (!strcmp(state, "p1"))
        {
            if (symbol == '.')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f10");    // ?
                return token;
            }
            else
            {
                // TODO return error
            }
        }
        else if (!strcmp(state, "f13"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f14");    // ?
                return token;
            }
            else
            {
                // TODO: return error
            }
        }
        else if (!strcmp(state, "f15"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f16");    // ?
                return token;
            }
            else
            {
                ungetc(symbol, stdin);
                return token;
            }
        }
        else if (!strcmp(state, "p2"))
        {
            if (symbol == '=')
            {
                int pos = strlen(token->name);
                token->name[pos] = symbol;
                token->name[pos+1] = '\0';
                strcpy(state, "f18");    // ?
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
        else if (!strcmp(state, "f21"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
            }
            else if (symbol == 'e' || symbol == 'E')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p4");
            }
            else if (symbol == '.')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p3");	
            }
            else
            {
                strcpy(token->name, "int"); // nazov?
                ungetc(symbol, stdin);
                return token;
            }
        }
        else if (!strcmp(state, "p3"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "f22");	
            }
            else
            {
                // TODO return error
            }
        }
        else if (!strcmp(state, "p4"))
        {
            if (symbol == '+' || symbol == '-')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p5");
            }
            else if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "f23");
            }
            else
            {
                //TODO return error
            }
        }
        else if (!strcmp(state, "f22"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
            }
            else if(symbol == 'e' || symbol == 'E')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p4");
            }
            else
            {
                ungetc(symbol, stdin);
                strcpy(token->name, "float"); // nazov ?
                return token;
            }
        }
        else if (!strcmp(state, "p5"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "f23");
            }
            else
            {
                // TODO return error
            }
        }
        else if (!strcmp(state, "f23"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
            }
            else
            {
                ungetc(symbol, stdin);
                strcpy(token->name, "exponent"); // nazov ?
                return token;
            }
        }
        else if (!strcmp(state, "p6"))
        {
            if (symbol < 32)
            {
                // TODO return error
            }
            else if (symbol == '\"')
            {
                strcpy(state, "f24"); // ?
                strcpy(token->name, "string"); // nazov ?
                return token;
            }
            else if (symbol == '\\')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p7");
            }
            else
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
            }
        }
        else if (!strcmp(state, "p7"))
        {
            if (symbol == '\\' || symbol == 't' || symbol == '\"' || symbol == '\\')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p6");
            }
            else if (symbol >= '0' && symbol <= '2')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p8");
            }
            else
            {
                // TODO return error
            }
        }
        if (!strcmp(state, "p8"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p9");
            }
            else
            {
                // TODO return error
            }
        }
        if (!strcmp(state, "p9"))
        {
            if (symbol >= '0' && symbol <= '9')
            {
                token_allocation(token);
                token->value[token->value_len-2] = symbol;
                token->value[token->value_len-1] = '\0';
                strcpy(state, "p6");
            }
            else
            {
                // TODO return error
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
