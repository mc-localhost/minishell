/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:38:12 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/24 11:18:19 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Expander expands
	- $USER to username found in environment variables,
	if variable with such name is not found, it's replaced
	with nothing.
	- $? to global variable used for storing last exit code.
	- $ with nothing afterwards to $ (basically remains unchanged).

Regular bash also handles cases like $$, $0
but they are out of scope of this project.

When expanding double-quoted string, the token remains.
When expanding just string, the expansion from the environment variable
gets split by sequences of spaces and turns into several SINGLE_Q tokens
and SPACE tokens, the rest of STRING gets saved, too. The initial token
is marked as PROCESSED.
*/

static void	insert_after(t_token *current, t_token *new_token)
{
	t_token	*next_token;

	if (!current || !new_token)
		return ;
	next_token = current->next;
	current->next = new_token;
	new_token->prev = current;
	if (next_token)
	{
		new_token->next = next_token;
		next_token->prev = new_token;
	}
	else
		new_token->next = NULL;
}

static void	new_single_string(char **str, t_token *token)
{
	char	*token_start;
	char	*new_string;

	token_start = *str;
	while (**str && !ft_isspace(**str))
		(*str)++;
	new_string = ft_substr_safe(token_start, 0, *str - token_start);
	insert_after(token, create_token(TOKEN_STRING_SINGLQ, new_string));
}

static void	expand_to_more(t_token *token, t_data *data)
{
	char	*str;
	t_token	*last_inserted;

	last_inserted = token;
	str = expand(token->value, data);
	while (*str)
	{
		if (skip_whitespace(&str) > 0)
		{
			insert_after(last_inserted, create_token(TOKEN_SPACE,
					ft_strdup_safe(" ")));
			last_inserted = last_inserted->next;
		}
		if (*str == '\0')
			break ;
		else
		{
			new_single_string(&str, last_inserted);
			last_inserted = last_inserted->next;
		}
	}
	token->type = PROCESSED;
}

void	expand_token_values(t_token *token, t_data *data)
{
	if (token->prev && token->prev->type == TOKEN_HEREDOC)
		return ;
	if (token->prev && token->prev->prev
		&& token->prev->prev->type == TOKEN_HEREDOC)
		return ;
	if (token->type == TOKEN_STRING_DOUBLEQ)
	{
		if (!ft_strchr(token->value, '$'))
			return ;
		token->value = expand(token->value, data);
	}
	else if (token->type == TOKEN_STRING)
	{
		if (!ft_strchr(token->value, '$'))
			return ;
		else if (!ft_strncmp(token->value, "$", 2) && token->next
			&& is_q_string(token->next->type))
		{
			token->value = ft_strdup_safe("");
			return ;
		}
		expand_to_more(token, data);
	}
	else
		return ;
}
