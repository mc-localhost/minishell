/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:19:56 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/26 19:25:36 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_exit(const char *msg, int r)
{
	if (ft_strlen(msg) == 0)
		msg = strerror(errno);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	ft_putstr_stderr("\n");
	if (r == 0)
		r = errno;
	exit(r);
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
