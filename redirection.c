/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:28:54 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/23 15:54:33 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	file_error(char *file)
{
	ft_putstr_stderr("minishell: ");
	ft_putstr_stderr(file);
	ft_putstr_stderr(": ");
	error_exit("", 1);
}

static t_redirection	*get_redirection(t_redirection *head, int out)
{
	t_redirection	*current;
	t_redirection	*direction;
	int				fd;

	current = head;
	direction = NULL;
	while (current != NULL)
	{
		direction = current;
		if (current->next)
		{
			fd = open_file(current->type, current->file, out);
			if (fd == -1)
			{
				g_global.last_exit_code = errno;
				file_error(current->file);
			}
			close(fd);
		}
		current = current->next;
	}
	return (direction);
}

void	set_redirect(t_token *token)
{
	t_redirection	*input;
	t_redirection	*output;
	int				fd;

	input = get_redirection(token->redirections_in, 0);
	output = get_redirection(token->redirections_out, 1);
	if (input)
	{
		fd = open_file(input->type, input->file, 0);
		if (fd == -1)
			file_error(input->file);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (output)
	{
		fd = open_file(output->type, output->file, 1);
		if (fd == -1)
			file_error(output->file);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
