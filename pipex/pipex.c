/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:33 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/19 20:38:55 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec(char *argv, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (!cmd)
		error_exit("ft_split failed");
	cmd = optmize_cmd(cmd, argv);
	path = find_path(cmd[0], env);
	if (!path)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		free_exit_error(cmd, ": command not found");
	}
	if (execve(path, cmd, env) == -1)
	{
		write(STDERR_FILENO, "pipex: ", 7);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		free(path);
		free_exit_error(cmd, ": Exec failed");
	}
	free_arr(cmd);
	free(path);
}

int	open_file(char *filename, int output)
{
	int	fd;

	if (output == 0)
		return (open(filename, O_RDONLY, 0777));
	else if (output == 1)
	{
		fd = open(filename, O_RDONLY, 0777);
		if (fd > 0)
		{
			close(fd);
			unlink(filename);
		}
		return (open(filename, O_WRONLY | O_CREAT, 0644));
	}
	return (-1);
}

void	child(char **argv, int *pipefd, char **env)
{
	int		fd;

	fd = open_file(argv[1], 0);
	if (fd == -1)
	{
		write(STDERR_FILENO, "pipex: input: ", 14);
		error_exit("");
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exec(argv[2], env);
}

void	parent(char **argv, int *pipefd, char **env)
{
	int		fd;

	fd = open_file(argv[4], 1);
	if (fd == -1)
	{
		write(STDERR_FILENO, "pipex: output: ", 14);
		error_exit("");
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	exec(argv[3], env);
}

int	pipex(int argc, char **argv, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		errno = EINVAL;
		error_exit("\nUsage: ./pipex <file1> <cmd1> <cmd2> <file2>");
	}
	if (!envp)
		error_exit("\nError: No environment variables found.");
	if (pipe(pipefd) == -1)
		error_exit("Pipe failed");
	pid = fork();
	if (pid == -1)
		error_exit("Fork failed");
	if (pid == 0)
		child(argv, pipefd, envp);
	parent(argv, pipefd, envp);
	waitpid(pid, NULL, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
