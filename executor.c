/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/23 15:03:09 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Counts valid nodes in the linked list
int	count_nodes(t_env_node *current)
{
	int	len;

	len = 0;
	while (current)
	{
		if (current->key && current->value)
			len++;
		current = current->next;
	}
	return (len);
}

// Joins key and value into a single string "key=value"
char	*join_key_value(char *key, char *value)
{
	char	*result;
	char	*final_result;

	result = ft_strjoin(key, "=");
	if (!result)
		return (NULL);
	final_result = ft_strjoin(result, value);
	free(result);
	return (final_result);
}

// Creates an array of strings from the linked list
char	**build_array(t_env_node *current, int len)
{
	char	**result;
	int		i;

	result = (char **)malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (current)
	{
		if (current->key && current->value)
		{
			result[i] = join_key_value(current->key, current->value);
			if (!result[i])
				return (free_arr(result), NULL);
			i++;
		}
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

char	**build_cmd_array(t_token *token)
{
	char	**result;
	int		i;

	result = (char **)malloc((token->args_count + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	result[0] = ft_strdup(token->value);
	if (!result[0])
		return (free(result), NULL);
	i = 0;
	while (token->args[i])
	{
		result[i + 1] = ft_strdup(token->args[i]);
		if (!result[i + 1])
			return (free_arr(result), NULL);
		i++;
	}
	result[i + 1] = NULL;
	return (result);
}

// Main function to convert linked list to array
char	**list_to_arr(t_env_node *current)
{
	int	len;

	len = count_nodes(current);
	if (len == 0)
		return (NULL);
	return (build_array(current, len));
}

void	single_exec(char **cmd, char **env, t_token *token)
{
	char	*path;

	set_redirect(token);
	path = find_path(cmd[0], env);
	if (!path)
	{
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		error_exit(": command not found", 127);
	}
	if (execve(path, cmd, env) == -1)
	{
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		free(path);
		error_exit(": Exec failed", 127);
	}
	free(path);
}

int	sys_cmd(char **cmd, char **envp, t_token *token)
{
	pid_t	pid;
	int		r;

	r = 0;
	if (!envp)
		error_exit("\nError: No environment variables found.", 127);
	pid = fork();
	if (pid == -1)
		error_exit("Fork failed", 127);
	if (pid == 0)
		single_exec(cmd, envp, token);
	waitpid(pid, &r, 0);
	r =  WEXITSTATUS(r);
	return (r);
}

int	exe_builtin_cmd(t_token *token, t_data *data, int fork)
{
	int		saved_stdin;
	int		saved_stdout;
	int		r;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	set_redirect(token);
	r = handle_builtin(token, data);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	if (fork == 1)
		exit(r);
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
		g_global.last_exit_code = exe_builtin_cmd(token, data, 0);
	else if (token->type == TOKEN_CMD)
	{
		cmd = build_cmd_array(token);
		if (!cmd)
			return ;
		env = list_to_arr(data->envs);
		if (!env)
			return (free_arr(cmd));
		g_global.last_exit_code = sys_cmd(cmd, env, token);
		free_arr(env);
		free_arr(cmd);
	}
}

void	execute_pipeline(t_data *data)
{
	t_token	*current;
	int		pipe_fds[2];
	int		prev_fd;
	pid_t	pid;

	prev_fd = -1;
	current = data->final_tokens;
	while (current)
	{
		if (current->next)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("Pipe failed");
				return ;
			}
		}
		pid = fork();
		if (pid == -1)
		{
			perror("Fork failed");
			return ;
		}
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				if (dup2(prev_fd, STDIN_FILENO) == -1)
				{
					perror("Dup2 failed (input)");
					exit(1);
				}
				close(prev_fd);
			}
			if (current->next)
				child(current, pipe_fds, data);
			else
				parent(current, pipe_fds, data);
		}
		if (prev_fd != -1)
			close(prev_fd);
		if (current->next)
		{
			close(pipe_fds[1]);
			prev_fd = pipe_fds[0];
		}
		current = current->next;
		waitpid(pid, NULL, 0);
	}
}
