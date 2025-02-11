
#include "../includes/minishell.h"

static void	builtin_token(t_token *token)
{
	int		i;
	int		num_builtins;
	char	*builtins[7] = {"cd", "echo", "pwd", "env", "export", "unset",
			"exit"};

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
	pipe_token->value = "|"; // unnecessary
	add_token(&data->final_tokens, pipe_token);
	data->num_pipes++;
}

static int	is_redirection(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

static int	is_string(t_token_type type)
{
	if (type == TOKEN_STRING || type == TOKEN_STRING_SINGLQ
		|| type == TOKEN_STRING_DOUBLEQ)
		return (1);
	return (0);
}

static t_redirection	*init_redir(t_token *current)
{
	t_redirection	*redir;

	redir = safe_malloc(sizeof(t_redirection));
	redir->type = current->type;
	redir->file = NULL;
	redir->next = NULL;
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

static void	add_redirection_to_cmd(t_token *cmd, t_token **current_ptr, t_data *data)
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
        	redir->file = ft_strdup(current->value);
		current->type = PROCESSED;
	}
	else
	{
		// syntax errors should go into syntax.c
		printf("minishell: syntax error near unexpected token `%s'\n",
			current->value); // get back to it to handle new_line and stuff
		exit(EXIT_FAILURE);
	}
	if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
		add_redir_to_end(&cmd->redirections_in, redir);
	else
		add_redir_to_end(&cmd->redirections_out, redir);
	*current_ptr = current;
}

static void	finalize_command(t_token *cmd, t_token **current_ptr, t_data *data)
{
	int		i;
	t_token	*current;

	i = 0;
	current = *current_ptr;
	// if it's null there were no cmds before pipe... and it will SEGFAULT
	cmd->args = safe_malloc((cmd->args_count + 1) * sizeof(char *));
	cmd->args[cmd->args_count] = NULL;
	while (current && current->type != TOKEN_PIPE)
	{
		if (current->type != PROCESSED)
		{
			cmd->args[i] = ft_strdup(current->value);
			current->type = PROCESSED;
			i++;
		}
		current = current->next;
	}
	builtin_token(cmd);
	add_token(&data->final_tokens, cmd);
	*current_ptr = current;
}

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
			current_cmd->args_count++;
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
