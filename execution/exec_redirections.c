#include "../minishell.h"

int ft_handle_output(char *file_name)
{
    int output_fd;

    output_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (output_fd < 0)
    {
        perror(file_name);
        return (-1);
    }
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    return (0);
}

int ft_handle_input(char *file_name)
{
    int input_fd;

    input_fd = open(file_name, O_RDONLY);
    if (input_fd < 0)
    {
        perror(file_name);
        return (-1);
    }
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    return (0);
}
int ft_handle_append(char *file_name)
{
    int j;
    int append_fd;

    append_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (append_fd < 0)
    {
        perror(file_name);
        return (-1);
    }
    dup2(append_fd, STDOUT_FILENO);
    close(append_fd);
    return (0);
}
int ft_find_del(char *line, char *del)
{
    int i;

    i = 0;
    while( line[i] != '\n' && del[i] && line[i] == del[i])
        i++;

    if (line[i] == '\n' && del[i] == '\0')
        return(1);
    return(0);
}

int ft_handle_heredoc(char *delimiter, t_env *envp, t_quots *quots) 
{
    char *str;
    char *temp;
    char *line;
    int fd;

    fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror(fd);
        return (-1);
    }
   /// signal(SIGINT,  SIG_DFL);
    while (1)
    {
        line = get_next_line(0);
        if (line == NULL)
            break;
        if (ft_find_del(line, delimiter) == 1)
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
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd == -1)
    {
        perror(fd);
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) 
    {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return (0);
}
