/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 16:31:18 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exec_error(char *cmd, t_data *data, int type)
{
	ft_putstr_stderr("minishell: ");
	if (!ft_strcmp(cmd, "."))
	{
		ft_putstr_stderr("filename argument required\n");
		error_exit(".: usage: . filename [arguments]", 127, data);
	}
	else if (is_directory(cmd) && ft_strchr(cmd, '/'))
	{
		ft_putstr_stderr(cmd);
		free(cmd);
		error_exit(": is a directory", type, data);
	}
	else
	{
		ft_putstr_stderr(cmd);
		ft_putstr_stderr(": ");
		if (is_directory(cmd) && !ft_strchr(cmd, '/'))
			type = 127;
		free(cmd);
		if (type == 127)
			error_exit("command not found", type, data);
		error_exit("", type, data);
	}
}

void	single_exec(char **cmd, char **env, t_token *token, t_data *data)
{
	char	*path;

	set_redirect(token, data);
	path = NULL;
	if (ft_strlen(cmd[0]) > 0)
		path = find_path(cmd[0], env);
	if (!path)
		print_exec_error(cmd[0], data, 127);
	if (execve(path, cmd, env) == -1)
	{
		if (errno == 2)
			print_exec_error(path, data, 127);
		print_exec_error(path, data, 126);
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
