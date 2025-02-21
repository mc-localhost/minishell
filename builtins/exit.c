/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:56 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/21 23:36:15 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
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

void	custom_exit(t_token *token)
{
	g_global.last_exit_code = 0;
	if (token->args_count != 0)
	{
		ft_putstr_stderr("exit\n");
		if (token->args_count >= 1)
		{
			if (!ft_isnum(token->args[0]))
			{
				ft_putstr_stderr("bash: exit: ");
				ft_putstr_stderr(token->args[0]);
				ft_putstr_stderr(" : numeric argument required");
				g_global.last_exit_code = 255;
			}
			else if (token->args_count == 1)
				g_global.last_exit_code = ft_atoi(token->args[0]);
			else if (token->args_count > 1)
				return (ft_putstr_stderr("bash: exit: too many arguments\n"));
		}
	}
	else
		printf("exit\n");
	free_all();
	unlink(HEREDOC_FILENAME);
	exit(g_global.last_exit_code);
}

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
*/