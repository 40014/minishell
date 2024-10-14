/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_non_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:54:51 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/13 08:54:54 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_if_path(char *commande)
{
	int	check;

	check = 0;
	check = if_contain_directory(commande);
	if (check == 1)
		check_if_directory(commande);
}

int	test_paths(char **commande, char **paths, char **envp)
{
	int			j;
	char		*join;
	char		*temp;

	check_if_path(commande[0]);
	if (execve(commande[0], commande, envp) == -1)
	{
		j = 0;
		while (paths[j])
		{
			temp = ft_strjoin(paths[j], "/", 1, 1);
			join = ft_strjoin(temp, commande[0], 1, 1);
			free(temp);
			execve(join, commande, envp);
			free(join);
			j++;
		}
	}
	return (1);
}

char	**convert_envp_to_arr(t_env *envp)
{
	int		count;
	char	**envp_arr;
	int		j;

	count = count_nodes(envp);
	envp_arr = malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (envp)
	{
		if (envp->val != NULL)
		{
			envp_arr[j] = ft_strjoin(envp->var, envp->val, 1, 1);
			j++;
		}
		envp = envp->next;
	}
	envp_arr[j] = NULL;
	return (envp_arr);
}

void	exec_non_builtin_in_child(t_env *envp, char **commande)
{
	char	**paths;
	char	**envp_arr;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	paths = ft_split(ft_getenv(envp, "PATH"), ':');
	envp_arr = convert_envp_to_arr(envp);
	if (test_paths(commande, paths, envp_arr) == 1)
	{
		if (commande[0][0] == '\0')
			ft_print_in_stderr("commande '", commande[0],
				"' not found\n");
		else
			ft_print_in_stderr(commande[0], ": commande not found\n", "");
	}
	ft_free_arr(paths);
	ft_free_arr(envp_arr);
	exit(127);
}

int	exec_non_builtin(char **commande, t_env **envp)
{
	int	pid;
	int	status;

	if (commande[0] == NULL)
		return (0);
	pid = fork();
	if (pid == 0)
		exec_non_builtin_in_child(*envp, commande);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handlle_sigint);
	if (WIFEXITED(status) != 0)
		g_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
	{
		g_exit_code = WTERMSIG(status) + 128;
		printf("\n");
	}
	return (g_exit_code);
}
