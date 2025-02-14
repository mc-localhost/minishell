/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:34 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/14 18:31:00 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// if (ft_strcmp(input, "env") == 0 || ft_strcmp(input, "export") == 0)
// 	print_env_list(data.envs);
// else if (ft_strcmp(input, "clear") == 0 || ft_strcmp(input, "cls") == 0)
// 	printf("\033[H\033[J"); // or system(input);
// else if (ft_strcmp(input, "pwd") == 0 )
// 	pwd();
// else
// 	printf("input: %s\n", input);

void	handle_builtin(t_token *token, t_data *data)
{
	if (!ft_strcmp(token->value, "cd"))
		cd(token);
	else if (!ft_strcmp(token->value, "echo"))
	{
		printf("executing echo\n");
		echo(token);
	}
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

// tests for builitns: https://github.com/jotavare/minishell?tab=readme-ov-file#export-env-and-unset