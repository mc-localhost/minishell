/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:05:34 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 04:04:36 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ist_echo(char *str)
{
	if (ft_tolower(str[0]) != 'e' || ft_tolower(str[1]) != 'c')
		return (0);
	if (ft_tolower(str[2]) != 'h' || ft_tolower(str[3]) != 'o')
		return (0);
	return (1);
}

int	ist_env(char *str)
{
	if (ft_tolower(str[0]) != 'e' || ft_tolower(str[1]) != 'n')
		return (0);
	if (ft_tolower(str[2]) != 'v')
		return (0);
	return (1);
}

int	handle_builtin(t_token *token, t_data *data)
{
	if (!ft_strcmp(token->value, "cd"))
		return (cd(token, data));
	else if (!ft_strcmp(token->value, "echo")
		|| (ft_strlen(token->value) == 4 && ist_echo(token->value)))
		return (echo(token));
	else if (!ft_strcmp(token->value, "env")
		|| (ft_strlen(token->value) == 3 && ist_env(token->value)))
		return (env(token, data));
	else if (!ft_strcmp(token->value, "export"))
		return (export(token, data));
	else if (!ft_strcmp(token->value, "pwd"))
		return (pwd(data));
	else if (!ft_strcmp(token->value, "unset"))
		return (unset(token, data));
	else if (!ft_strcmp(token->value, "exit"))
		return (custom_exit(token, data));
	else if (!ft_strcmp(token->value, "clear"))
		printf("\033[H\033[J");
	return (0);
}
