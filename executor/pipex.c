/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:33 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/26 19:06:58 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	redirect_to_prev_fd(int prev_fd)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 failed (input)");
			exit(errno);
		}
		close(prev_fd);
	}
}

void	execute_pipx(t_token *current, int pipefd[2], int parm[2], t_data *data)
{
	pid_t	pid;

	while (current)
	{
		if (current->next && pipe(pipefd) == -1)
			return (perror("Pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("Fork failed"));
		if (pid == 0)
			redirect_to_prev_fd(parm[0]);
		if (pid == 0)
			child(current, pipefd, data);
		current = current->next;
		if (parm[0] != -1)
			close(parm[0]);
		parm[0] = pipefd[0];
		close(pipefd[1]);
		if (!current)
			waitpid(pid, &parm[1], 0);
		if (WIFEXITED(parm[1]))
			g_global.last_exit_code = WEXITSTATUS(parm[1]);
	}
}

// parm[0] = prev_fd
// parm[1] = r
void	execute_pipeline(t_data *data)
{
	t_token	*current;
	int		pipefd[2];
	int		parm[2];

	parm[0] = -1;
	current = data->final_tokens;
	return (execute_pipx(current, pipefd, parm, data));
}
