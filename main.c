/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:52:12 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 17:37:02 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code;

int	main(int arc, char **arv, char **envp)
{
	t_hold_main	main_vars;

	if (arc > 1)
		return (1);
	g_exit_code = 0;
	main_vars.env_var = env_to_list(envp, arv[0]);
	main_vars.hold_vars = malloc(sizeof(t_hold));
	while (1)
	{
		if (checks_before_parse(&main_vars) == 1)
		{
			add_history(main_vars.input);
			if (check_parsing(&main_vars))
			{
				if (main_vars.i == 2)
					free_before_exit(&main_vars.hold_vars, &main_vars.env_var,
						&main_vars.data, 1);
				exec_commandes(&main_vars.env_var, &main_vars.data,
					&main_vars.hold_vars, &main_vars.quots);
				return_to_std(main_vars.saved_stdin, main_vars.saved_stdout);
			}
		}
		ft_free_data_list_and_input(&main_vars.data, main_vars.temp,
			main_vars.input);
	}
}
