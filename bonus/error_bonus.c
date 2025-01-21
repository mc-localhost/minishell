/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:27:31 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/12/20 16:13:22 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	perror_exit(char *msg, int i, t_pipe_data *data)
{
	if (data->fd_in > 2)
		close(data->fd_in);
	if (data->fd_out > 2)
		close(data->fd_out);
	if (data->paths)
		ft_free_split(data->paths);
	perror(msg);
	exit(i);
}
