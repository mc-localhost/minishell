
#include "../includes/minishell.h"

char	*ft_strtoupper(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\0')
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
	
}

int env_cmd_error(t_token *token)
{
	write(STDERR_FILENO, "env: ", 5);
	write(STDERR_FILENO, token->args[0], strlen(token->args[0]));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	return (-1);
}

int	env(t_token *token, t_data *data)
{
	if (token->args_count == 1 && !ft_strchr(token->args[0], '='))
	{
		if (find_env_var(&data->envs, ft_strtoupper(token->args[0])) != NULL)
			printf("%s\n", find_env_var(&data->envs, ft_strtoupper(token->args[0])));
		else
			return (env_cmd_error(token));
	}
	else if (token->args_count > 1)
		return (env_cmd_error(token));
	else
		print_env_list(data->envs);
	if (token->args_count == 1 && ft_strchr(token->args[0], '='))
		printf("%s\n", token->args[0]);
	return (1);
}
