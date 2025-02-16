/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:07:12 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 13:29:55 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_string(t_token_type type)
{
	if (type == TOKEN_STRING || type == TOKEN_STRING_SINGLQ
		|| type == TOKEN_STRING_DOUBLEQ)
		return (1);
	return (0);
}

static void	builtin_token(t_token *token)
{
	int		i;
	int		num_builtins;
	char	*builtins[9] = {"cd", "echo", "pwd", "env", "export", "unset", "exit", "clear", "cls"}; //fix to pass norm

	num_builtins = 7;
	i = 0;
	while (i < num_builtins)
	{
		if (!ft_strcmp(token->value, builtins[i]))
		{
			token->type = TOKEN_BUILTIN;
			break ;
		}
		i++;
	}
}

static void	add_pipe_token(t_data *data)
{
	t_token	*pipe_token;

	pipe_token = init_token();
	pipe_token->type = TOKEN_PIPE;
	add_token(&data->final_tokens, pipe_token);
	data->num_pipes++;
}

static void	finalize_command(t_token *cmd, t_token **current_ptr, t_data *data)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *current_ptr;
	if (!current)
	{
		printf("i'm in finalize_command about to segfault\n");
		// if it's null there were no cmds before pipe... and it will SEGFAULT - FIX by adding syntax error!
	}
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
}

/*
Process tokens loops through data.tokens to collect all the commands
with respective arguments and redirections, so that the list
passed to execution looks like:
TOKEN_CMD or TOKEN_BUILTIN, TOKEN_PIPE, TOKEN_CMD or TOKEN_BUILTIN ...

When token gets processed its type get changed to PROCESSED for
easier args collection. Everything between pipes is considered to be
1 command with all redirections with filenames stored in linked lists
for that particular command, and the rest of the tokens - in cmd.args
array.
*/

void	process_tokens(t_data *data)
{
	t_token	*current;
	t_token	*current_cmd;

	current = data->tokens;
	current_cmd = NULL;
	while (current)
	{
		if (current_cmd == NULL)
		{
			current_cmd = init_token();
			current_cmd->type = TOKEN_CMD;
			current_cmd->redirections_in = NULL;
			current_cmd->redirections_out = NULL;
		}
		if (is_redirection(current->type))
			add_redirection_to_cmd(current_cmd, &current, data);
		else if (is_string(current->type))
		{
			if (current_cmd->value == NULL)
			{
				current_cmd->value = current->value;
				current->type = PROCESSED;
			}
			else
				current_cmd->args_count++;
		}
		else if (current->type == TOKEN_SPACE)
			current->type = PROCESSED;
		else if (current->type == TOKEN_PIPE)
		{
			finalize_command(current_cmd, &data->tokens, data);
			add_pipe_token(data);
			current->type = PROCESSED;
			current_cmd = NULL;
		}
		current = current->next;
	}
	if (current_cmd)
		finalize_command(current_cmd, &data->tokens, data);
}
