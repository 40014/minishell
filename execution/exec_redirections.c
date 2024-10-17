/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrahm <hdrahm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:50:56 by hdrahm            #+#    #+#             */
/*   Updated: 2024/10/16 16:50:57 by hdrahm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_handle_output(char *file_name)
{
	int	output_fd;

	output_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (output_fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	dup2(output_fd, STDOUT_FILENO);
	close(output_fd);
	return (0);
}

int	ft_handle_input(char *file_name)
{
	int	input_fd;

	input_fd = open(file_name, O_RDONLY);
	if (input_fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	return (0);
}

int	ft_handle_append(char *file_name)
{
	int	append_fd;

	append_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (append_fd < 0)
	{
		perror(file_name);
		return (-1);
	}
	dup2(append_fd, STDOUT_FILENO);
	close(append_fd);
	return (0);
}

int	ft_find_del(char *line, char *del)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && del[i] && line[i] == del[i])
		i++;
	if (line[i] == '\n' && del[i] == '\0')
		return (1);
	return (0);
}
