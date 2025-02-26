/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 17:26:37 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/26 23:51:23 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include "pipex.h"
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

void			tokens_cleanup(t_data *data);
/*	GARBAGE COLLECTOR	*/
void			*safe_malloc(size_t size);
void			free_all(void);
void			free_arr(char **str);
void			free_env(t_data *data);

/*	SAFE LIBFT	*/
char			*ft_itoa_safe(int n);
char			**ft_split_safe(char const *s, char c);
char			*ft_strdup_safe(const char *src);
char			*ft_strjoin_safe(char const *s1, char const *s2);
size_t			ft_strlcpy_safe(char *dst, const char *src, size_t dstsize);
char			*ft_substr_safe(char const *s, unsigned int start, size_t len);

/*	ENVIRONMENT	*/
int				if_env_var(t_env_node **head, const char *str);
char			*find_env_var(t_env_node **head, const char *str);
t_env_node		*create_env_var(char *key, char *value);
void			add_env_var(t_env_node **head, t_env_node *new_node);
void			change_env_var(t_env_node **head, const char *key,
					const char *value);
void			delete_env_var(t_env_node **head, const char *key);

t_env_node		*copy_env_list(t_env_node *original);
void			sort_env_list(t_env_node *head);
void			bash_sort_env_list(t_env_node *head);
void			free_env_list(t_env_node *head);

/*	TOKENS	*/
t_token			*init_token(void);
t_token			*init_current_cmd(void);
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_token **head, t_token *new_token);

/*	FINAL TOKENS	*/
int				is_redirection(t_token_type type);
int				add_redirection_to_cmd(t_token *cmd, t_token **current_ptr,
					t_data *data);

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
int				is_q_string(t_token_type type);
int				is_string(t_token_type type);
void			builtin_token(t_token *token);
int				process_tokens(t_data *data);
int				handle_heredoc(t_token *token, char *delim, t_data *data);
int				parse(t_data *data);

/*	SYNTAX	*/
int				print_syntax_error(t_token *token);
int				unclosed_quotes_error(char q_type);
int				first_is_pipe(t_token **head);
int				last_is_pipe(t_token **head);

/*	ITERATIONS	*/
typedef void	(*t_token_func)(t_token *, t_data *);
void			iterate_tokens(t_data *data, t_token_func func);
void			iterate_final_tokens(t_data *data, t_token_func func);
void			expand_token_values(t_token *token, t_data *data);
void			print_token(t_token *token, t_data *data);

/*	BUILTINS	*/
int				is_valid_identifier(const char *str);
int				print_export_error(char *identifier, char *name);
int				handle_builtin(t_token *token, t_data *data);
int				env(t_token *token, t_data *data);
int				export(t_token *token, t_data *data);
int				unset(t_token *token, t_data *data);
int				pwd(t_data *data);
int				echo(t_token *token);
int				cd(t_token *token, t_data *data);
int				custom_exit(t_token *token, t_data *data);
int				clean_exit(t_data *data);

/*	EXECUTOR	*/
char			**list_to_arr(t_env_node *current);
char			**build_cmd_array(t_token *token);
void			single_exec(char **cmd, char **env, t_token *token);
int				exe_builtin_cmd(t_token *token, t_data *data);
void			execute(t_token *token, t_data *data);

/*	PIPEX	*/
void			execute_pipeline(t_data *data);

/*	CMD_HELPERS	*/
char			*join_key_value(char *key, char *value);
int				count_nodes(t_env_node *current);
void			envp_to_list(t_data *data, char **envp, int i);
/*	REDIRECTION	*/
void			set_redirect(t_token *token);

/*	SIGNALS	*/
void			ctrl_c(int sig);
void			ctrl_c_heredoc(int sig);
void			ctrl_backslash(int sig);
void			setup_signals(void);

/*	GET NEXT LINE FOR TESTER	*/
char			*get_next_line(int fd); //remove before submitting

#endif