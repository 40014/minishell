#include "minishell.h"


t_data *creat_node(char *command, char **arguments)
{
	t_data	*new_node = malloc(sizeof(t_data));
	new_node->command = ft_strdup(command);
	new_node->argumment = arguments;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node(t_data **head, char *command, char **arguments)
{
	t_data	*new_node;
	t_data	*tmp = *head;

	new_node = creat_node(command, arguments);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	ft_count_args(char *input)
{
	int	count;
	int	i;
	char	quote;

	count = 0;
	i  = 0;
	quote = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == ' ' && quote == 0)
		{
			while (input[i] == ' ')
				i++;
            if (input[i] == '\0')
                break;
			count++;
		}
		i++;
	}
	return (count + 1);
}

char *strsplit_by_pipe(char **str)
{
    char	*start;
    char	*pipe_pos;
    char	quote;
    int	i;

	start = *str;
	pipe_pos = NULL;
	quote = 0;
	i = 0;
    if (start == NULL)
        return NULL;
    while (start[i] != '\0')
    {
        if (start[i] == '\'' || start[i] == '"')
        {
            // Toggle quote tracking
            if (quote == 0)
                quote = start[i];
            else if (quote == start[i])
                quote = 0;
        }
        else if (start[i] == '|' && quote == 0)
        {
            // Found a pipe outside of quotes
            pipe_pos = &start[i];
            break;
        }
        i++;
    }
    if (pipe_pos != NULL)
    {
        *pipe_pos = '\0';  // Replace pipe with null terminator to isolate the current segment
        *str = pipe_pos + 1;  // Update the pointer to the position after the pipe
    }
    else
        *str = NULL;  // No more pipes, so set str to NULL
    return (start);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		j;
	char	*dup;

	dup = malloc ((ft_strlen(s1) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
	{
		dup[j] = s1[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}
