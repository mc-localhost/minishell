/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/21 19:19:43 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Counts valid nodes in the linked list
int	count_nodes(t_env_node *current)
{
	int len;
	
	len = 0;
	while (current)
	{
		if (current->key && current->value)
			len++;
		current = current->next;
	}
	return len;
}

// Joins key and value into a single string "key=value"
char	*join_key_value(char *key, char *value)
{
	char	*result;
	char	*final_result;
    
	result = ft_strjoin(key, "=");
	if (!result)
    	return NULL;
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

void	single_exec(char **cmd, char **env)
{
	char	*path;

	path = find_path(cmd[0], env);
	if (!path)
	{
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		error_exit(": command not found");
	}
	if (execve(path, cmd, env) == -1)
	{
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		free(path);
		error_exit(": Exec failed");
	}
	free(path);
}

char *get_redirection(t_redirection *head, int out)
{
	t_redirection	*current = head;
	char			*direction;
	int				fd;
    
	direction = NULL;
	while (current != NULL)
	{
		direction = current->file;
		if (current->next && out == 1)
		{
			fd = open_file(direction, 1);
			if (fd == -1)
			{
				return (NULL);//we need error handler here
			}
			close(fd);
		}
        current = current->next;
	}
	return (direction);
}
//pipefd[2] 0 for output 1 for input;
int	sys_cmd(char **cmd, char **envp, t_token *token)
{
	int		pipefd[2];
	char	*output;
	pid_t	pid;

	if (!envp)
		error_exit("\nError: No environment variables found.");
	output = get_redirection(token->redirections_out, 1);
	if (output != NULL)
	{
		printf("output redirect to %s\n", output);
		pipefd[0] = open(output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (pipefd[0] == -1)
		{
			write(STDERR_FILENO, "direction: input: ", 18);//we need error handler here
			return (-1);
		}
	}
    pid = fork();
    if (pid == -1)
        error_exit("Fork failed");
    if (pid == 0)
    {
		if (output != NULL)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
        single_exec(cmd, envp);
    }
    waitpid(pid, NULL, 0);
    //close(fd);
	if (output != NULL) {
		close(pipefd[0]);
	}
	return (0);
}

void	execute(t_token *token, t_data *data)
{
	char	**env;
	char	**cmd;
	if (token->type == TOKEN_BUILTIN)
	{
		handle_builtin(token, data);
		// active = 0; //should go somewhere in data or be global
	}
	else if (token->type == TOKEN_CMD)
	{
		cmd = build_cmd_array(token);
		if (!cmd)
			return ;
		env = list_to_arr(data->envs);
		if (!env)
			return (free_arr(cmd));
		sys_cmd(cmd, env, token);
		free_arr(env);
		free_arr(cmd);
	}
}
