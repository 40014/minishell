#include "../minishell.h"

int ft_atoi3(char *str)
{
	int i;
	int symbol;
	int outcome;

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
	return (outcome * symbol);
}

static long ft_atoi4(char *str, t_env **envp, t_data **data, t_hold **hold_vars)
{
	int				i;
	int				s;
	unsigned long	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		s = s * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - 48);
		if ((r > LONG_MAX && s == 1) || (s == -1 && r > (unsigned long)LONG_MIN))
		{
			ft_print_in_stderr("exit: ", str, ": numeric argument required\n");
			free_before_exit(hold_vars, envp, data, 0);
			exit(2);
		}
		i++;
	}
	return (r * s);
}

int ft_isalnum(char *str, t_env **envp, t_data **data, t_hold **hold_vars)
{
	int i;
	int count;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (1);
	count = 0;
	while (str[i])
	{
		while (str[i] >= '0' && str[i++] <= '9')
			count++;
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] != '\0')
			return (1);
	}
	ft_atoi4(str, envp, data, hold_vars);
	return (0);
}

int exec_exit(char **commande, t_env **envp, t_data **data, t_hold **hold_vars)
{
	int i;

	if (commande[1] != NULL && ft_isalnum(commande[1], envp, data,
										  hold_vars) == 1)
	{
		ft_print_in_stderr("exit: ", commande[1],
						   ": numeric argument required\n");
		free_before_exit(hold_vars, envp, data, 0);
		exit(2);
	}
	else if (commande[1] != NULL && commande[2] != NULL)
	{
		ft_putstr_fd("exit: too many arguments\n");
		return (1);
	}
	else if (commande[1] != NULL)
	{
		i = ft_atoi3(commande[1]);
		free_before_exit(hold_vars, envp, data, 0);
		exit(i);
	}
	else
		free_before_exit(hold_vars, envp, data, 0);
	exit(exit_code);
}
