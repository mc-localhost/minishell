/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:31:13 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/26 18:24:56 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static int	cd_error_x(char *str)
// {
// 	ft_putstr_stderr("cd: string not in pwd: ");
// 	ft_putstr_stderr(str);
// 	ft_putstr_stderr("\n");
// 	return (errno);
// }
// if (token->args_count > 1)
// 	return (cd_error_x(token->args[0]));

int	error_notfound(char *str)
{
	ft_putstr_stderr("minishell: cd: ");
	ft_putstr_stderr(str);
	ft_putstr_stderr(": No such file or directory\n");
	return (1);
}

// int	cd(t_token *token, t_data *data)
// {
// 	char	cwd[1024];
// 	char	*path;

// 	if (token->args_count == 0 || !ft_strcmp(token->args[0], "~"))
// 		path = find_env_var(&data->envs, "HOME");
// 	else
// 		path = token->args[0];
// 	if (chdir(path) == 0)
// 	{
// 		if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		{
// 			change_env_var(&data->envs, "OLDPWD", find_env_var(&data->envs,
// 					"PWD"));
// 			change_env_var(&data->envs, "PWD", cwd);
// 		}
// 	}
// 	else if (token->args_count == 1)
// 		return (error_notfound(path));
// 	return (0);
// }

int	change_dir(char *path, t_data *data)
{
	char	cwd[1024];

	if (chdir(path) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			change_env_var(&data->envs, "OLDPWD", find_env_var(&data->envs,
					"PWD"));
			change_env_var(&data->envs, "PWD", cwd);
		}
		return (0);
	}
	return (1);
}

int	cd(t_token *token, t_data *data)
{
	char	*path;
	char	*tmp;

	if (token->args_count == 0 || !ft_strcmp(token->args[0], "~"))
		path = find_env_var(&data->envs, "HOME");
	else if (token->args[0][0] == '~')
	{
		tmp = ft_strtrim(token->args[0], "~");
		if (!tmp)
			return (error_notfound(token->args[0]));
		path = ft_strjoin(find_env_var(&data->envs, "HOME"), tmp);
		free(tmp);
		if (change_dir(path, data) != 0)
			return (free(path), error_notfound(token->args[0]));
		else
			return (free(path), 0);
	}
	else if (!ft_strcmp(token->args[0], "-"))
	{
		path = find_env_var(&data->envs, "OLDPWD");
		if (!path)
			return (ft_putstr_stderr("minishell: cd: OLDPWD not set\n"), 1);
		printf("%s\n", path);
	}
	else
		path = token->args[0];
	if (change_dir(path, data) != 0)
		return (error_notfound(path));
	return (0);
}
