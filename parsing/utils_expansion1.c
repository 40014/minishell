/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:19:24 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/16 18:26:34 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_env_variable(const char *str, int *skip)
{
	char	var_name[BUFSIZ];
	int		var_index;

	var_index = 0;
	if (str[*skip] == '$')
	{
		var_name[var_index++] = str[*skip];
		(*skip)++;
	}
	while (str[*skip] && ft_is_valid(str[*skip]) == 1 && var_index < BUFSIZ - 1)
	{
		var_name[var_index++] = str[*skip];
		(*skip)++;
	}
	var_name[var_index] = '\0';
	return (ft_strdup(var_name));
}

char	*ft_strjoinee(char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	len1 = 0;
	len2 = 0;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	if (s1 != NULL)
		ft_strcpy(result, s1);
	if (s2 != NULL)
		ft_strcpy(result + len1, s2);
	free(s1);
	return (result);
}
