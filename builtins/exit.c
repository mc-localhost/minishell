/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:56 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 12:13:46 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
bash-3.2$ exit hello
exit
bash: exit: hello: numeric argument required

exits with exit code 255

bash-3.2$ exit 123 123
exit
bash: exit: too many arguments
bash-3.2$

doesn't exit, exit code = 1

bash-3.2$ exit 9223372036854775807
exit
vvasiuko@2-C-9 ~ % echo $?
255

bash-3.2$ exit -5
exit
vvasiuko@2-C-9 ~ % echo $?
251

*/

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (-1);
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i] && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	custom_exit(t_token *token, t_data *data)
{
	if (!data->is_active)
		ft_putstr_stderr("exit\n");
	if (token->args_count >= 1)
	{
		if (ft_isnum(token->args[0]) <= 0)
		{
			ft_putstr_stderr("minishell: exit: ");
			ft_putstr_stderr(token->args[0]);
			ft_putstr_stderr(": numeric argument required\n");
			g_global.last_exit_code = 255;
		}
		else if (token->args_count > 1)
		{
			g_global.last_exit_code = 1;
			return (
				ft_putstr_stderr("minishell: exit: too many arguments\n"),
				1);
		}
		else if (token->args_count == 1)
			g_global.last_exit_code = ft_atoi_exit(token->args[0]);
	}
	return (clean_exit(data));
}

int	clean_exit(t_data *data)
{
	tokens_cleanup(data);
	if (!data->is_active)
		unlink(HEREDOC_FILENAME);
	free_all();
	free_env(data);
	rl_clear_history();
	exit(g_global.last_exit_code);
}
