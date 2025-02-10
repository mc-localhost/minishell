
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
            printf("changed token type to BULTIN for %s\n", token->value);
			break ;
		}
		i++;
	}
}

static t_token *add_cmd_token(t_token *current, t_data *data)
{
	t_token *current_cmd;

	current_cmd = init_token();
    current_cmd->type = TOKEN_CMD;
    current_cmd->value = ft_strdup(current->value); //needs safe malloc
    builtin_token(current_cmd);
    add_token(&data->final_tokens, current_cmd);
    printf("added TOKEN_CMD for %s\n", current->value);
	return (current_cmd);
}

static void add_pipe_token(t_data *data)
{
	t_token *pipe_token;

	pipe_token = init_token();
    pipe_token->type = TOKEN_PIPE;
    add_token(&data->final_tokens, pipe_token);
    printf("added TOKEN_PIPE\n");
    data->num_pipes++;
}

static int is_redirection(t_token_type type)
{
    if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT ||
        type == TOKEN_APPEND || type == TOKEN_HEREDOC)
        return (1);
    return (0);
}

static t_redirection *init_redir(t_token *current)
{
    t_redirection   *redir;

    redir = safe_malloc(sizeof(t_redirection));
    redir->type = current->type;
    redir->file = NULL;
    redir->next = NULL;
    return (redir);
}

static void add_redirection_to_cmd(t_token *cmd, t_token **current_ptr)
{
    t_token *current;
    t_redirection *redir;

    current = *current_ptr;
    redir = init_redir(current);
    printf("initialised REDIRECTION type %i for TOKEN_CMD %s\n", redir->type, cmd->value);
    if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
    {
        //adding in the wrong direction - FIX!
        redir->next = cmd->redirections_in;
        cmd->redirections_in = redir;
    }
    else
    {
        redir->next = cmd->redirections_out;
        cmd->redirections_out = redir;
    }
    printf("been at %i\n", current->type);
    current = current->next;
    printf("landed at %i\n", current->type);
    // skip spaces after the redirection
    while (current && current->type == TOKEN_SPACE)
    {
        printf("skipped space (%s) before filename\n", current->value);
        current = current->next;
    }
    if (current && (current->type == TOKEN_STRING || current->type == TOKEN_STRING_SINGLQ))
    {
        // a bit more complex for heredoc
        redir->file = ft_strdup(current->value);
        printf("found file for REDIRECTION %s\n", redir->file);
        // current = current->next;
    }
    else
    {
        //syntax errors should go into syntax.c
        printf("minishell: syntax error near unexpected token `%s'\n", current->value); //get back to it to handle new_line and stuff
        exit(EXIT_FAILURE);
    }
    *current_ptr = current;
}

static void finalize_command(t_token *cmd, t_token *current)
{
    int args_index;

    printf("finalizing cmd token %s\n", cmd->value);
    cmd->args = safe_malloc((cmd->args_count + 1)* sizeof(char *));
    cmd->args[cmd->args_count] = NULL;
    args_index = 0;
    while (current && current->type != TOKEN_PIPE)
    {
        if (current->type == TOKEN_STRING || current->type == TOKEN_STRING_SINGLQ || current->type == TOKEN_SPACE)
        {
            cmd->args[args_index] = ft_strdup(current->value);
            printf("added arg %i: \"%s\"\n", args_index, cmd->args[args_index]);
            args_index++;
        }
        else if (is_redirection(current->type))
        {
            current = current->next; // skip redirection token
            while (current != NULL && current->type == TOKEN_SPACE)
            {
                printf("supposedly skipped space:%s\n", current->value);
                current = current->next;
            }
            if (current && (current->type == TOKEN_STRING || current->type == TOKEN_STRING_SINGLQ))
            {
                printf("supposedly skipped filename:%s\n", current->value);
                current = current->next; // skip filename
            }
            continue ;
        }
        current = current->next;
    }
}

void	process_tokens(t_data *data)
{
    t_token *current;
    t_token *current_cmd;
    t_token *after_cmd;

	current = data->tokens;
	current_cmd = NULL;
    while (current)
    {
        if ((current->type == TOKEN_STRING || current->type ==TOKEN_STRING_SINGLQ) && current_cmd == NULL)
        {
			current_cmd = add_cmd_token(current, data);
            after_cmd = current->next;
        }
        else if (current_cmd != NULL)
        {
            if (current->type == TOKEN_PIPE)
			{
                finalize_command(current_cmd, after_cmd);
				add_pipe_token(data);
                current_cmd = NULL;
			}
            else if (is_redirection(current->type))
                add_redirection_to_cmd(current_cmd, &current);
            else if (current->type == TOKEN_STRING || current->type == TOKEN_STRING_SINGLQ || current->type == TOKEN_SPACE)
                current_cmd->args_count++;
        }
        current = current->next;
    }
    if (current_cmd != NULL)
        finalize_command(current_cmd, after_cmd);
}
