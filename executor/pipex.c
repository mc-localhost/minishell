/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 22:47:33 by aelaaser          #+#    #+#             */
/*   Updated: 2025/03/07 12:48:31 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child(t_token *token, int *pipefd, t_data *data)
{
	char	**envp;
	char	**cmd;

	envp = list_to_arr(data->envs);
	set_redirect(token, data);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (token->type == TOKEN_BUILTIN)
		g_global.last_exit_code = exe_builtin_cmd(token, data);
	else
	{
		cmd = build_cmd_array(token);
		if (cmd)
		{
			single_exec(cmd, envp, token, data);
			free(cmd);
		}
		else
			g_global.last_exit_code = 1;
	}
	free_arr(envp);
	clean_exit(data);
}

void	redirect_to_prev_fd(int prev_fd, int pipefd[2], t_token *current)
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
	if (current->next)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}

void	parent(int *pid_list, int i)
{
	int	j;
	int	status;

	j = 0;
	while (j < i)
	{
		waitpid(pid_list[j], &status, 0);
		j++;
	}
	if (WIFEXITED(status))
		g_global.last_exit_code = WEXITSTATUS(status);
}

void	execute_pipx(t_token *current, int pipefd[2], int parm[2], t_data *data)
{
	pid_t	pid;
	int		pid_list[1024];

	data->is_active = 1;
	while (current)
	{
		if (current->next && pipe(pipefd) == -1)
			return (perror("Pipe failed"));
		pid = fork();
		if (pid == -1)
			return (perror("Fork failed"));
		if (pid == 0)
			redirect_to_prev_fd(parm[0], pipefd, current);
		if (pid == 0)
			child(current, pipefd, data);
		else
			pid_list[parm[1]++] = pid;
		if (parm[0] != -1)
			close(parm[0]);
		parm[0] = pipefd[0];
		close(pipefd[1]);
		current = current->next;
	}
	parent(pid_list, parm[1]);
	data->is_active = 0;
}

// parm[0] = prev_fd
// parm[1] = pid_counter
void	execute_pipeline(t_data *data)
{
	t_token	*current;
	int		pipefd[2];
	int		parm[2];

	parm[0] = -1;
	parm[1] = 0;
	current = data->final_tokens;
	return (execute_pipx(current, pipefd, parm, data));
}
