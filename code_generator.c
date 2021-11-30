#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "code_generator.h"
#include "error.h"

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

void dyn_string_init(TDynString *dyn_string)
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
    
    dyn_string->length += strlen(code) + n_plus_0;
    dyn_string->string = (char *)realloc(dyn_string->string, dyn_string->length * sizeof(char));
       
    if (dyn_string->string == NULL) return INTERNAL_ERROR; 
    
    return 0;
}



void generate_code(TDynString *dyn_string, char *code, bool flag)
{
    if (flag){
        // Reallocation
        int error = dyn_string_realloc(dyn_string, code);
        
        // Internal error during reallocation
        if (error == INTERNAL_ERROR)
        {
            // TODO nejako to poriesit
        }

        // Concatenation
        strcat(dyn_string->string, code);
        strcat(dyn_string->string, "\n");
    }            
    else
    {
        printf("%s\n", code);
    }
}

int main()
{
    // Asi bude potrebna aj alokacia struktury, kedze sa to bude pouzivat vsade
    // to pridam zajtra ked tak
    TDynString dyn_string;
    dyn_string_init(&dyn_string);

    generate_code(&dyn_string, "Lenovo", true);
    generate_code(&dyn_string, "320", true);
    generate_code(&dyn_string, "ideapad", true);
    generate_code(&dyn_string, "Trust", true);    
    generate_code(&dyn_string, "dawd", true);
    generate_code(&dyn_string, "gwfqw", true);
    printf("%s", dyn_string.string);
    return 0;
}