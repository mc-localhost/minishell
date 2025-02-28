/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:19:56 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/27 00:36:26 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	open_file(t_token_type type, char *filename, int output)
{
	int	fd;

	if (output == 0)
		return (open(filename, O_RDONLY));
	else if (output == 1)
	{
		if (type == TOKEN_APPEND)
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd > 0)
			return (fd);
	}
	return (-1);
}

void	error_exit(const char *msg, int r, t_data *data)
{
	if (ft_strlen(msg) == 0)
		msg = strerror(errno);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	ft_putstr_stderr("\n");
	if (r == 0)
		r = errno;
	g_global.last_exit_code = r;
	clean_exit(data);
}

int	ft_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
}

void	envp_to_list(t_data *data, char **envp, int i)
{
	t_env_node	*env_list;
	char		*equal_sign;
	size_t		key_len;
	char		*key;
	char		*value;

	env_list = NULL;
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		key_len = equal_sign - envp[i];
		key = malloc((key_len + 1) * sizeof(char));
		ft_strlcpy(key, envp[i], key_len + 1);
		value = ft_strdup(equal_sign + 1);
		add_env_var(&env_list, create_env_var(key, value));
		i++;
	}
	data->envs = env_list;
}
