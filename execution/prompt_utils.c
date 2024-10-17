/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:51:23 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:51:25 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2, int flag, int size)
{
	char	*join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + size);
	if (!join)
		return (NULL);
	while (s1[j])
		join[i++] = s1[j++];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	if (flag == 1)
	{
		join[i] = '\0';
		return (join);
	}
	join[i] = '$';
	join[i + 1] = '>';
	join[i + 2] = ' ';
	join[i + 3] = '\0';
	return (join);
}

char	*put_right_color(char *prompt)
{
	char	*temp;
	char	*hold;

	if (prompt == NULL)
		return (NULL);
	temp = ft_strjoin(prompt, "\x1b[0m", 1, 1);
	free(prompt);
	if (g_exit_code == 0)
		hold = ft_strjoin("\x1b[1;32m\x1b[1mminishell:\x1b[0m", temp, 1, 1);
	else
		hold = ft_strjoin("\x1b[1;31m\x1b[1mminishell:\x1b[0m", temp, 1, 1);
	free(temp);
	return (hold);
}

char	*check_if_pwd_error(t_env *envp)
{
	char	path[PATH_MAX];
	char	*prompt;

	prompt = NULL;
	if (getcwd(path, PATH_MAX) == NULL)
	{
		if (ft_getenv(envp, "PWD") == NULL)
			prompt = ft_strjoin("\x1b[1;37m\x1b[1m", ".", 0, 4);
		else
			prompt = ft_strjoin("\x1b[1;37m\x1b[1m",
					ft_getenv(envp, "PWD"), 0, 4);
		return (put_right_color(prompt));
	}
	return (NULL);
}

char	*print_prompt(t_env *envp)
{
	char	*home;
	char	path[PATH_MAX];
	char	*prompt;
	int		i;

	prompt = check_if_pwd_error(envp);
	if (prompt != NULL)
		return (prompt);
	getcwd(path, PATH_MAX);
	home = ft_getenv(envp, "HOME");
	if (ft_strcmp(path, home) == 0)
		prompt = ft_strjoin("\x1b[1;37m\x1b[1m", "~", 0, 4);
	else
	{
		i = 0;
		while (home && home[i] && home[i] == path[i])
			i++;
		if (home && home[i] == '\0')
			prompt = ft_strjoin("\x1b[1;37m\x1b[1m~", &path[i], 0, 4);
		else
			prompt = ft_strjoin("\x1b[1;37m\x1b[1m", path, 0, 4);
	}
	return (put_right_color(prompt));
}
