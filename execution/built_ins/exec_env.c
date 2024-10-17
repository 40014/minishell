/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:46 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:49:47 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_print_env(t_env *envp)
{
	char	*var;
	char	*val;

	while (envp)
	{
		if (envp->var[0] == '_' && envp->var[1] == '=')
		{
			var = envp->var;
			val = envp->val;
		}
		else
		{
			if (envp->val)
				printf("%s", envp->var);
			if (envp->val)
				printf("%s\n", envp->val);
		}
		envp = envp->next;
	}
	printf("%s", var);
	printf("%s\n", val);
}

int	exec_env(char **commande, t_env *envp)
{
	if (commande[1] == NULL)
		ft_print_env(envp);
	else
	{
		ft_print_in_stderr("env: '", commande[1],
			"': No such file or directory\n");
		return (127);
	}
	return (0);
}
