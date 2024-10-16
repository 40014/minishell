/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:15:58 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:16:00 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arg_list(t_arg_node *head)
{
	t_arg_node	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->arg);
		free(temp);
	}
}

void	ft_free_redirection_list(t_redir_node *redir_list)
{
	t_redir_node	*temp;

	while (redir_list)
	{
		temp = redir_list;
		redir_list = redir_list->next;
		if (temp->redirection)
			free(temp->redirection);
		free(temp);
	}
}

void	ft_free_list(t_data *head)
{
	t_data	*temp;
	int		i;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->argumment)
		{
			i = 0;
			while (temp->argumment[i] != NULL)
			{
				free(temp->argumment[i]);
				i++;
			}
			free(temp->argumment);
		}
		if (temp->redirections)
			ft_free_redirection_list(temp->redirections);
		free(temp);
	}
}

void	ft_free_list2(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->var);
		free(temp->val);
		free(temp);
	}
}

void	free_before_exit(t_hold **hold_vars, t_env **envp, t_data **data, int i)
{
	free((*hold_vars)->input);
	free((*hold_vars)->temp);
	free(*hold_vars);
	ft_free_list(*data);
	ft_free_list2(*envp);
	if (i == 1)
	{
		rl_clear_history();
		exit(g_exit_code);
	}
}
