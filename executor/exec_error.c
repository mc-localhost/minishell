/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:44:43 by aelaaser          #+#    #+#             */
/*   Updated: 2025/03/07 12:59:13 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exec_error_ext(char *cmd, t_data *data, int type, char *err)
{
	if (is_directory(cmd) && ft_strchr(cmd, '/'))
	{
		err = ft_strjoin_safe(err, ft_strjoin_safe(cmd, ": is a directory"));
		free(cmd);
	}
	else
	{
		err = ft_strjoin_safe(err, ft_strjoin_safe(cmd, ": "));
		if (!is_directory(cmd) && !ft_strchr(cmd, '/'))
			type = 127;
		free(cmd);
		if (type == 127)
			err = ft_strjoin_safe(err, "command not found");
		else if (type == 126)
			err = ft_strjoin_safe(err, "Permission denied");
		else
			err = ft_strjoin_safe(err, strerror(errno));
	}
	error_exit(err, type, data);
}

void	print_exec_error(char *cmd, t_data *data, int type)
{
	char	*err;

	err = ft_strdup_safe("minishell: ");
	if (!ft_strcmp(cmd, "."))
	{
		err = ft_strjoin_safe(err,
				"filename argument required\n.: usage: . filename [arguments]");
		type = 127;
		error_exit(err, type, data);
	}
	else
		print_exec_error_ext(cmd, data, type, err);
}

int	env_cmd_error(t_token *token)
{
	ft_putstr_stderr("env: ");
	ft_putstr_stderr(token->args[0]);
	ft_putstr_stderr(": No such file or directory\n");
	return (1);
}
