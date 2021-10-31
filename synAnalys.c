#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "scanner.c"
#include "error.h"




enum STATE {assign, assigns, arg, args, exp, item, item_n, init, init_value, prog, prog_con, par_type, ret_val, ret_type, st_list, type, types, value, values, params, params_n};





bool synAnalys(Token *token, enum STATE state){
    
    if(state == prog){
        if(token->name == "keyword" && token->value == "require"){
            read_token(token);

        }
        else{
            
        }
    }




}




int main(){

    enum STATE state = prog;


    Token *token = malloc(sizeof(Token));
    
    //printf("Syn analys: %d", read_token(token));  
    bool output = synAnalys(token, state);


    return 0;
}