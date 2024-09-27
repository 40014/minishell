#include "../minishell.h"

void ft_printf_error(int i)
{
	if (i == 2 || i == 3)
	{
		if (i == 2)
			printf("unexpected EOF while looking for matching `\'' \n");
		else
			printf("unexpected EOF while looking for matching `\"' \n");
	}
	else
		printf("minishell: syntax error near unexpected token \n");
}

// t_data *creat_node(char **arguments)
// {
// 	t_data *new_node = malloc(sizeof(t_data));
// 	if (!new_node)
// 		return NULL;
// 	new_node->argumment = arguments;
// 	new_node->next = NULL;
// 	return (new_node);
// }

// void ft_add_node(t_data **head, char **arguments)
// {
// 	t_data *new_node;
// 	t_data *tmp = *head;

// 	new_node = creat_node(arguments);
// 	if (!new_node)
// 		return;
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return;
// 	}
// 	else
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new_node;
// 	}
// }

t_data *creat_node(char **arguments, char **redirection)
{
    t_data *new_node = malloc(sizeof(t_data));
    if (!new_node)
        return NULL;
    new_node->argumment = arguments;
    new_node->redirection = redirection;
    new_node->next = NULL;
    return new_node;
}
void ft_add_node(t_data **head, char **arguments, char **redirection)
{
    t_data *new_node;
    t_data *tmp = *head;

    new_node = creat_node(arguments, redirection);
    if (!new_node)
        return;
    if (*head == NULL)
    {
        *head = new_node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

size_t ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char *ft_strdup(const char *s1)
{
	int j;
	char *dup;

	dup = malloc((ft_strlen(s1) + 1) * sizeof(char));
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


static int count_words(const char *str, char delim)
{
    int count = 0;
    int in_word = 0;

    while (*str)
    {
        if (*str != delim && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*str == delim)
        {
            in_word = 0;
        }
        str++;
    }
    return count;
}

// Helper function to allocate and copy each word
static char *malloc_word(const char *str, char delim)
{
    int len = 0;
    const char *start = str;

    while (*str && *str != delim)
    {
        len++;
        str++;
    }

    char *word = malloc(sizeof(char) * (len + 1));  // Allocate memory for the word
    if (!word)
        return NULL;

    strncpy(word, start, len);  // Copy the word
    word[len] = '\0';  // Null-terminate the word
    return word;
}

// Main function to split the string by the delimiter
char **ft_splite(const char *str, char delim)
{
    int words = count_words(str, delim);
    char **split = malloc((words + 1) * sizeof(char *));  // Allocate memory for array of strings
    int i = 0;

    if (!split)
        return NULL;

    while (*str)
    {
        if (*str != delim)
        {
            split[i] = malloc_word(str, delim);  // Allocate and copy each word
            if (!split[i])
            {
                // Free allocated memory in case of failure
                while (i > 0)
                    free(split[--i]);
                free(split);
                return NULL;
            }
            i++;
            while (*str && *str != delim)
                str++;
        }
        else
            str++;
    }
    split[i] = NULL;
    return split;
}
