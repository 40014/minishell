#include "../minishell.h"


int ft_handle_output(char *argument, int i)
{
    char *file_name;
    int j;
    int output_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    output_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (output_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(output_fd, STDOUT_FILENO);
    close(output_fd);
    free(file_name);
    return (i);
}

int ft_handle_input(char *argument, int i)
{
    char *file_name;
    int j;
    int input_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    input_fd = open(file_name, O_RDONLY);
    if (input_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(input_fd, STDIN_FILENO);
    close(input_fd);
    free(file_name);
    return (i);
}
int ft_handle_append(char *argument, int i)
{
    char *file_name;
    int j;
    int append_fd;

    file_name = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    append_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644  );
    if (append_fd < 0)
    {
        perror(file_name);
        free(file_name);
        return (-1);
    }
    dup2(append_fd, STDOUT_FILENO);
    close(append_fd);
    free(file_name);
    return (i);
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
int ft_handle_heredoc(char *argument, int i) {
    char *str;
    char *temp;
    char *line;
    char *delimiter;
    int fd;

    delimiter = ft_cpy_commande(argument, i + 1);
    while (argument[i + 1] && argument[i + 1] != '>' && argument[i + 1] != '<')
        i++;
    fd = open("/tmp/heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (fd == -1)
    {
        perror(fd);
        free(delimiter);
        return (-1);
    }
    while (1)
    {
        line = get_next_line(0);
        if (line == NULL)
        {
            break;
        }
        if (ft_find_del(line, delimiter) == 1)
        {
            free(line);
            break;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
    close(fd);
    free(delimiter);
    fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (fd == -1)
    {
        perror(fd);
        return (-1);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return (-1);
    }
    close(fd);
    return i;
}
