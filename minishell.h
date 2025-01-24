/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/24 18:36:03 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef enum e_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECTION
}							t_node_type;

/* char **builtins;

echo, echo -n 	= print all args, add '\n' in the end if there is no -n flag
cd				= chdir(path)
pwd				= printf(getcwd())
env				= printf() all env variables
export			= change env value
unset			= remove env value
exit	exit(status)

*/

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

typedef struct s_node
{
	t_node_type				type;
	char					*misc;
	struct s_node			*next;
	union
	{
		// handle commands and redirections
		t_token				token;
		// handle pipes
		struct
		{
			struct s_node	*left;
			struct s_node	*right;
		} s_binary;
	} u_node_type;
}							t_node;

typedef struct s_ast
{
	// AST root
	t_node					*root;
	// store and modify env vars
	char					**env;
	// argc argv?
}							t_ast;

#endif