#include "../minishell.h"

int create_pipes(t_data *temp, t_env **env, t_quots *quots, t_hold **hold_vars)
{
    int pid;

    if ((pid = fork()) == -1)
    {
        perror("Error creating new process");
        exit(1);
    }
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        if (quots->fdin != 0)
        {
            dup2(quots->fdin, 0);
            close(quots->fdin);
        }
        if (quots->fdout != 1)
        {
            dup2(quots->fdout, 1);
            close(quots->fdout);
        }
        exit(exec_simple_commande(quots, env, &temp, hold_vars));
    }
    return(pid);
}
void get_last_child_exit_code(int pid)
{
    int exit_status;
    int status;

    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    waitpid(pid, &exit_status, 0);
    while (wait(&status) > 0);
    if (WIFEXITED(exit_status) != 0)
        exit_code = WEXITSTATUS(exit_status);
    else if (WIFSIGNALED(status) != 0)
        exit_code = WTERMSIG(status);
    signal(SIGINT, handlle_sigint);
    signal(SIGQUIT, SIG_DFL);
}
void exec_with_pipes(t_env **envp, t_data **data, t_hold **hold_vars, t_quots *quots)
{
    t_data *temp;
    int fd[2];
    int pid;
    int count;

    temp = *data;
    quots->fdin = 0;
    while (temp)
    {
        if (temp->next != NULL)
        {
            if (pipe(fd) == -1)
            {
                perror("Error creating pipe");
                exit(1);
            }
        }
        else
            quots->fdout = 1;
        quots->fdout = fd[1];
        pid  = create_pipes(temp, envp, quots, hold_vars);
        if (quots->fdin != 0)
            close(quots->fdin);
        if (quots->fdout != 1)
            close(quots->fdout);
        quots->fdin = fd[0];
        temp = temp->next;
    }
    get_last_child_exit_code(pid);
}
