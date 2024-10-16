/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:14:26 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:14:29 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handle_dollar_digit(char **result, int *i, char *str)
{
	if (str[*i + 1] == '0')
	{
		*result = ft_strjoinee(*result, "minishell");
		*i += 2;
	}
	else
	{
		*i += 2;
	}
}

void	ft_handle_dollar_variable(char **result, char *str, int *i,
		t_env *env_var)
{
	char				tmp[BUFSIZ];
	long unsigned int	j;
	char				*env_result;

	j = 0;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != ' ' && str[*i] != '$'
		&& ft_is_valid(str[*i]) == 1 && j < sizeof(tmp) - 1)
	{
		tmp[j] = str[*i];
		j++;
		(*i)++;
	}
	tmp[j] = '\0';
	env_result = ft_getenv(env_var, tmp);
	if (env_result != NULL)
		*result = ft_strjoinee(*result, env_result);
}

void	append_char_to_resulte(char **result, char current_char)
{
	char	character[2];

	character[0] = current_char;
	character[1] = '\0';
	*result = ft_strjoinee(*result, character);
}

char	*ft_expand_herdoc(char *str, t_env *env_var, t_quots *quots)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && ft_is_digits(str[i + 1]) == 1
			&& quots->herdoc_expan != 1)
			ft_handle_dollar_digit(&result, &i, str);
		else if (str[i] != '\0' && str[i] == '$' && str[i + 1] != '$'
			&& quots->herdoc_expan != 1)
			ft_handle_dollar_variable(&result, str, &i, env_var);
		else
		{
			append_char_to_resulte(&result, str[i]);
			i++;
		}
	}
	if (result == NULL)
		return (ft_strdup(str));
	else
		return (result);
}
