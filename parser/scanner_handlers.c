/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:09:03 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/17 16:28:31 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_pipe(char **str, t_data *data)
{
	add_token(&data->tokens, create_token(TOKEN_PIPE, ft_strdup_safe("|")));
	(*str)++;
}

int	handle_q_string(char **str, t_data *data, char q_type)
{
	char			*token_start;
	t_token_type	type;

	(*str)++;
	token_start = *str;
	while (**str && **str != q_type)
		(*str)++;
	if (**str == q_type)
	{
		if (q_type == '\'')
			type = TOKEN_STRING_SINGLQ;
		else
			type = TOKEN_STRING_DOUBLEQ;
		add_token(&data->tokens, create_token(type, ft_substr_safe(token_start,
					0, *str - token_start)));
		(*str)++;
	}
	else
		return (unclosed_quotes_error(q_type));
	return (EXIT_SUCCESS);
}

void	handle_string(char **str, t_data *data)
{
	char	*token_start;

	token_start = *str;
	while (**str && !ft_isspace(**str) && !ft_strchr("|<>\"'", **str))
		(*str)++;
	add_token(&data->tokens, create_token(TOKEN_STRING,
			ft_substr_safe(token_start, 0, *str - token_start)));
}

void	handle_in(char **str, t_data *data)
{
	(*str)++;
	if (**str && **str == '<')
	{
		(*str)++;
		add_token(&data->tokens, create_token(TOKEN_HEREDOC,
				ft_strdup_safe("<<")));
	}
	else
		add_token(&data->tokens, create_token(TOKEN_REDIRECT_IN,
				ft_strdup_safe("<")));
}

void	handle_out(char **str, t_data *data)
{
	(*str)++;
	if (**str && **str == '>')
	{
		(*str)++;
		add_token(&data->tokens, create_token(TOKEN_APPEND,
				ft_strdup_safe(">>")));
	}
	else
		add_token(&data->tokens, create_token(TOKEN_REDIRECT_OUT,
				ft_strdup_safe(">")));
}
