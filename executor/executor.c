/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 17:17:07 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exec_error(char *cmd, t_data *data, int type)
{
	char	*err;
	err = ft_strdup_safe("minishell: ");
	if (!ft_strcmp(cmd, "."))
	{
		err = ft_strjoin_safe(err, "filename argument required\n.: usage: . filename [arguments]");
		type = 127;
	}
	else if (is_directory(cmd) && ft_strchr(cmd, '/'))
	{
		err = ft_strjoin_safe(err, ft_strjoin_safe(cmd, ": is a directory"));
		free(cmd);
	}
	else
	{
		err = ft_strjoin_safe(err, ft_strjoin_safe(cmd, ": "));
		if (!is_directory(cmd) && !ft_strchr(cmd, '/'))
			type = 127;
		free(cmd);
		if (type == 127)
			err = ft_strjoin_safe(err, "command not found");
		else if (type == 126)
			err = ft_strjoin_safe(err, "Permission denied");
		else
			err = ft_strjoin_safe(err, strerror(errno));
	}
	error_exit(err, type, data);
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
	// if (!envp)
	// 	error_exit("\nError: No environment variables found.", 127, data);
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
		g_global.last_exit_code = sys_cmd(cmd, env, token, data);
		free_arr(env);
		free_arr(cmd);
	}
}
