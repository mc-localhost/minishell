/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:34 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/14 22:22:04 by aelaaser         ###   ########.fr       */
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

int	handle_builtin(t_token *token, t_data *data)
{
	if (!ft_strcmp(token->value, "cd"))
		return (cd(token, data));
	else if (!ft_strcmp(token->value, "echo"))
	{
		printf("executing echo\n");
		echo(token);
	}
	else if (!ft_strcmp(token->value, "env"))
		return (env(token, data));
	else if (!ft_strcmp(token->value, "export"))
		printf("executing export\n");
	else if (!ft_strcmp(token->value, "pwd"))
		pwd(data);
	else if (!ft_strcmp(token->value, "unset"))
		return (unset(token, data));
	else if (!ft_strcmp(token->value, "exit"))
		return (999999);
	else if (!ft_strcmp(token->value, "clear") || !ft_strcmp(token->value, "cls"))
		printf("\033[H\033[J");
	return (0);
}

// tests for builitns: https://github.com/jotavare/minishell?tab=readme-ov-file#export-env-and-unset