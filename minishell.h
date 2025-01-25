/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/25 17:10:24 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
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

/*	FOR GARBAGE COLLECTOR	*/

typedef struct s_alloc_node
{
	void					*ptr;
	struct s_alloc_node		*next;
}							t_alloc_node;

/*	FOR ENVIRONMENT VARIABLES	*/

typedef struct s_env_node
{
	char					*key;
	char					*value;
	struct s_env_node *next; // technically prev, not next
}							t_env_node;

/*	FOR PARSING		*/

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF,
	TOKEN_INVALID
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	// for command name
	char					*value;
	// for command flafs and etc.
	char					**args;
	// for redirections
	char					*file;
}							t_token;

/*	FOR STORING VARS AND COMMANDS	*/

typedef struct s_ast
{
	// list of tokens? t_token *tokens;
	t_env_node				*envs;
}							t_ast;

/*	GLOBAL	*/
t_alloc_node				*g_garbage_list;
t_ast						g_ast;

/*	F 	U 	N 	C 	T 	I 	O 	N 	S	*/

/*	GARBAGE COLLECTOR	*/
void						*safe_malloc(size_t size);
void						free_all(void);

/*	ENVIRONMENT	*/
t_env_node					*create_env_var(char *key, char *value);
void						add_env_var(t_env_node **head,
								t_env_node *new_node);
void						change_env_var(t_env_node **head, const char *key,
								const char *value);
void						delete_env_var(t_env_node **head, const char *key);
void						envp_to_list(char **envp, int i);
void						print_env_list(t_env_node *current);

/*	MAIN	*/

#endif

// typedef enum e_node_type
// {
// 	AST_COMMAND,
// 	AST_PIPE,
// 	AST_REDIRECTION
// }							t_node_type;

// typedef struct s_node
// {
// 	t_node_type				type;
// 	char					*misc;
// 	struct s_node			*next;
// 	union
// 	{
// 		// handle commands and redirections
// 		t_token				token;
// 		// handle pipes
// 		struct
// 		{
// 			struct s_node	*left;
// 			struct s_node	*right;
// 		} s_binary;
// 	} u_node_type;
// }							t_node;