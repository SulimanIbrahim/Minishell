#include "minishell.h"


void     test_add(t_input *input, int result, int test_num){
     if (parsing(input) == result)
        printf("\x1b[33m%d\x1b[32m -- Test passed ✅  \x1b[36mtest case --> (%s)\x1b[0m\n", test_num, input->cmds);
    else 
        printf("\x1b[33m%d\x1b[31m -- Test failed 💔  \x1b[31mtest case --> (%s)\x1b[0m\n", test_num, input->cmds);

}

int main(int ac, char **av, char **env){

    t_input input;

    (void)av;
	(void)ac;
    input.env = env;
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
   input.cmds = "ls >> k >> k>\0";
    test_add(&input, false,12);
   ////////////////////////////////////////////////////
   input.cmds = "$PATH\0";
    test_add(&input, true,13);
   ////////////////////////////////////////////////////
   input.cmds = "ls >> l\0";
    test_add(&input, true , 14);
    ////////////////////////////////////////////////////
    input.cmds = "ls <l\0";
    test_add(&input, true ,15);
    ////////////////////////////////////////////////////
    input.cmds = "ls > c >\0";
    test_add(&input,false , 16);
    ////////////////////////////////////////////////////
    input.cmds = "ls |\0";
    test_add(&input, false, 17);
    ////////////////////////////////////////////////////
    input.cmds = ">\0";
    test_add(&input,false ,18);
    ////////////////////////////////////////////////////
    input.cmds = "$\0";
    test_add(&input, true,19);
    ////////////////////////////////////////////////////
    input.cmds = "$PWD\0";
    test_add(&input, true,20);
    ////////////////////////////////////////////////////
    input.cmds = "\0";
    test_add(&input, true,21);
    ////////////////////////////////////////////////////
    input.cmds = "ls\'ls\'\0";
    test_add(&input, true,22);
    ////////////////////////////////////////////////////
    input.cmds = "ls | \"|\" | k\0";
    test_add(&input, true,23);
    ////////////////////////////////////////////////////
    input.cmds = "ls | \"|\" | k |\0";
    test_add(&input, false,24);
    ////////////////////////////////////////////////////
    input.cmds = "ls | \"|\" | k \"\"|\0";
    test_add(&input, false,25);
    ////////////////////////////////////////////////////
    input.cmds = "ls | \"|\" kk\0";
    test_add(&input, true,26);
    ////////////////////////////////////////////////////
    input.cmds = "ls \">\"\0";
    test_add(&input, true,27);
    ////////////////////////////////////////////////////
    input.cmds = "ls \">\" >\0";
    test_add(&input, false,28);
    ////////////////////////////////////////////////////
    input.cmds = "ls >\0";
    test_add(&input, false,29);
    ////////////////////////////////////////////////////
    input.cmds = "ls > \"\'\"\0";
    test_add(&input, true,30);
    ////////////////////////////////////////////////////
    input.cmds = "ls > \"\"\0";
    test_add(&input, true,31);
    ////////////////////////////////////////////////////
    input.cmds = "ls > \"\" | > \"|\"\0";
    test_add(&input, true,32);
    ////////////////////////////////////////////////////
    input.cmds = "ls > k | ls > | \0";
    test_add(&input, false,33);
}

