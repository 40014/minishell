/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:34 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:50:35 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_one_node(char *envp)
{
	t_env	*node;
	char	*temp;
	int		i;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	i = 0;
	while (envp[i] != '=' && envp[i] != '\0')
		i++;
	temp = malloc(i + 2);
	i = 0;
	while (envp[i] != '=' && envp[i] != '\0')
	{
		temp[i] = envp[i];
		i++;
	}
	temp[i] = '=';
	temp[i + 1] = '\0';
	node->var = ft_strdup(temp);
	node->val = grep_env_value(envp, i + 1);
	node->val = set_shlvl(temp, node->val, NULL);
	node->next = NULL;
	free(temp);
	return (node);
}

t_env	*ft_one_node2(char *envp)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->var = ft_strdup(envp);
	node->val = NULL;
	node->next = NULL;
	return (node);
}

void	ft_create_nodes(t_env **head, char *envp)
{
	t_env	*temp;
	t_env	*new_node;
	int		i;

	temp = *head;
	i = 0;
	while (envp[i] != '=' && envp[i] != '\0')
		i++;
	if (envp[i] == '=')
		new_node = ft_one_node(envp);
	else
		new_node = ft_one_node2(envp);
	if (temp == NULL)
		*head = new_node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	check_missing_vars(t_env **env, char *first_arg, int t1, int t2)
{
	t_env	*temp;
	int		t3;
	int		t4;

	temp = *env;
	t4 = 0;
	t3 = 0;
	while (temp)
	{
		if (ft_strcmp3(temp->var, "PWD") == 0)
			t1 = 1;
		else if (ft_strcmp3(temp->var, "SHLVL") == 0)
			t2 = 1;
		else if (ft_strcmp3(temp->var, "OLDPWD") == 0)
			t3 = 1;
		else if (ft_strcmp3(temp->var, "_") == 0)
			t4 = 1;
		temp = temp->next;
	}
	add_missing_vars(env, t1, t2, t3);
	if (t4 == 0)
		add_update_last_commande(env, first_arg);
}

t_env	*env_to_list(char **envp, char *first_arg)
{
	t_env	*env_var;
	int		i;

	i = 0;
	env_var = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strcmp3(envp[i], "PWD") != 0)
			ft_create_nodes(&env_var, envp[i]);
		i++;
	}
	check_missing_vars(&env_var, first_arg, 0, 0);
	return (env_var);
}
