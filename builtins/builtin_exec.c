
#include "../includes/minishell.h"

		// if (ft_strcmp(input, "env") == 0 || ft_strcmp(input, "export") == 0)
		// 	print_env_list(data.envs);
		// else if (ft_strcmp(input, "clear") == 0 || ft_strcmp(input, "cls") == 0)
		// 	printf("\033[H\033[J"); // or system(input);
		// else if (ft_strcmp(input, "pwd") == 0 )
		// 	pwd();
		// else
		// 	printf("input: %s\n", input);

void handle_builtin(t_token *token, t_data *data)
{
    if (!ft_strcmp(token->value, "cd"))
        printf("executing cd\n");
    else if (!ft_strcmp(token->value, "echo"))
        echo(token);
    else if (!ft_strcmp(token->value, "env"))
        env(data);
    else if (!ft_strcmp(token->value, "export"))
		printf("executing export\n");
    else if (!ft_strcmp(token->value, "pwd"))
		pwd(data);
    else if (!ft_strcmp(token->value, "unset"))
		printf("executing unset\n");
    else if (!ft_strcmp(token->value, "exit"))
        printf("executing exit\n");
}
