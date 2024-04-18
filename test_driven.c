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
   input.cmds = ft_strdup("ld | fdgd |");
   test_add(&input, false, 2);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls | ls");
   test_add(&input, true, 3);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls || ls");
   test_add(&input, false, 4);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\'\'");
   test_add(&input, true, 5);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\"\"");
   test_add(&input, true, 6);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\'ls\"");
   test_add(&input, false, 7);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\"ls\"");
   test_add(&input, true, 8);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\"\"\"\'");
   test_add(&input, false, 9);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\"\'\"\'");
   test_add(&input, false, 10);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("\"\'\"\'");
   test_add(&input, false, 11);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls >> k >> k>");
    test_add(&input, false,12);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("$PATH");
    test_add(&input, true,13);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls >> l");
    test_add(&input, true , 14);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls <l");
    test_add(&input, true ,15);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > c >");
    test_add(&input,false , 16);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls |");
    test_add(&input, false, 17);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup(">");
    test_add(&input,false ,18);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("$");
    test_add(&input, true,19);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("$PWD");
    test_add(&input, true,20);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("");
    test_add(&input, true,21);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls\'ls\'");
    test_add(&input, true,22);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls | \"|\" | k");
    test_add(&input, true,23);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls | \"|\" | k |");
    test_add(&input, false,24);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls | \"|\" | k \"\"|");
    test_add(&input, false,25);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls | \"|\" kk");
    test_add(&input, true,26);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls \">\"");
    test_add(&input, true,27);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls \">\" >");
    test_add(&input, false,28);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls >");
    test_add(&input, false,29);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > \"\'\"");
    test_add(&input, true,30);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > \"\"");
    test_add(&input, true,31);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > \"\" | > \"|\"");
    test_add(&input, true,32);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > k | ls > | ");
    test_add(&input, false,33);
    ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls \">>\" k >> k\">\"");
    test_add(&input, true,33);
   ////////////////////////////////////////////////////
   input.cmds = ft_strdup("ls >> l\">\"");
    test_add(&input, true, 34);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls <l");
    test_add(&input, true ,35);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("ls > c \'>\'<");
    test_add(&input, false, 36);
    ////////////////////////////////////////////////////
    input.cmds = ft_strdup("\t ls \t\t\t\t\t\t\t\t\t");
    test_add(&input, true, 37);

}

