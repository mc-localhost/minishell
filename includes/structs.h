/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:01 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 18:05:07 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "minishell.h"

/*	FOR GARBAGE COLLECTOR	*/

typedef struct s_alloc_node
{
	void				*ptr;
	struct s_alloc_node	*next;
}						t_alloc_node;

/*	FOR ENVIRONMENT VARIABLES	*/

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node *next; // technically prev, not next
}						t_env_node;

/*	FOR PARSING		*/

typedef enum e_token_type
{
	TOKEN_STRING,
	TOKEN_STRING_SINGLQ,
	TOKEN_SPACE,
	TOKEN_CMD,
	TOKEN_BUILTIN,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_INVALID
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	// for command name
	char				*value;
	// for command flags and etc.
	char				**args;
	int					args_count;
	// for redirections
	char				*file;
	struct s_token		*prev;
	struct s_token		*next;
}						t_token;

/*	FOR STORING VARS AND COMMANDS	*/

typedef struct s_data
{
	char				*input;
	char				*input_copy;
	t_token				*tokens;
	t_env_node			*envs;
}						t_data;

#endif