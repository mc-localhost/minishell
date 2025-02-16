/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:13 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/16 14:07:23 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	cd_error_x(char *str)
{
	ft_putstr_stderr("cd: string not in pwd: ");
	ft_putstr_stderr(str);
	ft_putstr_stderr("\n");
	return (-1);
}

int	error_notfound(char *str)
{
	ft_putstr_stderr(str);
	ft_putstr_stderr(": No such file or directory\n");
	return (-1);
}

int	cd(t_token *token, t_data *data)
{
	char	cwd[1024];

	if (token->args_count > 1)
		return (cd_error_x(token->args[0]));
	else if (token->args_count == 1 && chdir(token->args[0]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			change_env_var(&data->envs, "OLDPWD", find_env_var(&data->envs,
					"PWD"));
			change_env_var(&data->envs, "PWD", cwd);
		}
	}
	else if (token->args_count == 1)
		return (error_notfound(token->args[0]));
	return (1);
}
