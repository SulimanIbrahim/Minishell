#include "minishell.h"


void     test_add(t_input *input, int test_num){
     if (parsing(input) == true)
        printf("%d Test passed 😀\n", test_num);
    else 
        printf("%d Test failed 😱\n", test_num);
}

int main(){

    t_input input;

    input.cmds = "|\0";
   test_add(&input, 1);
   input.cmds = "ld | fdgd |\0";
   test_add(&input,2);
   input.cmds = "ls | ls\0";
   test_add(&input,3);
   input.cmds = "ls || ls\0";
   test_add(&input,4);
}