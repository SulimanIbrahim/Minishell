#include "minishell.h"


void     test_add(t_input *input, int test_num){
     if (parsing(input) == true)
        printf("%d Test passed 😀 with \"%s\" \n", test_num, input->cmds);
    else 
        printf("%d Test failed 😱 with \"%s\" \n", test_num, input->cmds);
}

int main(int ac, char **av, char **env){

    t_input input;

    (void)av;
	(void)ac;
    input.env = env;
    input.cmds = "|\0";
    test_add(&input, 1);
    input.cmds = "ld | fdgd |\0";
    test_add(&input,2);
    input.cmds = "ls | ls\0";
    test_add(&input,3);
    input.cmds = "ls || ls\0";
    test_add(&input,4);
    input.cmds = "ls >> l\0";
    test_add(&input,5);
    input.cmds = "ls <l\0";
    test_add(&input,6);
    input.cmds = "ls > c >\0";
    test_add(&input,7);
    input.cmds = "ls |\0";
    test_add(&input,8);
    input.cmds = ">\0";
    test_add(&input,9);
    input.cmds = "$\0";
    test_add(&input,10);
    input.cmds = "$PWD\0";
    test_add(&input,11);
    input.cmds = "\0";
    test_add(&input,12);
}