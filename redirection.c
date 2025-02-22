/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:28:54 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/22 19:36:42 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_redirection(t_redirection *head, int out)
{
	t_redirection	*current;
	char			*direction;
	int				fd;

	current = head;
	direction = NULL;
	while (current != NULL)
	{
		direction = current->file;
		if (current->next && out == 1)
		{
			fd = open_file(direction, 1);
			if (fd == -1)
			{
				g_global.last_exit_code = errno;
				return (NULL);
			}
			close(fd);
		}
		current = current->next;
	}
	return (direction);
}

void	set_redirect(t_token *token)
{
	char	*input;
	char	*output;
	int		fd;

	input = get_redirection(token->redirections_in, 0);
	output = get_redirection(token->redirections_out, 1);
	if (input)
	{
		fd = open_file(input, 0);
		if (fd == -1)
			error_exit("input error");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (output)
	{
		fd = open_file(output, 1);
		if (fd == -1)
			error_exit("output error");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}
