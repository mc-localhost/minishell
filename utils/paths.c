/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:54:55 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/17 15:06:08 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	path_find_and_split(char **envp, t_pipe_data *data)
{
	int		i;
	char	**split_paths;

	i = 0;
	while (envp[i] && ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	if (!envp[i])
		perror_free_struct(data, "PATH not found", 1);
	split_paths = ft_split(&envp[i][5], ':');
	if (!split_paths)
		perror_free_struct(data, "Split failed", 1);
	data->paths = split_paths;
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
			perror_free_struct(data, "Memory allocation failed", 1);
		cmd_path = ft_strjoin(temp_path, cmd);
		free(temp_path);
		if (!cmd_path)
			perror_free_struct(data, "Memory allocation failed", 1);
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
		perror_free_struct(data, "Split failed", 1);
	path = find_exec(cmd_n_flags[0], data);
	if (!path)
	{
		ft_free_split(cmd_n_flags);
		perror_free_struct(data, "Command not found", 127);
	}
	if (execve(path, cmd_n_flags, envp) == -1)
	{
		free(path);
		ft_free_split(cmd_n_flags);
		perror_free_struct(data, "Execute error", 1);
	}
}
