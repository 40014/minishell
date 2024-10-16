/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:18:39 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:18:41 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split_string_on_error(char **result, int idx)
{
	int	j;

	j = 0;
	while (j < idx)
	{
		free(result[j]);
		j++;
	}
	free(result);
}

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	handle_allocation_error(char **result, int idx)
{
	free_split_string_on_error(result, idx);
	return (-1);
}

int	allocate_and_store_word(char **result, int idx, const char *start, int len)
{
	result[idx] = malloc((len + 1) * sizeof(char));
	if (result[idx] == NULL)
		return (-1);
	ft_strncpy(result[idx], start, len);
	result[idx][len] = '\0';
	return (0);
}
