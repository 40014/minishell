#include "../../minishell.h"

void	ft_print_env(t_env *envp)
{
	while (envp)
	{
		if (envp->val)
			printf("%s", envp->var);
		if (envp->val)
			printf("%s\n", envp->val);
		envp = envp->next;
	}
}

int	exec_env(char **commande, t_env *envp)
{
	if (commande[1] == NULL)
		ft_print_env(envp);
	else
	{
		ft_print_in_stderr("env: '", commande[1],
			"': No such file or directory\n");
		return (127);
	}
	return (0);
}
