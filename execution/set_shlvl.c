#include "../minishell.h"

int ft_isdigit(char *number)
{
    int i;

    i = 0;
    while(number[i])
    {
        if (number[0] == '-')
            i++;
        if (!(number[i] >= '0' && number[i] <= '9'))
            return(1);
        i++;
    }
    return(0);
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

char *set_shlvl(char *var, char *shlvl)
{
    char *newshlvl;
    static int first_time;

    if (ft_strcmp3(var, "SHLVL") == 0 && first_time == 0)
    {
        first_time++;
        if (ft_isdigit(shlvl) == 1)
        {
            newshlvl = ft_calloc(2, 1);
            newshlvl[0] = '1';
            free(shlvl);
            return(newshlvl);
        }
        if (ft_atoi(shlvl) >= 999)
        {
            printf("warning: shell level %d too high, resetting to 1 \n", ft_atoi(shlvl) + 1);
            newshlvl = ft_calloc(2, 1);
            newshlvl[0] = '1';
            free(shlvl);
            return(newshlvl);
        }
        if (ft_atoi(shlvl) < 0)
        {
            newshlvl = ft_calloc(2, 1);
            newshlvl[0] = '0';
            free(shlvl);
            return(newshlvl);
        }
        else
            newshlvl = ft_getshlvl(ft_atoi(shlvl) + 1);
        free(shlvl);
        return(newshlvl);
    }
    return(shlvl);
}

