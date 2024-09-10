#include "../minishell.h"

t_data *creat_node(char **arguments)
{
	t_data *new_node = malloc(sizeof(t_data));
	if (!new_node)
		return NULL;
	new_node->argumment = arguments;
	new_node->next = NULL;
	return (new_node);
}

void ft_add_node(t_data **head, char **arguments)
{
	t_data *new_node;
	t_data *tmp = *head;

	new_node = creat_node(arguments);
	if (!new_node)
		return;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
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

char *ft_strjoine(char const *s1, char const *s2)
{
	size_t i;
	size_t j;
	char *newstr;

	if (s1 == NULL)
		return (s2);
	i = 0;
	j = 0;
	newstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (newstr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		newstr[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		newstr[i + j] = s2[j];
		j++;
	}
	newstr[i + j] = '\0';
	return (newstr);
}
