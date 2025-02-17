/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:01:56 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:48:23 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	custom_exit(t_token *token) //not finished
{
	g_global.last_exit_code = 0;
	if (token->args_count != 0)
	{
		if (token->args_count == 1)
			g_global.last_exit_code = ft_atoi(token->args[0]);
	}
	free_all();
	unlink(HEREDOC_FILENAME);
	printf("exit\n");
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