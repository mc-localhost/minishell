
#include "../includes/minishell.h"

void	env(t_data *data)
{
	print_env_list(data->envs);
}
