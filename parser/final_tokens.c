/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:12 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/23 12:53:03 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	add_pipe_token(t_data *data, t_token **cmd, t_token **current)
{
	t_token	*pipe_token;

	pipe_token = init_token();
	pipe_token->type = TOKEN_PIPE;
	add_token(&data->final_tokens, pipe_token);
	data->num_pipes++;
	(*current)->type = PROCESSED;
	*cmd = NULL;
}

static void	handle_string_token(t_token *current, t_token *cmd)
{
	if (!cmd->value)
	{
		cmd->value = current->value;
		current->type = PROCESSED;
	}
	else
		cmd->args_count++;
}

static int	finalize_command(t_token *cmd, t_token **current_ptr, t_data *data)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *current_ptr;
	if (!cmd->value)
		return (print_syntax_error(current));
	cmd->args = safe_malloc((cmd->args_count + 1) * sizeof(char *));
	cmd->args[cmd->args_count] = NULL;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type != PROCESSED)
		{
			cmd->args[i] = ft_strdup_safe(current->value);
			current->type = PROCESSED;
			i++;
		}
		current = current->next;
	}
	builtin_token(cmd);
	add_token(&data->final_tokens, cmd);
	*current_ptr = current;
	return (EXIT_SUCCESS);
}

/*
Process tokens loops through data.tokens to collect all the commands
with respective arguments and redirections, so that the list
passed to execution looks like:
TOKEN_CMD or TOKEN_BUILTIN, TOKEN_PIPE, TOKEN_CMD or TOKEN_BUILTIN ...

When token gets processed its type gets changed to PROCESSED for
easier args collection. Everything between pipes is considered to be
1 command with all redirections with filenames stored in linked lists
for that particular command, and the rest of the tokens - in cmd.args
array.
*/

static int	process_one(t_token **current_cmd, t_token **current, t_data *data)
{
	if (is_redirection((*current)->type))
	{
		if (add_redirection_to_cmd((*current_cmd), current,
				data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_string((*current)->type))
		handle_string_token((*current), (*current_cmd));
	else if ((*current)->type == TOKEN_SPACE)
		(*current)->type = PROCESSED;
	else if ((*current)->type == TOKEN_PIPE)
	{
		if (finalize_command((*current_cmd), &data->tokens,
				data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		add_pipe_token(data, current_cmd, current);
	}
	return (EXIT_SUCCESS);
}

int	process_tokens(t_data *data)
{
	t_token	*current;
	t_token	*current_cmd;

	current = data->tokens;
	current_cmd = NULL;
	while (current)
	{
		if (current_cmd == NULL)
			current_cmd = init_current_cmd();
		if (process_one(&current_cmd, &current, data) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		current = current->next;
	}
	if (current_cmd)
		return (finalize_command(current_cmd, &data->tokens, data));
	return (EXIT_SUCCESS);
}
