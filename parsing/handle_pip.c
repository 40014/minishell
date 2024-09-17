#include "../minishell.h"

char ft_handle_quote(char current_chara, char quotee)
{
    if (current_chara == '\'' || current_chara == '"')
    {
        if (quotee == 0)
            return (current_chara);
        else if (quotee == current_chara)
            return (0);
    }
    return (quotee);
}

int find_pipe_position(char *start, char *quote)
{
    int i = 0;

    while (start[i] != '\0')
    {
        *quote = ft_handle_quote(start[i], *quote);
        if (start[i] == '|' && *quote == 0)
            return(i);
        i++;
    }
    return (-1);
}

char *strsplit_by_pipe(char **str)
{
    char *start;
    char *pipe_pos;
    char quote;
    int pipe_index;

    start = *str;
    pipe_pos = NULL;
    quote = 0;
    if (start == NULL)
        return NULL;
    pipe_index = find_pipe_position(start, &quote);
    if (pipe_index != -1)
        pipe_pos = &start[pipe_index];
    if (pipe_pos != NULL)
    {
        *pipe_pos = '\0';
        *str = pipe_pos + 1;
    }
    else
        *str = NULL; 
    return start;
}
