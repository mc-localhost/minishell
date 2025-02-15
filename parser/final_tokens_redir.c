/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:35:49 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:28:48 by vvasiuko         ###   ########.fr       */
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

t_redirection	*init_redir(t_token *current)
{
	t_redirection	*redir;

	redir = safe_malloc(sizeof(t_redirection));
	redir->type = current->type;
	redir->file = NULL;
	redir->next = NULL;
	return (redir);
}

void	add_redir_to_end(t_redirection **head, t_redirection *new_redir)
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

void	add_redirection_to_cmd(t_token *cmd, t_token **current_ptr,
		t_data *data)
{
	t_token			*current;
	t_redirection	*redir;

	current = *current_ptr;
	redir = init_redir(current);
	current->type = PROCESSED;
	current = current->next;
	while (current && current->type == TOKEN_SPACE)
	{
		current->type = PROCESSED;
		current = current->next;
	}
	if (current && is_string(current->type))
	{
		if (redir->type == TOKEN_HEREDOC)
			redir->file = handle_heredoc(current, data);
		else
			redir->file = ft_strdup_safe(current->value);
		current->type = PROCESSED;
	}
	else
	{
		// syntax errors should go into syntax.c
		printf("minishell: syntax error near unexpected token `%s'\n", current->value);
		exit(EXIT_FAILURE);
	}
	if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
		add_redir_to_end(&cmd->redirections_in, redir);
	else
		add_redir_to_end(&cmd->redirections_out, redir);
	*current_ptr = current;
}
