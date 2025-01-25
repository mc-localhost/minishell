/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:54:55 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/12/20 16:14:35 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	**path_find_and_split(char **envp)
{
	int		i;
	char	**split_paths;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	split_paths = ft_split(&envp[i][5], ':');
	if (!split_paths)
		return (NULL);
	return (split_paths);
}

char	*find_exec(char *cmd, t_pipe_data *data)
{
	char	*cmd_path;
	char	*temp_path;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		temp_path = ft_strjoin(data->paths[i], "/");
		if (!temp_path)
			perror_exit("Memory allocation failed", 1, data);
		cmd_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!cmd_path)
			perror_exit("Memory allocation failed", 1, data);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	execute_command(char *cmd, char **envp, t_pipe_data *data)
{
	char	**cmd_n_flags;
	char	*path;

	cmd_n_flags = ft_split(cmd, ' ');
	if (!cmd_n_flags)
		perror_exit("Split failed", 1, data);
	path = find_exec(cmd_n_flags[0], data);
	if (!path)
	{
		ft_free_split(cmd_n_flags);
		perror_exit("Command not found", 127, data);
	}
	if (execve(path, cmd_n_flags, envp) == -1)
	{
		free(path);
		ft_free_split(cmd_n_flags);
		perror_exit("Execute error", 1, data);
	}
}
