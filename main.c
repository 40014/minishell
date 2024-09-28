#include "minishell.h"

void print_use_list(t_data *head) // for testing
{
    t_data *temp = head;
    int i = 0;
    while (temp)
    {
        while (temp->redirection[i] != NULL)
        {
            printf("redirection %d:%s\n", i, temp->redirection[i]);
            i++;
        }
        i = 0;
        printf("--------------------------\n");
        while (temp->argumment[i] != NULL)
        {
            printf("Arg %d:%s\n", i, temp->argumment[i]);
            i++;
        }
        i = 0;
        temp = temp->next;
        if (temp)
        {
            printf("---- Next node ----\n");
        }
    }
}

int exit_code ;

int main(int arc, char **arv, char **envp)
{
    t_data *data;
    t_env *env_var;
    t_hold *hold_vars;
    t_quots quots;
    char *input;
    int i;
    int saved_stdout;
    int saved_stdin;
    char *temp;
    
    if (arc > 1)
        return (1);
    env_var = env_to_list(envp);
    hold_vars = malloc(sizeof(t_hold));
    quots.x = 0;
    data = NULL;
    while (1)
    {
        saved_stdout = dup(STDOUT_FILENO);
        saved_stdin = dup(STDIN_FILENO);
        input = readline(temp = print_prompt(env_var, NULL, NULL));
        if (check_prompt(input) != 0)
        {
            add_history(input);
            if (((i = parse_line(&data, input, env_var, &quots)) == 0 || i == 2)  && quots.empty != 2)
            {
                if (i == 2)
                {
                    free(temp);
                    exit(exit_code);
                }
                print_use_list(data);
                hold_vars->input = input;
                hold_vars->temp = temp;
                quots.saved_stdin = saved_stdin;
                exec_commandes(&env_var, &data, &hold_vars, &quots);
                dup2(saved_stdout, STDOUT_FILENO);
                dup2(saved_stdin, STDIN_FILENO);
                close(saved_stdout);
                close(saved_stdin);
            }
        }
        ft_free_list(data);
        data = NULL;
        quots.x = 0;
        free(temp);
        free(input);
    }
}
