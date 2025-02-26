/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:35:49 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/26 18:19:15 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redirection(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

static t_redirection	*init_redir(t_token **current)
{
	t_redirection	*redir;

	redir = safe_malloc(sizeof(t_redirection));
	redir->type = (*current)->type;
	redir->file = NULL;
	redir->next = NULL;
	(*current)->type = PROCESSED;
	*current = (*current)->next;
	return (redir);
}

static void	add_redir_to_end(t_redirection **head, t_redirection *new_redir)
{
	t_redirection	*current;

	if (!*head)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

static void	skip_spaces(t_token **current)
{
	while (*current && (*current)->type == TOKEN_SPACE)
	{
		(*current)->type = PROCESSED;
		*current = (*current)->next;
	}
}

int	add_redirection_to_cmd(t_token *cmd, t_token **current_ptr, t_data *data)
{
	t_redirection	*redir;

	redir = init_redir(current_ptr);
	skip_spaces(current_ptr);
	if (*current_ptr && is_string((*current_ptr)->type))
	{
		if (redir->type == TOKEN_HEREDOC)
		{
			if (handle_heredoc(*current_ptr, (*current_ptr)->value,
					data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			redir->file = ft_strdup_safe(HEREDOC_FILENAME);
		}
		else
			redir->file = ft_strdup_safe((*current_ptr)->value);
		(*current_ptr)->type = PROCESSED;
	}
	else
		return (print_syntax_error(*current_ptr));
	if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
		add_redir_to_end(&cmd->redirections_in, redir);
	else
		add_redir_to_end(&cmd->redirections_out, redir);
	return (EXIT_SUCCESS);
}
