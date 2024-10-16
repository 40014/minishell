/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momazouz <momazouz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 21:19:14 by momazouz          #+#    #+#             */
/*   Updated: 2024/10/15 21:19:17 by momazouz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_digits(char c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

int	ft_is_valid(char c)
{
	if (c > 64 && c < 91)
		return (1);
	else if (c > 96 && c < 123)
		return (1);
	else if (c > 47 && c < 58)
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	if (src == NULL || dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	lenght(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nbr;

	nbr = n;
	len = lenght(n);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (nbr == 0)
		result[0] = '0';
	result[len] = '\0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr != 0)
	{
		result[--len] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (result);
}
