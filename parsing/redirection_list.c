/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: medo <medo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:50:37 by medo              #+#    #+#             */
/*   Updated: 2024/10/08 18:50:39 by medo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redir_node	*create_redir_node(char *redir)
{
	t_redir_node	*new_node;

	new_node = malloc(sizeof(t_redir_node));
	if (!new_node)
		return (NULL);
	if (redir != NULL)
		new_node->redirection = ft_strdup(redir);
	else
		new_node->redirection = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	append_redir_node(t_redir_node **redir_list, t_redir_node *new_node)
{
	t_redir_node	*current;

	if (!*redir_list)
		*redir_list = new_node;
	else
	{
		current = *redir_list;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
