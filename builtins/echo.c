
#include "../includes/minishell.h"

void echo(t_token *token)
{
	int	i;

	if (!ft_strcmp(token->args[0], "-n"))
	{
		i = 1;
		if (!ft_strcmp(token->args[i], " "))
			i++;
		while (i < token->args_count)
		{
			printf("%s", token->args[i]); // spaces will be also saved as arguments
			i++;
		}
	}
	else
	{
		i = 0;
		while (i < token->args_count - 1)
		{
			printf("%s", token->args[i]); // spaces will be also saved as arguments
			i++;
		}
		printf("%s\n", token->args[i]);
	}
}
