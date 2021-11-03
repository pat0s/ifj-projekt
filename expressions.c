
#include "expressions.h"


int precence_table[TABLE_SIZE][TABLE_SIZE] =
{
//     +,- | *,/,// | .. |   #  |  i   |  RO  |  (   |   )  | string | $  
    { REDUC, SHIFT, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, EMPTY, REDUC },   // +,-
    { REDUC, REDUC, EMPTY, SHIFT, SHIFT, REDUC, SHIFT, REDUC, EMPTY, REDUC },   // *, /, //
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, SHIFT, REDUC },   // .. 
    { REDUC, REDUC, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, EMPTY, SHIFT, REDUC },   // #
    { REDUC, REDUC, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // i - id, number, int
    { SHIFT, SHIFT, EMPTY, SHIFT, SHIFT, EMPTY, SHIFT, REDUC, EMPTY, REDUC },   // RO - relational operators ( >, <, <=, >=, ==, ~=, )
    { SHIFT, SHIFT, EMPTY, SHIFT, SHIFT, SHIFT, SHIFT, EQUAL, EMPTY, EMPTY },   // (
    { REDUC, REDUC, REDUC, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // )
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, REDUC, EMPTY, REDUC, EMPTY, REDUC },   // string
    { SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, SHIFT, EMPTY, SHIFT, EMPTY }    // $
}

/* End of file expressions.c */