/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printin_stderror.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:55:51 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/13 08:55:54 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putchar_fd(char c)
{
	write(2, &c, 1);
}

void	ft_putstr_fd(char const *str)
{
	while (*str)
		ft_putchar_fd(*str++);
}

void	ft_print_in_stderr(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*join;

	temp = ft_strjoin(s1, s2, 1, 1);
	join = ft_strjoin(temp, s3, 1, 1);
	free(temp);
	ft_putstr_fd(join);
	free(join);
}
