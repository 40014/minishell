#include "minishell.h"

// void	print_redir_list(t_redir_node *redir_list)
// {
// 	t_redir_node	*temp;
// 	int				i;

// 	temp = redir_list;
// 	i = 0;
// 	while (temp)
// 	{
// 		printf("Redirection %d: %s\n", i, temp->redirection);
// 		temp = temp->next;
// 		i++;
// 	}
// }

// void	print_use_list(t_data *head) // for testing
// {
// 	t_data *temp = head;
// 	int i = 0;
// 	while (temp)
// 	{
// 		print_redir_list(temp->redirections);
// 		printf("--------------------------\n");
// 		i = 0;
// 		while (temp->argumment[i] != NULL)
// 		{
// 			printf("Arg %d:%s\n", i, temp->argumment[i]);
// 			i++;
// 		}
// 		i = 0;
// 		temp = temp->next;
// 		if (temp)
// 		{
// 			printf("---- Next node ----\n");
// 		}
// 	}
// }

void	handlle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = 130;
}

void	return_to_std(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
}

void	ft_free_data_list_and_input(t_data **data, char *temp, char *input)
{
	ft_free_list(*data);
	free(temp);
	free(input);
}

int	checks_before_parse(t_hold_main *main_vars)
{
	signal(SIGINT, handlle_sigint);
	signal(SIGQUIT, SIG_IGN);
	main_vars->quots.x = 0;
	main_vars->data = NULL;
	main_vars->saved_stdout = dup(STDOUT_FILENO);
	main_vars->saved_stdin = dup(STDIN_FILENO);
	main_vars->input = readline((main_vars->temp = print_prompt(main_vars->env_var)));
	main_vars->hold_vars->input = main_vars->input;
	main_vars->hold_vars->temp = main_vars->temp;
	if (check_prompt(main_vars->input) == 1)
		return (1);
	if (check_prompt(main_vars->input) == 3)
	{
		exec_exit((char *[]){"exit", NULL}, &main_vars->env_var,
			&main_vars->data, &main_vars->hold_vars);
	}
	return (0);
}

int		g_exit_code;

int	main(int arc, char **arv, char **envp)
{
	t_hold_main	main_vars;

	if (arc > 1)
		return (1);
	main_vars.env_var = env_to_list(envp, arv[0]);
	main_vars.hold_vars = malloc(sizeof(t_hold));
	while (1)
	{
		if (checks_before_parse(&main_vars) == 1)
		{
			add_history(main_vars.input);
			if (((main_vars.i = parse_line(&main_vars.data, main_vars.input, main_vars.env_var, &main_vars.quots)) == 0 || main_vars.i == 2) && main_vars.quots.empty != 2)
			{
				if (main_vars.i == 2)
					free_before_exit(&main_vars.hold_vars, &main_vars.env_var,
						&main_vars.data, 1);
				exec_commandes(&main_vars.env_var, &main_vars.data,
					&main_vars.hold_vars, &main_vars.quots);
				return_to_std(main_vars.saved_stdin, main_vars.saved_stdout);
			}
		}
		ft_free_data_list_and_input(&main_vars.data, main_vars.temp, main_vars.input);
	}
}
