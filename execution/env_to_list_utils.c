/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:29 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:50:31 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*grep_env_value(char *envp, int i)
{
	int		j;
	char	*value;

	j = 0;
	while (envp[j])
		j++;
	value = malloc(j - i + 1);
	j = 0;
	while (envp[i])
	{
		value[j] = envp[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

void	add_missing_vars(t_env **env, int t1, int t2, int t3)
{
	char	path[PATH_MAX];
	char	*hold;

	getcwd(path, PATH_MAX);
	if (t1 == 0)
	{
		hold = ft_strjoin("PWD=", path, 1, 1);
		ft_create_nodes(env, hold);
		free(hold);
	}
	if (t2 == 0)
		ft_create_nodes(env, "SHLVL=0");
	if (t3 == 0)
		ft_create_nodes(env, "OLDPWD");
}

void	add_update_last_commande(t_env **env, char *var_val)
{
	char	*temp;
	t_env	*search;
	int		t;

	search = *env;
	t = 0;
	while (search)
	{
		if (ft_strcmp3(search->var, "_") == 0)
			t = 1;
		search = search->next;
	}
	if (t == 0)
	{
		temp = ft_strjoin("_=", var_val, 1, 1);
		ft_create_nodes(env, temp);
		free(temp);
	}
	else
		ft_update_val(env, "_=", var_val);
}

char	*ft_getenv(t_env *envp, char *var)
{
	int	i;

	while (envp != NULL)
	{
		i = 0;
		while (envp->var[i] && var[i])
		{
			if (envp->var[i] != var[i])
				break ;
			i++;
		}
		if (var[i] == '\0' && envp->var[i] == '=')
			return (envp->val);
		envp = envp->next;
	}
	return (NULL);
}
