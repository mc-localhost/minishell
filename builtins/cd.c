/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:13 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/14 21:53:48 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int cd_error_x(char *str)
{
	write(STDERR_FILENO, "cd: string not in pwd: ", 23);
	write(STDERR_FILENO, str, strlen(str));
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

int error_notfound(char *str)
{
	write(STDERR_FILENO, str, strlen(str));
	write(STDERR_FILENO, ": No such file or directory\n", 28);
	return (-1);
}

int	cd(t_token *token, t_data *data)
{
	char	cwd[1024];
	
	if (token->args_count > 1)
		return (cd_error_x(token->args[0]));
	else if (token->args_count == 1 && chdir(token->args[0]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	change_env_var(&data->envs, "OLDPWD", find_env_var(&data->envs, "PWD"));
			change_env_var(&data->envs, "PWD", cwd);
    	}
	}
	else if (token->args_count == 1)
		return(error_notfound(token->args[0]));
	return (1);
}
