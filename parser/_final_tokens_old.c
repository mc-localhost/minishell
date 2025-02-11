
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
            printf("changed token type to BUILTIN for %s\n", token->value);
			break ;
		}
		i++;
	}
}

static t_token *add_cmd_token(t_token *current, t_data *data)
{
	t_token *current_cmd;
    printf("started adding cmd token\n");
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

static int is_string(t_token_type type)
{
    if (type == TOKEN_STRING || type ==TOKEN_STRING_SINGLQ || type == TOKEN_STRING_DOUBLEQ)
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

static void add_redir_to_end(t_redirection **head, t_redirection *new_redir)
{
    t_redirection   *current;

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

static void add_redirection_to_cmd(t_token *cmd, t_token **current_ptr)
{
    t_token *current;
    t_redirection *redir;

    current = *current_ptr;
    redir = init_redir(current);
    printf("initialised REDIRECTION type %i for TOKEN_CMD %s\n", redir->type, cmd->value);
    current = current->next;
    while (current && current->type == TOKEN_SPACE)
    {
        printf("skipped space (%s) before filename\n", current->value);
        current = current->next;
    }
    if (current && is_string(current->type))
    {
        // a bit more complex for heredoc
        redir->file = ft_strdup(current->value);
        printf("found file for REDIRECTION %s\n", redir->file);
    }
    else
    {
        //syntax errors should go into syntax.c
        printf("minishell: syntax error near unexpected token `%s'\n", current->value); //get back to it to handle new_line and stuff
        exit(EXIT_FAILURE);
    }
    if (redir->type == TOKEN_REDIRECT_IN || redir->type == TOKEN_HEREDOC)
        add_redir_to_end(&cmd->redirections_in, redir);
    else
        add_redir_to_end(&cmd->redirections_out, redir);
    printf("added redirection to list\n");
    *current_ptr = current;
}

static void finalize_command(t_token *cmd, t_token *current)
{
    int args_index;

    args_index = 0;
    printf("finalizing cmd token %s\n", cmd->value);
    cmd->args = safe_malloc((cmd->args_count + 1)* sizeof(char *));
    cmd->args[cmd->args_count] = NULL;
    while (current && current->type != TOKEN_PIPE)
    {
        if (is_string(current->type) || current->type == TOKEN_SPACE)
        {
            cmd->args[args_index] = ft_strdup(current->value);
            printf("added arg %i: \"%s\"\n", args_index, cmd->args[args_index]);
            args_index++;
        }
        else if (is_redirection(current->type))
        {
            current = current->next; // skip redirection token
            while (current && current->type == TOKEN_SPACE)
            {
                printf("supposedly skipped space:%s\n", current->value);
                current = current->next;
            }
            if (current && is_string(current->type))
            {
                printf("supposedly skipped filename:%s\n", current->value);
                current = current->next; // skip filename
            }
            continue ;
        }
        current = current->next;
    }
}

void process_tokens(t_data *data)
{
    t_token *current = data->tokens;
    t_token *current_cmd = NULL;
    t_token *dummy_cmd = NULL; // To hold redirections before the command
    t_token *after_cmd;

    while (current)
    {
        if (is_string(current->type) && current_cmd == NULL)
        {
            // Start a new command
            current_cmd = add_cmd_token(current, data);
            after_cmd = current->next;
            // If a dummy command exists, transfer its redirections to the actual command
            if (dummy_cmd != NULL)
            {
                current_cmd->redirections_in = dummy_cmd->redirections_in;
                current_cmd->redirections_out = dummy_cmd->redirections_out;
                free(dummy_cmd); // Free the dummy command
                dummy_cmd = NULL;
            }
        }
        else if (current_cmd)
        {
            if (current->type == TOKEN_PIPE)
            {
                // Finalize current command and add pipe to final_tokens
                finalize_command(current_cmd, after_cmd);
                current_cmd = NULL;
                add_pipe_token(data);
                printf("finalized cmd before pipe\n");
            }
            else if (is_redirection(current->type))
            {
                // Handle redirection and its filename
                add_redirection_to_cmd(current_cmd, &current);
            }
            else if (is_string(current->type) || current->type == TOKEN_SPACE)
            {
                // Count the argument (we'll populate cmd->args later)
                current_cmd->args_count++;
                printf("updated args count: %i\n", current_cmd->args_count);
            }
        }
        else if (is_redirection(current->type))
        {
            // Handle redirections before the command token
            if (dummy_cmd == NULL)
            {
                // Create a dummy command to hold the redirections
                dummy_cmd = init_token();
                dummy_cmd->type = TOKEN_CMD;
                dummy_cmd->value = strdup(""); // Empty command name
                add_token(&data->final_tokens, dummy_cmd);
            }
            add_redirection_to_cmd(dummy_cmd, &current);
        }
        current = current->next;
        if (current->value)
            printf("moved to token \"%s\"\n", current->value);
    }

    // Finalize the last command if it exists
    if (current_cmd)
    {
        finalize_command(current_cmd, after_cmd);
    }
    // else if (dummy_cmd != NULL)
    // {
    //     // If there's a dummy command but no actual command, finalize it
    //     finalize_command(dummy_cmd, after_cmd);
    // }
}
