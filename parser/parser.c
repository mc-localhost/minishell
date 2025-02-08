
#include "../includes/minishell.h"

void	expand_token_values(t_token *token, t_data *data)
{
	if (token->type != TOKEN_STRING)
		return ;
	token->value = expand(token->value, data);
}

void	builtin_token(t_token *token, t_data *data)
{
	int		i;
	int		num_builtins;
	char	*builtins[7] = {"cd", "echo", "pwd", "env", "export", "unset",
			"exit"};

	(void)data;
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

	printf("***		printing scanned	***\n\n");
	iterate_tokens(data, print_token);
	iterate_tokens(data, expand_token_values);
	printf("***		printing expanded	***\n\n");
	iterate_tokens(data, print_token);
	iterate_tokens(data, builtin_token);
	printf("***		printing builtin type change	***\n\n");
	iterate_tokens(data, print_token);
	return (EXIT_SUCCESS);
}