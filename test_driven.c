#include "minishell.h"


void     test_add(t_input *input, int result, int test_num){
     if (parsing(input) == result)
        printf("%d\x1b[32m Test passed 😀\x1b[0m\n", test_num);
    else 
        printf("%d\x1b[31mTest failed 😱\x1b[0m\n", test_num);
}

int main(){

    t_input input;

    input.cmds = "|\0";
   test_add(&input, false, 1);
    ////////////////////////////////////////////////////
   input.cmds = "ld | fdgd |\0";
   test_add(&input, false, 2);
   ////////////////////////////////////////////////////
   input.cmds = "ls | ls\0";
   test_add(&input, true, 3);
   ////////////////////////////////////////////////////
   input.cmds = "ls || ls\0";
   test_add(&input, false, 4);
   ////////////////////////////////////////////////////
   input.cmds = "\'\'\0";
   test_add(&input, true, 5);
   ////////////////////////////////////////////////////
   input.cmds = "\"\"\0";
   test_add(&input, true, 6);
   ////////////////////////////////////////////////////
   input.cmds = "\'ls\"\0";
   test_add(&input, false, 7);
   ////////////////////////////////////////////////////
   input.cmds = "\"ls\"\0";
   test_add(&input, true, 8);
   ////////////////////////////////////////////////////
   input.cmds = "\"\"\"\'\0";
   test_add(&input, false, 9);
   ////////////////////////////////////////////////////
   input.cmds = "\"\'\"\'\0";
   test_add(&input, false, 10);
   ////////////////////////////////////////////////////
   input.cmds = "\"\'\"\'\0";
   test_add(&input, false, 11);
   ////////////////////////////////////////////////////
}