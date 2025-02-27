/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:11:27 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/27 06:03:38 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*get_path_with_home(char *cmd, char **envp)
{
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "HOME", 4) == 0)
		i++;
	if (!envp[i])
		return (0);
	tmp = ft_strtrim(cmd, "~");
	path = ft_strjoin(envp[i] + 5, tmp);
	free(tmp);
	return (path);
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
		return (get_path_with_home(cmd, envp));
	if (ft_strchr(cmd, '/'))
		return (0);
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i])
		return (0);
	return (get_path(cmd, envp[i]));
}

// Creates an array of strings from the linked list
char	**build_array(t_env_node *current, int len)
{
	char	**result;
	int		i;

	result = (char **)malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (current)
	{
		if (current->key && current->value)
		{
			result[i] = join_key_value(current->key, current->value);
			if (!result[i])
				return (free_arr(result), NULL);
			i++;
		}
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

// Main function to convert linked list to array
char	**list_to_arr(t_env_node *current)
{
	int	len;

	len = count_nodes(current);
	if (len == 0)
		return (NULL);
	return (build_array(current, len));
}

