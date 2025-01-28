/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 16:35:16 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <stdio.h>  // printf, perror
# include <stdlib.h> // malloc, free, getenv, exit
// write, access, read, close, fork, dup, dup2, pipe, isatty
# include <dirent.h>    // opendir, readdir, closedir
# include <fcntl.h>     // open, unlink
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/types.h> // opendir, readdir, closedir, fork, wait
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <termcap.h>   // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h>   // tcsetattr, tcgetattr
# include <unistd.h>
// readline, add_history
# include <readline/readline.h>
// rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay
# include <readline/history.h>

# define PROMPT "minishell> "

/*	G	L	O	B	A	L		V	A	R	I	A	B	L	E	S	*/
int				g_last_exit_code;
t_alloc_node	*g_garbage_list;

/*	F 	U 	N 	C 	T 	I 	O 	N 	S	*/

/*	GARBAGE COLLECTOR	*/
void			*safe_malloc(size_t size);
void			free_all(void);

/*	ENVIRONMENT	*/
t_env_node		*create_env_var(char *key, char *value);
void			add_env_var(t_env_node **head, t_env_node *new_node);
void			change_env_var(t_env_node **head, const char *key,
					const char *value);
void			delete_env_var(t_env_node **head, const char *key);
void			envp_to_list(t_data *data, char **envp, int i);
void			print_env_list(t_env_node *current);

/*	PARSER	*/
t_token			*create_token(t_token_type type, char *value, char **args, char *file);
void			add_token(t_token **head, t_token *new_token);
void			print_tokens(t_token *current);
int				scan(char *str, t_data *data);
/*	MAIN	*/

#endif