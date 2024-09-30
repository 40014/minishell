#include "../minishell.h"


int ft_handle_heredoc2(t_redir_node *red, t_data **data, t_env *envp, t_quots *quots) 
{
    char *str;
    char *temp;
    char *line;
    int fd;
    char *file_name;
    char *id;

    id = ft_itoa(quots->id);
    printf("num id %s\n", id);
    file_name = ft_strjoin("/tmp/heredoc_tmp", id, 1, 1);
    free(id);
    fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror(fd);
        return (-1);
    }
    while (1)
    {
        line = get_next_line(0);
        if (line == NULL)
            break;
        if (ft_find_del(line, red->next->redirection) == 1)
        {
            free(line);
            break;
        }
        temp = ft_expand_herdoc(line, envp, quots);
        write(fd, temp, ft_strlen(temp));
        free(temp);
        free(line);
    }
    close(fd);
    free(red->redirection);
    red->redirection = ft_strdup("<");
    free(red->next->redirection);
    red->next->redirection = file_name;
    return (0);
}

void delete_heredoc_files()
{
    char *file_name;
    char *id;

    int i;
    i = 0;
    while (i < 16)
    {
        id = ft_itoa(i);
        file_name = ft_strjoin("/tmp/heredoc_tmp",id , 1, 1);
        if (access(file_name, F_OK) == 0)
            unlink(file_name);
        else
        {
            free(file_name);
            free(id);
            break;
        }
        free(file_name);
        free(id);
        i++;
    }

}
void ft_exec_heredocs(t_data **data_add , t_env *envp, t_quots *quots)
{
    int i;
    t_data *temp;
    t_redir_node *red;

    temp = *data_add;
    i = 0;
    quots->id = 0;
    while (temp)
    {
        red = temp->redirections;
        while(red)
        {
            if (red->redirection[0] == '<' && red->redirection[1] == '<' && red->redirection[2] == '\0')
            {
                ft_handle_heredoc2(red, envp, data_add, quots);
                 quots->id++;
            }
            red = red->next->next;
        }
        temp = temp->next;
    }
}