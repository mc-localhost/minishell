/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:50:02 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/17 15:43:23 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	setup_pipe_fds(t_pipe_data *data)
{
	close(data->pipefd[0]);
	if (dup2(data->fd_in, STDIN_FILENO) == -1)
		perror_free_struct(data, "Input redirect failed", 1);
	if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
		perror_free_struct(data, "Pipe redirect failed", 1);
	close(data->fd_in);
	close(data->pipefd[1]);
}

void	setup_pipe_fds2(t_pipe_data *data)
{
	close(data->pipefd[1]);
	if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
		perror_free_struct(data, "Pipe redirect failed", 1);
	if (dup2(data->fd_out, STDOUT_FILENO) == -1)
		perror_free_struct(data, "Output redirect failed", 1);
	close(data->pipefd[0]);
	close(data->fd_out);
}

void	forks(char **argv, char **envp, t_pipe_data *data)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		perror_free_struct(data, "Fork failed", 1);
	if (data->pid1 == 0)
	{
		setup_pipe_fds(data);
		execute_command(argv[2], envp, data);
	}
	data->pid2 = fork();
	if (data->pid2 < 0)
		perror_free_struct(data, "Fork failed", 1);
	if (data->pid2 == 0)
	{
		setup_pipe_fds2(data);
		execute_command(argv[3], envp, data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	data;

	data = (t_pipe_data){0};
	if (argc != 5)
		return (write(2, "Wrong arguments\n", 16), 1);
	data.fd_in = open(argv[1], O_RDONLY);
	if (data.fd_in < 0)
		perror_free_struct(&data, "Input file error", 127);
	data.fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (data.fd_out < 0)
		perror_free_struct(&data, "Output file error", 127);
	if (pipe(data.pipefd) < 0)
		perror_free_struct(&data, "Pipe failed", 1);
	path_find_and_split(envp, &data);
	forks(argv, envp, &data);
	cleanup_and_wait(&data);
	return (0);
}
