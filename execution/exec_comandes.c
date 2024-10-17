/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_comandes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:38 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:50:40 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	exec_simple_commande(t_env **envp, t_data **data, t_hold **hold_vars,
		t_quots *quots)
{
	if (check_handle_redirections(*data) == 1)
		return (g_exit_code);
	if (ft_strcmp((*data)->argumment[0], "echo") == 0)
		g_exit_code = exec_echo((*data)->argumment);
	else if (ft_strcmp((*data)->argumment[0], "pwd") == 0)
		g_exit_code = exec_pwd((*data)->argumment);
	else if (ft_strcmp((*data)->argumment[0], "cd") == 0)
		g_exit_code = exec_cd((*data)->argumment, envp);
	else if (ft_strcmp((*data)->argumment[0], "export") == 0)
		g_exit_code = exec_export((*data)->argumment, envp);
	else if (ft_strcmp((*data)->argumment[0], "env") == 0)
		g_exit_code = exec_env((*data)->argumment, *envp);
	else if (ft_strcmp((*data)->argumment[0], "unset") == 0)
		g_exit_code = exec_unset((*data)->argumment, envp);
	else if (ft_strcmp((*data)->argumment[0], "exit") == 0)
	{
		close(quots->fdout);
		close(quots->fdin);
		g_exit_code = exec_exit((*data)->argumment, envp, data, hold_vars);
	}
	else
		g_exit_code = exec_non_builtin((*data)->argumment, envp);
	return (g_exit_code);
}

void	exec_commandes(t_env **envp, t_data **data, t_hold **hold_vars,
		t_quots *quots)
{
	int	i;

	if ((*data) != NULL)
	{
		if (ft_exec_heredocs(data, *envp, quots) == -1)
			return ;
	}
	if ((*data)->next == NULL && (*data) != NULL)
	{
		i = 0;
		while ((*data)->argumment[i])
			i++;
		if ((*data)->argumment[0])
			add_update_last_commande(envp, (*data)->argumment[i - 1]);
		exec_simple_commande(envp, data, hold_vars, quots);
		if ((*data)->argumment[0])
			add_update_last_commande(envp, (*data)->argumment[i - 1]);
	}
	if ((*data)->next != NULL)
		exec_with_pipes(envp, data, hold_vars, quots);
	delete_heredoc_files();
}
