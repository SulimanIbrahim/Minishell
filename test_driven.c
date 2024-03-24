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
    input.cmds = ft_strdup("|");

   test_add(&input, false, 1);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ld | fdgd |");
   test_add(&input, false, 2);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls | ls");
   test_add(&input, true, 3);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls || ls");
   test_add(&input, false, 4);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\'\'");
   test_add(&input, true, 5);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\"\"");
   test_add(&input, true, 6);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\'ls\"");
   test_add(&input, false, 7);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\"ls\"");
   test_add(&input, true, 8);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\"\"\"\'");
   test_add(&input, false, 9);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\"\'\"\'");
   test_add(&input, false, 10);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("\"\'\"\'");
   test_add(&input, false, 11);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls >> k >> k>");
    test_add(&input, false,12);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("$PATH");
    test_add(&input, true,13);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls >> l");
    test_add(&input, true , 14);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls <l");
    test_add(&input, true ,15);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > c >");
    test_add(&input,false , 16);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls |");
    test_add(&input, false, 17);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup(">");
    test_add(&input,false ,18);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("$");
    test_add(&input, true,19);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("$PWD");
    test_add(&input, true,20);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("");
    test_add(&input, true,21);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls\'ls\'");
    test_add(&input, true,22);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls | \"|\" | k");
    test_add(&input, true,23);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls | \"|\" | k |");
    test_add(&input, false,24);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls | \"|\" | k \"\"|");
    test_add(&input, false,25);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls | \"|\" kk");
    test_add(&input, true,26);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls \">\"");
    test_add(&input, true,27);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls \">\" >");
    test_add(&input, false,28);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls >");
    test_add(&input, false,29);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > \"\'\"");
    test_add(&input, true,30);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > \"\"");
    test_add(&input, true,31);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > \"\" | > \"|\"");
    test_add(&input, true,32);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > k | ls > | ");
    test_add(&input, false,33);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls \">>\" k >> k\">\"");
    test_add(&input, true,33);
   ////////////////////////////////////////////////////
    free_all(NULL, &input);
   input.cmds = ft_strdup("ls >> l\">\"");
    test_add(&input, true, 34);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls <l");
    test_add(&input, true ,35);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
    input.cmds = ft_strdup("ls > c \'>\'<");
    test_add(&input, false, 36);
    ////////////////////////////////////////////////////
    free_all(NULL, &input);
}

