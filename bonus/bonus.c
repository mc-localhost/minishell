/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:50:02 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/12/20 16:35:07 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	create_process(char *cmd, char **envp, t_pipe_data *data)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) < 0)
		perror_exit("Pipe error", 1, data);
	pid = fork();
	if (pid < 0)
		perror_exit("Fork error", 1, data);
	if (pid == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) < 0)
			perror_exit("Pipe redirect failed", 1, data);
		close(pipefd[1]);
		execute_command(cmd, envp, data);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) < 0)
			perror_exit("Pipe redirect failed", 1, data);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
	}
}

void	init(int argc, char **argv, char **envp, t_pipe_data *data)
{
	data->paths = path_find_and_split(envp);
	if (!data->paths)
	{
		write(2, "PATH split failed\n", 18);
		exit(1);
	}
	data->fd_in = open(argv[1], O_RDONLY);
	if (data->fd_in < 0)
		perror_exit("Input file error", 127, data);
	data->fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->fd_out < 0)
		perror_exit("Output file error", 127, data);
	if (dup2(data->fd_in, STDIN_FILENO) < 0)
		perror_exit("Pipe redirect failed", 1, data);
	close(data->fd_in);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe_data	data;
	int			i;

	data = (t_pipe_data){0};
	if (argc >= 5)
	{
		init(argc, argv, envp, &data);
		i = 2;
		while (i < argc - 2)
			create_process(argv[i++], envp, &data);
		if (dup2(data.fd_out, STDOUT_FILENO) < 0)
			perror_exit("Pipe redirect failed", 1, &data);
		close(data.fd_out);
		execute_command(argv[argc - 2], envp, &data);
		ft_free_split(data.paths);
	}
	else
		return (write(2, "Wrong arguments\n", 16), 1);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_pipe_data	data;
// 	int			i;

// 	data = (t_pipe_data){0};
// 	if (argc < 5)
// 		return (write(2, "Wrong arguments\n", 16), 1);
// 	data.cmd_num = argc - 3;
// 	data.pipes_num = argc - 4;
// 	path_find_and_split(envp, &data);
// 	data.fd_in = open(argv[1], O_RDONLY);
// 	if (data.fd_in < 0)
// 		perror_free_struct(&data, "Input file error", 127);
// 	data.fd_out = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0000644);
// 	if (data.fd_out < 0)
// 		perror_free_struct(&data, "Output file error", 127);
// 	data.pipefd = malloc(data.pipes_num * sizeof(int[2]));
// 	if (!data.pipefd)
// 		perror_free_struct(&data, "Pipes malloc failed", 1);
// 	i = 0;
// 	while (i < data.pipes_num)
// 	{
// 		data.pipefd[i][0] = 0;
// 		data.pipefd[i][1] = 0;
// 		if (pipe(data.pipefd[i]) < 0)
// 			perror_free_struct(&data, "Pipe failed", 1);
// 		i++;
// 	}
// 	data.pids = malloc(data.cmd_num * sizeof(pid_t));
// 	if (!data.pids)
// 		perror_free_struct(&data, "Processes malloc failed", 1);
// 	data.pids[0] = fork();
// 	if (data.pids[0] < 0)
// 		perror_free_struct(&data, "Fork failed", 1);
// 	if (data.pids[0] == 0)
// 	{
// 		setup_pipe_fds(&data);
// 		execute_command(argv[2], envp, &data);
// 	}
// 	return (0);
// }
