#ifndef _CODE_GENERATOR_H_
#define _CODE_GENERATOR_H_

typedef struct dynString
{
    char *string;
    int length;
} TDynString;

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

// funkce parameter integer, return ukazatel na string

#endif