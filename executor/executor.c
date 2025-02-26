/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 00:37:40 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_exec(char **cmd, char **env, t_token *token, t_data *data)
{
	char	*path;

	set_redirect(token, data);
	path = NULL;
	if (ft_strlen(cmd[0]) > 0)
		path = find_path(cmd[0], env);
	if (!path)
	{
		ft_putstr_stderr("minishell: ");
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": ", 2);
		error_exit("", 127, data);
	}
	if (execve(path, cmd, env) == -1)
	{
		ft_putstr_stderr("minishell: ");
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": ", 2);
		free(path);
		error_exit("", 126, data);
	}
	free(path);
}

int	sys_cmd(char **cmd, char **envp, t_token *token, t_data *data)
{
	pid_t	pid;
	int		r;

	r = 0;
	if (!envp)
		error_exit("\nError: No environment variables found.", 127, data);
	pid = fork();
	if (pid == -1)
		error_exit("Fork failed", 127, data);
	if (pid == 0)
		single_exec(cmd, envp, token, data);
	waitpid(pid, &r, 0);
	if (WIFEXITED(r))
		g_global.last_exit_code = WEXITSTATUS(r);
	return (g_global.last_exit_code);
}

int	exe_builtin_cmd(t_token *token, t_data *data)
{
	int		saved_stdin;
	int		saved_stdout;
	int		r;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	set_redirect(token, data);
	r = handle_builtin(token, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (r);
}
//	we don't need it anymore
// int	builtin_cmd(t_token *token, t_data *data)
// {
// 	pid_t	pid;

//     pid = fork();
//     if (pid == -1)
//         error_exit("Fork failed");
//     if (pid == 0)
//         exe_builtin_cmd(token, data, 1);
//     waitpid(pid, NULL, 0);
// 	return (0);
// }

void	execute(t_token *token, t_data *data)
{
	char	**env;
	char	**cmd;

	if (token->type == TOKEN_BUILTIN && data->num_pipes == 0)
		g_global.last_exit_code = exe_builtin_cmd(token, data);
	else if (token->type == TOKEN_CMD)
	{
		cmd = build_cmd_array(token);
		if (!cmd)
			return ;
		env = list_to_arr(data->envs);
		if (!env)
			return (free_arr(cmd));
		g_global.last_exit_code = sys_cmd(cmd, env, token, data);
		free_arr(env);
		free_arr(cmd);
	}
}
