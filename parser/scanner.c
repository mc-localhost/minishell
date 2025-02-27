/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:56:33 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/27 01:25:07 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_whitespace(char **str)
{
	int	i;

	i = 0;
	while (**str && ft_isspace(**str))
	{
		(*str)++;
		i++;
	}
	return (i);
}

static int	handle_special(char **str, t_data *data)
{
	if (**str && ft_strchr("|<>\"'", **str))
	{
		if (**str == '<')
			handle_in(str, data);
		else if (**str == '>')
			handle_out(str, data);
		else if (**str == '|')
			handle_pipe(str, data);
		else if (**str == '\"' || **str == '\'')
			return (handle_q_string(str, data, **str));
	}
	return (EXIT_SUCCESS);
}

/*
Scanner is looping through the input character by character
not skipping spaces but rather creating a token for any sequence of spaces.

Strings quoted with "", '' and unquoted are handled separately.
Each redirection has its own token type as well.
*/

int	scan(t_data *data)
{
	char	*str;

	if (!data->input)
		return (EXIT_FAILURE);
	str = data->input;
	skip_whitespace(&str);
	while (*str)
	{
		if (skip_whitespace(&str) > 0)
			add_token(&data->tokens, create_token(TOKEN_SPACE,
					ft_strdup_safe(" ")));
		if (*str == '\0')
			break ;
		if (ft_strchr("|<>\"'", *str))
		{
			if (handle_special(&str, data) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			handle_string(&str, data);
	}
	return (EXIT_SUCCESS);
}
