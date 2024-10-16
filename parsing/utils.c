/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:19:42 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:55:55 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_printf_error(int i)
{
	if (i == 2 || i == 3)
	{
		if (i == 2)
			ft_putstr_fd("unexpected EOF while looking for matching `\'' \n");
		else
			ft_putstr_fd("unexpected EOF while looking for matching `\"' \n");
	}
	else if (i == 1)
		ft_putstr_fd("minishell: syntax error near unexpected token \n");
}

t_data	*creat_node(char **arguments, t_redir_node *redirection)
{
	t_data	*new_node;

	new_node = malloc(sizeof(t_data));
	if (!new_node)
		return (NULL);
	new_node->argumment = arguments;
	new_node->redirections = redirection;
	new_node->next = NULL;
	return (new_node);
}

void	ft_add_node(t_data **head, char **arguments, t_redir_node *redirection)
{
	t_data	*new_node;
	t_data	*tmp;

	tmp = *head;
	new_node = creat_node(arguments, redirection);
	if (!new_node)
		return ;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
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
