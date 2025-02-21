/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:34 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/21 20:10:26 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_builtin(t_token *token, t_data *data)
{
	if (!ft_strcmp(token->value, "cd"))
		return (cd(token, data));
	else if (!ft_strcmp(token->value, "echo"))
		return (echo(token));
	else if (!ft_strcmp(token->value, "env"))
		return (env(token, data));
	else if (!ft_strcmp(token->value, "export"))
		return (export(token, data));
	else if (!ft_strcmp(token->value, "pwd"))
		return (pwd(data));
	else if (!ft_strcmp(token->value, "unset"))
		return (unset(token, data));
	else if (!ft_strcmp(token->value, "exit"))
		custom_exit(token);
	else if (!ft_strcmp(token->value, "clear"))
		printf("\033[H\033[J");
	return (0);
}
