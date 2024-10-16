/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_to_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:15:08 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:15:10 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_arg_node	*create_arg_node(char *arg)
{
	t_arg_node	*new_node;

	new_node = malloc(sizeof(t_arg_node));
	if (!new_node)
		return (NULL);
	new_node->arg = ft_strdup(arg);
	new_node->next = NULL;
	return (new_node);
}

void	append_arg_node(t_arg_node **head, t_arg_node *new_node)
{
	t_arg_node	*temp;

	if (!*head)
	{
		*head = new_node;
	}
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	count_arg_nodes(t_arg_node *head)
{
	int	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

char	**convert_list_to_array(t_arg_node *head)
{
	int			count;
	int			i;
	char		**args;
	t_arg_node	*temp;

	i = 0;
	count = count_arg_nodes(head);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	temp = head;
	while (i < count)
	{
		args[i] = ft_strdup(temp->arg);
		temp = temp->next;
		i++;
	}
	args[count] = NULL;
	return (args);
}
