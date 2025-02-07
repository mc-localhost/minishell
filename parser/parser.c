
#include "../includes/minishell.h"

void	expand_token_value(t_token *token)
{
	if (token->type != TOKEN_STRING)
		return ;
	
}

void	builtin_token(t_token *token)
{
	int		i;
	int		num_builtins;
	char	*builtins[7] = {"cd", "echo", "pwd", "env", "export", "unset", "exit"};

	if (token->type != TOKEN_CMD)
		return ;
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

int	parse(t_data *data)
{
	scan(data);
	// find commands and set their arguments

	// deal with pipes and redirections

	// set builtin commands as TOKEN_BUILTIN
	iterate_tokens(data->tokens, print_token);
	iterate_tokens(data->tokens, builtin_token);
	iterate_tokens(data->tokens, print_token);

	// expand strings
	// printf("%s\n", expand(data->input_copy, data));
	return (EXIT_SUCCESS);
}