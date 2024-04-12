#include "minishell.h"


void     test_add(t_input *input, int result, int test_num){
     if (parsing(input) == result)
        printf("\x1b[33m%d\x1b[32m -- Test passed ✅  \x1b[36mtest case --> (%s)\x1b[0m\n", test_num, input->cmds);
    else 
        printf("\x1b[33m%d\x1b[31m -- Test failed 💔  \x1b[31mtest case --> (%s)\x1b[0m\n", test_num, input->cmds);
}


void test_add_exe(char *input_test, char *expected_output, int test_num, char **env) {
     t_input input;
    t_var var;
    t_cmd **cmd;

    ft_memset(&var, 0, sizeof(t_var));
    ft_memset(&input, 0, sizeof(t_input));
    ft_memset(&cmd, 0, sizeof(t_cmd));
    input.env = dup_shell(env);
    add_shlvl(input.env);
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    input.num_of_cmd = 1;
    input.cmds = ft_strdup(input_test);
    if (!input.cmds)
        ft_exit(NULL, &input, &var);
    if (parsing(&input)) {
        cmd = (t_cmd **)ft_calloc(input.num_of_cmd, sizeof(t_cmd));
        cmd[input.num_of_cmd] = NULL;
        tokenize_cmds(&input, cmd, &var);
        if (cmd) {
            // Redirect stdout to a temporary file
            FILE *temp_stdout = freopen("temp_stdout.txt", "w", stdout);

            // Execute the command
            execute(cmd, &input, &var);

            // Close the temporary file
            fclose(temp_stdout);

            // Open the temporary file for reading
            FILE *fp = fopen("temp_stdout.txt", "r");
            if (fp == NULL)
            {
                perror("Error opening file");
                exit(1);
            }

            // Read the contents of the temporary file
            char output[1024]; // Adjust size according to your needs
            fgets(output, sizeof(output), fp);
            // Close the file
            fclose(fp);
            if (strcmp(output, expected_output) == 0) {
                printf("output = %sexpected to be = %s", output, expected_output);
                printf("\x1b[33m%d\x1b[32m -- Test passed ✅  \x1b[36m\n", test_num);
            } else {
                printf("output = %sexpected to be = %s\n", output, expected_output);
                printf("\x1b[33m%d\x1b[31m -- Test failed 💔  \x1b[31m\n", test_num);
            }
        } else {
            exit(1);
        }
    }
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
    // ////////////////////////////////////////////////////
    // test_add_exe("echo \'\"\'","\"\n", 37, env);
    // ////////////////////////////////////////////////////
    // test_add_exe("echo ","\n", 38, env);
    ////////////////////////////////////////////////////
    test_add_exe("echo -n l","l", 39, env);
    ////////////////////////////////////////////////////
    test_add_exe("echo -nnnn l","l", 40, env);
    ////////////////////////////////////////////////////
}
