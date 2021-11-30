#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define n_plus_0 2 // need to alocate space for characters \n and \0 

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

void generate_code(char *string, char *code, bool flag)
{
    if (flag){
        string = (char *)realloc(string, strlen(code)*sizeof(char) + n_plus_0);
        strcat(string, code);
        strcat(string, "\n");
    }            
    else
    {
        printf("%s\n", code);
    }
}

int main(){    
    char *while_string = (char *)malloc(sizeof(char));
    generate_code(while_string, "Lenovo", true);
    generate_code(while_string, "320", true);
    generate_code(while_string, "ideapad", true);
    generate_code(while_string, "Trust", true);    
    generate_code(while_string, "dawd", true);
    generate_code(while_string, "gwfqw", true);
    printf("%s", while_string);
    return 0;
}