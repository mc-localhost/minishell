/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:27:31 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/17 14:53:12 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	perror_exit(char *msg, int i)
{
	perror(msg);
	exit(i);
}

void	perror_free_struct(t_pipe_data *data, char *msg, int i)
{
	if (data->paths)
		ft_free_split(data->paths);
	if (data->fd_in > 2)
		close(data->fd_in);
	if (data->fd_out > 2)
		close(data->fd_out);
	if (data->pipefd[0] > 2)
		close(data->pipefd[0]);
	if (data->pipefd[1] > 2)
		close(data->pipefd[1]);
	perror_exit(msg, i);
}
