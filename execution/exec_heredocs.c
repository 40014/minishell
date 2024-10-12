#include "../minishell.h"

void	exec_heredoc_in_child(t_env *envp, t_quots *quots, int fd, char *del)
{
	char	*line;
	char	*temp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_find_del(line, del) == 1)
		{
			free(line);
			break ;
		}
		temp = ft_expand_herdoc(line, envp, quots);
		write(fd, temp, ft_strlen(temp));
		free(temp);
		free(line);
	}
	exit(0);
}

int	get_child_exit_code(int pid, char *file_name, t_redir_node *red)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handlle_sigint);
	signal(SIGQUIT, SIG_DFL);
	if (WIFSIGNALED(status) != 0)
	{
		g_exit_code = WTERMSIG(status) + 128;
		free(file_name);
		printf("\n");
		return (-1);
	}
	free(red->redirection);
	red->redirection = ft_strdup("<");
	free(red->next->redirection);
	red->next->redirection = file_name;
	return (0);
}

int	ft_handle_heredoc(t_redir_node *red, t_env *envp, t_quots *quots)
{
	int		fd;
	char	*file_name;
	char	*id;
	int		pid;

	id = ft_itoa(quots->id);
	file_name = ft_strjoin("/tmp/heredoc_tmp", id, 1, 1);
	free(id);
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror(file_name);
		return (-1);
	}
	pid = fork();
	if (pid == 0)
		exec_heredoc_in_child(envp, quots, fd, red->next->redirection);
	if (get_child_exit_code(pid, file_name, red) == -1)
		return (-1);
	return (0);
}

void	delete_heredoc_files(void)
{
	char	*file_name;
	char	*id;
	int		i;

	i = 0;
	while (i < 16)
	{
		id = ft_itoa(i);
		file_name = ft_strjoin("/tmp/heredoc_tmp", id, 1, 1);
		if (access(file_name, F_OK) == 0)
			unlink(file_name);
		else
		{
			free(file_name);
			free(id);
			break ;
		}
		free(file_name);
		free(id);
		i++;
	}
}

int	ft_exec_heredocs(t_data **data_add, t_env *envp, t_quots *quots)
{
	t_data			*temp;
	t_redir_node	*red;

	temp = *data_add;
	quots->id = 0;
	while (temp)
	{
		red = temp->redirections;
		while (red)
		{
			if (red->redirection[0] == '<' && red->redirection[1] == '<'
				&& red->redirection[2] == '\0')
			{
				if (ft_handle_heredoc(red, envp, quots) == -1)
					return (-1);
				quots->id++;
			}
			red = red->next->next;
		}
		temp = temp->next;
	}
	return (0);
}
