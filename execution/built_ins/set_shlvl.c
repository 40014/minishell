/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:23 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:50:26 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_atoi2(char *str)
{
	int	i;
	int	symbol;
	int	outcome;

	i = 0;
	symbol = 1;
	outcome = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			symbol = symbol * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		outcome = outcome * 10 + (str[i] - 48);
		i++;
	}
	if (((outcome * symbol) >= INT_MAX) || ((outcome * symbol) <= INT_MIN))
		return (-1);
	return (outcome * symbol);
}

int	ft_isdigit(char *number)
{
	int	i;

	i = 0;
	while (number[i] == ' ' || (number[i] >= 9 && number[i] <= 13))
		i++;
	if (number[i] == '-' || number[i] == '+')
		i++;
	if (number[i] == '\0')
		return (1);
	while (number[i])
	{
		while (number[i] >= '0' && number[i] <= '9')
			i++;
		while (number[i] == ' ' || (number[i] >= 9 && number[i] <= 13))
			i++;
		if (number[i] != '\0')
			return (1);
	}
	return (0);
}

int	ft_nlenght(int n)
{
	unsigned int	count;
	long			x;

	x = n;
	count = 0;
	if (x == 0)
		return (1);
	while (x != 0)
	{
		if (x < 0)
		{
			x = -x;
			count++;
		}
		x = x / 10;
		count++;
	}
	return (count);
}

char	*ft_getshlvl(int n)
{
	char			*str;
	unsigned int	l;
	long			x;

	l = ft_nlenght(n);
	x = n;
	str = (char *)malloc(l + 1);
	if (str == NULL)
		return (NULL);
	if (x == 0)
		str[0] = '0';
	str[l] = '\0';
	while (x != 0)
	{
		if (x < 0)
		{
			x = -x;
			str[0] = '-';
		}
		str[l - 1] = (x % 10) + 48;
		x = x / 10;
		l--;
	}
	return (str);
}

char	*set_shlvl(char *var, char *shlvl, char *newshlvl)
{
	static int	first_time;

	if (ft_strcmp3(var, "SHLVL") == 0 && first_time == 0)
	{
		first_time++;
		newshlvl = ft_calloc(2, 1);
		if (ft_isdigit(shlvl) == 1)
			newshlvl[0] = '1';
		else if (ft_atoi2(shlvl) >= 999)
		{
			printf("warning: shell level (%d) too high, resetting to 1 \n",
				ft_atoi2(shlvl) + 1);
			newshlvl[0] = '1';
		}
		else if (ft_atoi2(shlvl) < 0)
			newshlvl[0] = '0';
		else
		{
			free(newshlvl);
			newshlvl = ft_getshlvl(ft_atoi2(shlvl) + 1);
		}
		free(shlvl);
		return (newshlvl);
	}
	return (shlvl);
}
