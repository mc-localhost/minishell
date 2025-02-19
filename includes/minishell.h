/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 17:40:52 by vvasiuko         ###   ########.fr       */
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
# define HEREDOC_PROMPT "> "
# define HEREDOC_FILENAME ".heredoc_file"

/*	F 	U 	N 	C 	T 	I 	O 	N 	S	*/

/*	GARBAGE COLLECTOR	*/
void			*safe_malloc(size_t size);
void			free_all(void);
void			free_arr(char **str);

/*	SAFE LIBFT	*/
char			*ft_itoa_safe(int n);
char			**ft_split_safe(char const *s, char c);
char			*ft_strdup_safe(const char *src);
char			*ft_strjoin_safe(char const *s1, char const *s2);
size_t			ft_strlcpy_safe(char *dst, const char *src, size_t dstsize);
char			*ft_substr_safe(char const *s, unsigned int start, size_t len);

/*	ENVIRONMENT	*/
char			*find_env_var(t_env_node **head, const char *str);
t_env_node		*create_env_var(char *key, char *value);
void			add_env_var(t_env_node **head, t_env_node *new_node);
void			change_env_var(t_env_node **head, const char *key,
					const char *value);
void			delete_env_var(t_env_node **head, const char *key);
void			envp_to_list(t_data *data, char **envp, int i);
void			print_env_list(t_env_node *current);

/*	TOKENS	*/
t_token			*init_token(void);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);

/*	SCANNER	*/
int				skip_whitespace(char **str);
int				scan(t_data *data);
void			handle_pipe(char **str, t_data *data);
int				handle_q_string(char **str, t_data *data, char q_type);
void			handle_string(char **str, t_data *data);
void			handle_in(char **str, t_data *data);
void			handle_out(char **str, t_data *data);

/*	PARSER	*/
char			*expand(char *str, t_data *data);
int				is_string(t_token_type type);
void			builtin_token(t_token *token);
int				process_tokens(t_data *data);
char			*handle_heredoc(t_token *token, t_data *data);
int				parse(t_data *data);

/*	SYNTAX	*/
int				print_syntax_error(t_token *token);
int				unclosed_quotes_error(char q_type);

/*	FINAL TOKENS	*/
int				is_redirection(t_token_type type);
int				add_redirection_to_cmd(t_token *cmd, t_token **current_ptr,
					t_data *data);

/*	ITERATIONS	*/
typedef void	(*t_token_func)(t_token *, t_data *);
void			iterate_tokens(t_data *data, t_token_func func);
void			iterate_final_tokens(t_data *data, t_token_func func);
void			expand_token_values(t_token *token, t_data *data);
void			print_token(t_token *token, t_data *data);

/*	BUILTINS	*/
int				handle_builtin(t_token *token, t_data *data);
int				env(t_token *token, t_data *data);
int				export(t_token *token, t_data *data);
int				unset(t_token *token, t_data *data);
void			pwd(t_data *data);
int				echo(t_token *token);
int				cd(t_token *token, t_data *data);
void			custom_exit(t_token *token);

/*	EXECUTOR	*/
void			execute(t_token *token, t_data *data);

/*	SIGNALS	*/
void			setup_signals(void);

/*	GET NEXT LINE FOR TESTER	*/
char			*get_next_line(int fd);

#endif