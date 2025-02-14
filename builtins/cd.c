/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:13 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/14 18:56:03 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd(t_token *token, t_data *data)
{
	char*	newpwd;
	
	if (token->args_count > 1)
	{
		printf("cd: string not in pwd: %s\n", token->args[0]);
		return (0);
	}
	else if (token->args_count == 1 && chdir(token->args[0]) == 0)
	{
		newpwd = ft_strjoin(find_env_var(&data->envs, "PWD"), "/");
		if (newpwd)
		{
			newpwd = ft_strjoin(newpwd, token->args[0]);
			if (newpwd) {
				change_env_var(&data->envs, "OLDPWD", find_env_var(&data->envs, "PWD"));
				change_env_var(&data->envs, "PWD", newpwd);
			}
		}
		free(newpwd);
	}
	else if (token->args_count == 1)
	{
	 	printf("cd: no such file or directory: %s\n", token->args[0]);
		return (0);
	}
	return (1);
}
