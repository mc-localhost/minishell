/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:19:56 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/23 14:37:18 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error_exit(const char *msg)
{
	if (ft_strlen(msg) == 0)
		msg = strerror(errno);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	ft_putstr_stderr("\n");
	exit(errno);
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

void	free_exit_error(char **cmd, char *msg)
{
	free_arr(cmd);
	error_exit(msg);
}
