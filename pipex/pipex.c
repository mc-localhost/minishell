/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:33 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/23 00:29:08 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char *filename, int output)
{
	int	fd;

	if (output == 0)
		return (open(filename, O_RDONLY));
	else if (output == 1)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd > 0)
			return (fd);
	}
	return (-1);
}

void	child(t_token *token, int *pipefd, t_data *data)
{
	char	**envp;
	char	**cmd;

	envp = list_to_arr(data->envs);
	set_redirect(token);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (token->type == TOKEN_BUILTIN)
		exe_builtin_cmd(token, data, 1);
	else
	{
		cmd = build_cmd_array(token);
		if (!cmd)
		{
			free_arr(envp);
			exit(1);
		}
		single_exec(cmd, envp, token);
		free(cmd);
	}
	free_arr(envp);
}

void	parent(t_token *token, int *pipefd, t_data *data)
{
	char	**envp;
	char	**cmd;

	envp = list_to_arr(data->envs);
	set_redirect(token);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (token->type == TOKEN_BUILTIN)
		exe_builtin_cmd(token, data, 1);
	else
	{
		cmd = build_cmd_array(token);
		if (!cmd)
		{
			free_arr(envp);
			exit(1);
		}
		single_exec(cmd, envp, token);
		free(cmd);
	}
	free_arr(envp);
}

int	pipex(t_token *token, t_data *data)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (errno);
	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
		child(token, pipefd, data);
	parent(token->next, pipefd, data);
	waitpid(pid, NULL, 0);
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}
