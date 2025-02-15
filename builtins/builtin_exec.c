/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:34 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 15:56:58 by vvasiuko         ###   ########.fr       */
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
		pwd(data);
	else if (!ft_strcmp(token->value, "unset"))
		return (unset(token, data));
	else if (!ft_strcmp(token->value, "exit"))
		return (999999);
	else if (!ft_strcmp(token->value, "clear") || !ft_strcmp(token->value, "cls"))
		printf("\033[H\033[J");
	return (0);
}
