/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:11:27 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/23 16:40:39 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*quotation_fix(char *str)
{
	int	size;
	int	x;

	size = ft_strlen(str);
	if (size > 2)
	{
		if (str[0] == 39 && str[1] == '"')
		{
			str = ft_strtrim(str, "\"'");
			return (ft_strjoin("\"", ft_strjoin(str, "\"")));
		}
		if (str[0] == '"' && str[1] == 39)
			return (ft_strtrim(str, "\""));
		x = 0;
		while (str[x])
		{
			if (str[x] == 39 || str[x] == '"')
			{
				str[x] = ' ';
			}
			x++;
		}
	}
	return (str);
}

char	**optmize_cmd(char **cmd, char *argv)
{
	int	size;
	int	x;

	size = ft_arr_size(cmd);
	x = 2;
	if (size > 2 && (ft_strchr(argv, 39) || ft_strchr(argv, '"')))
	{
		while (size > 2)
		{
			cmd[1] = ft_strjoin(cmd[1], " ");
			cmd[1] = ft_strjoin(cmd[1], cmd[x]);
			free(cmd[x]);
			cmd[x] = NULL;
			x++;
			size--;
		}
		cmd[1] = quotation_fix(cmd[1]);
	}
	return (cmd);
}

char	*get_path(char *cmd, char *envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = ft_split(envp + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (free_arr(paths), path);
		free(path);
		i++;
	}
	free_arr(paths);
	return (0);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (0);
	return (get_path(cmd, envp[i]));
}
