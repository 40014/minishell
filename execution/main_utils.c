/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:51:14 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:51:15 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	main_vars->quots.fdout = main_vars->saved_stdout;
	main_vars->quots.fdin = main_vars->saved_stdin;
	main_vars->temp = print_prompt(main_vars->env_var);
	main_vars->input = readline(main_vars->temp);
	main_vars->hold_vars->input = main_vars->input;
	main_vars->hold_vars->temp = main_vars->temp;
	if (check_prompt(main_vars->input) == 1)
		return (1);
	if (check_prompt(main_vars->input) == 3)
	{
		close(main_vars->saved_stdout);
		close(main_vars->saved_stdin);
		exec_exit((char *[]){"exit", NULL}, &main_vars->env_var,
			&main_vars->data, &main_vars->hold_vars);
	}
	return (0);
}
