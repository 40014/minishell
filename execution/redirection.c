/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:56:10 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/13 08:56:12 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_which_redirection(char *redirection, char *file_name)
{
	if (redirection[0] == '>' && redirection[1] == '>')
	{
		if ((ft_handle_append(file_name)) == -1)
			return (-1);
	}
	else if (redirection[0] == '>')
	{
		if ((ft_handle_output(file_name)) == -1)
			return (-1);
	}
	else if (redirection[0] == '<')
	{
		if ((ft_handle_input(file_name)) == -1)
			return (-1);
	}
	return (0);
}

int	check_handle_redirections(t_data *data)
{
	t_redir_node	*temp;

	temp = data->redirections;
	while (temp)
	{
		if (temp->next->redirection == NULL)
		{
			ft_putstr_fd("ambiguous redirect\n");
			g_exit_code = 1;
			return (1);
		}
		if (ft_which_redirection(temp->redirection, temp->next->redirection)
			== -1)
		{
			g_exit_code = 1;
			return (1);
		}
		temp = temp->next->next;
	}
	return (0);
}
