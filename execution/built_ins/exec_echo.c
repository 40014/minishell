/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:40 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:49:41 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	check_valid_options(char **commande)
{
	int	j;
	int	i;

	j = 1;
	while (commande[j] != NULL)
	{
		i = 0;
		if (commande[j][i] == '-')
			i++;
		else
			return (j);
		if (commande[j][i] == '\0')
			return (j);
		while (commande[j][i])
		{
			if (commande[j][i] != 'n')
				return (j);
			while (commande[j][i] == 'n')
				i++;
		}
		j++;
	}
	return (j);
}

int	exec_echo(char **commande)
{
	int	j;
	int	n;

	j = check_valid_options(commande);
	n = j;
	while (commande[j] != NULL)
	{
		ft_putstr(commande[j]);
		if (commande[j + 1] != NULL)
			ft_putstr(" ");
		j++;
	}
	if (n == 1)
		ft_putstr("\n");
	return (0);
}
