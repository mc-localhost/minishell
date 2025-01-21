/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:50:05 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/12/20 16:23:02 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

/* for libft */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/* write, read, close, access, pipe, dup, dup2, execve, fork */
# include <sys/types.h>
# include <sys/uio.h>

/* strerror */
# include <string.h>

/* open, unlink */
# include <fcntl.h>

/* waitpid, wait */
# include <sys/wait.h>

// typedef struct s_pipe_data
// {
// 	int		fd_in;
// 	int		fd_out;
// 	int		cmd_num;
// 	int		pipes_num;
// 	int		pipefd_in[2];
// 	int		pipefd_out[2];
// 	pid_t	*pids;
// 	int		(*pipefd)[2];
// 	char	**paths;
// }			t_pipe_data;

typedef struct s_pipe_data
{
	int		fd_in;
	int		fd_out;
	char	**paths;
}			t_pipe_data;

char		**ft_split(char const *s, char c);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		ft_free_split(char **split);
void		perror_exit(char *msg, int i, t_pipe_data *data);

char		**path_find_and_split(char **envp);
char		*find_exec(char *cmd, t_pipe_data *data);
void		execute_command(char *cmd, char **envp, t_pipe_data *data);
void		create_process(char *cmd, char **envp, t_pipe_data *data);
void		init(int argc, char **argv, char **envp, t_pipe_data *data);

#endif