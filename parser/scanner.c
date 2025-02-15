/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:56:33 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:29:14 by vvasiuko         ###   ########.fr       */
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

static void	handle_special(char **str, t_data *data)
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
			handle_q_string(str, data, **str);
	}
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

	str = data->input_copy;
	skip_whitespace(&str);
	while (*str)
	{
		if (skip_whitespace(&str) > 0)
			add_token(&data->tokens, create_token(TOKEN_SPACE, ft_strdup_safe(" ")));
		if (*str == '\0')
			break ;
		if (ft_strchr("|<>\"'", *str))
			handle_special(&str, data);
		else
			handle_string(&str, data);
	}
	return (EXIT_SUCCESS);
}
