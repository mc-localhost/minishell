/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:11:27 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/26 19:09:52 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_path(char *cmd, char *envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	paths = ft_split(envp + 5, ':');
	if (!paths)
		return (0);
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

	if (!ft_strcmp(cmd, ".") || !ft_strcmp(cmd, ".."))
		return (0);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = 0;
	if (cmd[0] == '~')
	{
		cmd = ft_strtrim(cmd, "~");
		while (envp[i] && ft_strnstr(envp[i], "HOME", 4) == 0)
			i++;
		if (!envp[i])
			return (0);
		return (get_path(cmd, envp[i]));
	}
	if (ft_strchr(cmd, '/'))
		return (0);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (0);
	return (get_path(cmd, envp[i]));
}
