#include "../../minishell.h"

int	go_home(t_env *envp)
{
	char	*home;

	home = ft_getenv(envp, "HOME");
	if (home == NULL)
	{
		ft_putstr_fd("cd : HOME not set\n");
		return (1);
	}
	if (chdir(home) != 0 && home[0] != '\0')
	{
		ft_print_in_stderr("cd: ", home, ": No such file or directory\n");
		return (1);
	}
	return (0);
}

int	go_from_home(t_env *envp, char *path)
{
	char	*home;
	char	*join;

	home = ft_getenv(envp, "HOME");
	if (path[0] == '~' && path[1] == '\0')
	{
		if (go_home(envp) == 0)
			return (0);
		return (1);
	}
	if (path[0] == '~')
	{
		if (path[1] == '/' && home != NULL)
			join = ft_strjoin(home, &path[1], 1, 1);
		else
			join = ft_strdup(path);
		if (chdir(join) != 0)
		{
			perror(join);
			free(join);
			return (1);
		}
		free(join);
	}
	return (0);
}

int	go_to_specific_path(t_env *envp, char *path)
{
	char	*oldpwd;

	if (path[0] == '-' && path[1] == '\0')
	{
		oldpwd = ft_getenv(envp, "OLDPWD");
		if (oldpwd == NULL)
		{
			ft_putstr_fd("cd : OLDPWD not set\n");
			return (1);
		}
		if (chdir(oldpwd) != 0)
		{
			perror(oldpwd);
			return (1);
		}
		printf("%s\n", oldpwd);
		return (0);
	}
	if (chdir(path) != 0)
	{
		perror(path);
		return (1);
	}
	return (0);
}

int	exec_cd(char **commande, t_env **envp, int check, int wd_err)
{
	char	cur_path[PATH_MAX];
	char	old_path[PATH_MAX];

	if (getcwd(old_path, PATH_MAX) == NULL)
		wd_err = 1;
	if (commande[1] != NULL && commande[2] != NULL)
	{
		ft_putstr_fd("too many arguments\n");
		check = 1;
	}
	else if (commande[1] == NULL || (commande[1][0] == '-'
		&& commande[1][1] == '-' && commande[1][2] == '\0'))
		check = go_home(*envp);
	else if (commande[1][0] == '~')
		check = go_from_home(*envp, commande[1]);
	else
		check = go_to_specific_path(*envp, commande[1]);
	if (check == 0)
	{
		if (getcwd(cur_path, PATH_MAX) != NULL)
			ft_update_val(envp, "PWD=", cur_path);
		if (commande[1] != NULL && wd_err == 0)
			ft_update_val(envp, "OLDPWD=", old_path);
	}
	return (check);
}
