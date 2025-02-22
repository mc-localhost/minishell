/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:01 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/22 17:51:17 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

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
	// technically prev
	struct s_env_node		*next;
}							t_env_node;

/*	FOR PARSING		*/

typedef enum e_token_type
{
	TOKEN_STRING,
	TOKEN_STRING_SINGLQ,
	TOKEN_STRING_DOUBLEQ, // important for heredoc
	TOKEN_SPACE,
	TOKEN_CMD,
	TOKEN_BUILTIN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_INVALID,
	PROCESSED
}							t_token_type;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_token
{
	t_token_type			type;
	// for command name
	char					*value;
	// for command flags and etc.
	char					**args;
	int						args_count;
	// for redirections
	t_redirection			*redirections_in;
	t_redirection			*redirections_out;
	struct s_token			*prev;
	struct s_token			*next;
}							t_token;

/*	FOR STORING VARS AND COMMANDS	*/

typedef struct s_data
{
	char					*input;
	t_token					*tokens;
	t_token					*final_tokens;
	int						num_pipes;
	t_env_node				*envs;
}							t_data;

/*	GLOBAL	*/

typedef struct s_global
{
	t_alloc_node			*garbage_list;
	int						last_exit_code;
	int						heredoc_running;
	int						cmd_running;
}							t_global;

t_global					g_global;

#endif