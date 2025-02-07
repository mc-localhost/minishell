/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:56:33 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/28 17:48:47 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void handle_pipe(t_data *data)
// {
// 	printf("found TOKEN_PIPE\n");
// 	add_token(&data->tokens, create_token(TOKEN_PIPE, ft_strdup("|"), NULL, NULL)); //safe malloc needed
// }

// static void	handle_q_string(char *str, t_data *data, char q_type)
// {
// 	char	*token_start;
// 	t_token_type type;

// 	str++;
// 	token_start = str;
// 	while (*str != q_type)
// 		str++;
// 	if (q_type == '\'') //special token type because $ won't expand
// 		type = TOKEN_STRING_SINGLQ;
// 	else
// 		type = TOKEN_STRING;
// 	add_token(&data->tokens, create_token(type, strndup(token_start, str - token_start - 1), NULL, NULL));
		//replace strndup with custom ft_substr
// }

// static void	handle_string(char *str, t_data *data)
// {
// 	char	*token_start;

// 	token_start = str;
// 	while (*str && !ft_isspace(*str) && !ft_strchr("|<>\"'", *str))
// 		str++;
// 	add_token(&data->tokens, create_token(TOKEN_STRING, strndup(token_start, str - token_start), NULL, NULL)); //replace strndup with custom
// }

// static void heredoc(char *str, t_data *data)
// {
// 	// handle input redirection
// 	printf("found TOKEN_REDIRECT_IN\n");
// 	str++;
// 	if (*str && *str == '<')
// 	{
// 		str++;
// 		printf("heredoc\n");
// 	}
// 	add_token(&data->tokens, create_token(TOKEN_REDIRECT_IN, ft_strdup("<"), NULL, NULL)); //safe malloc needed
// }

// static void append(char *str, t_data *data)
// {
// 	// handle output redirection
// 	printf("found TOKEN_REDIRECT_OUT\n");
// 	str++;
// 	if (*str && *str == '>')
// 	{
// 		str++;
// 		printf("append\n");
// 	}
// 	add_token(&data->tokens, create_token(TOKEN_REDIRECT_OUT, ft_strdup(">"), NULL, NULL)); //safe malloc needed
// }

// static void handle_special(char *str, t_data *data)
// {
// 	if (*str && ft_strchr("|<>\"'", *str))
// 	{
// 		if (*str == '<')
// 			heredoc(str, data);
// 		else if (*str == '|')
// 			handle_pipe(data);
// 		else if (*str == '>')
// 			append(str, data);
// 		else if (*str == '\"' || *str == '\'')
// 			handle_q_string(str, data, *str);
// 	}
// }

// static int skip_whitespace(char *str)
// {
// 	int i;

// 	i = 0;
// 	while (*str && ft_isspace(*str))
// 	{
// 		str++;
// 		i++;
// 	}
// 	return (i);
// }

// int	scan(t_data *data)
// {
// 	char 	*str;

// 	str = data->input_copy;
// 	skip_whitespace(str);
// 	while (*str)
// 	{
// 		if (skip_whitespace(str) > 0)
// 			add_token(&data->tokens, create_token(TOKEN_SPACE, ft_strdup(" "), NULL, NULL)); //safe malloc needed
// 		if (*str == '\0')
// 			break ;
// 		handle_string(str, data);
// 		handle_special(str, data);
// 	}
// 	return (EXIT_SUCCESS);
// }

static void	handle_pipe(char **str, t_data *data)
{
	printf("found TOKEN_PIPE\n");
	add_token(&data->tokens, create_token(TOKEN_PIPE, ft_strdup("|"), NULL,
			NULL));
	(*str)++;
}

static void	handle_q_string(char **str, t_data *data, char q_type)
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
			type = TOKEN_STRING;
		add_token(&data->tokens, create_token(type, ft_substr(token_start, 0,
					*str - token_start), NULL, NULL));  //change to safe malloc
		(*str)++;
	}
}

static void	handle_string(char **str, t_data *data)
{
	char	*token_start;

	token_start = *str;
	while (**str && !ft_isspace(**str) && !ft_strchr("|<>\"'", **str))
		(*str)++;
	add_token(&data->tokens, create_token(TOKEN_STRING, ft_substr(token_start,
				0, *str - token_start), NULL, NULL));  //change to safe malloc
}

static void	heredoc(char **str, t_data *data)
{
	printf("found TOKEN_REDIRECT_IN\n");
	(*str)++;
	if (**str && **str == '<')
	{
		(*str)++;
		printf("heredoc\n");
		add_token(&data->tokens, create_token(TOKEN_HEREDOC, ft_strdup("<<"),
				NULL, NULL));
	}
	else
		add_token(&data->tokens, create_token(TOKEN_REDIRECT_IN, ft_strdup("<"),
				NULL, NULL));
}

static void	append(char **str, t_data *data)
{
	printf("found TOKEN_REDIRECT_OUT\n");
	(*str)++;
	if (**str && **str == '>')
	{
		(*str)++;
		printf("append\n");
		add_token(&data->tokens, create_token(TOKEN_APPEND, ft_strdup(">>"),
				NULL, NULL));
	}
	else
		add_token(&data->tokens, create_token(TOKEN_REDIRECT_OUT,
				ft_strdup(">"), NULL, NULL));
}

static void	handle_special(char **str, t_data *data)
{
	if (**str && ft_strchr("|<>\"'", **str))
	{
		if (**str == '<')
			heredoc(str, data);
		else if (**str == '|')
			handle_pipe(str, data);
		else if (**str == '>')
			append(str, data);
		else if (**str == '\"' || **str == '\'')
			handle_q_string(str, data, **str);
	}
}

static int	skip_whitespace(char **str)
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

int	scan(t_data *data)
{
	char	*str;

	str = data->input_copy;
	skip_whitespace(&str);
	while (*str)
	{
		if (skip_whitespace(&str) > 0)
			add_token(&data->tokens, create_token(TOKEN_SPACE, ft_strdup(" "),
					NULL, NULL));
		if (*str == '\0')
			break ;
		if (ft_strchr("|<>\"'", *str))
			handle_special(&str, data);
		else
			handle_string(&str, data);
	}
	return (EXIT_SUCCESS);
}
