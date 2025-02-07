// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   scanner.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/01/25 17:56:33 by vvasiuko          #+#    #+#             */
// /*   Updated: 2025/01/28 17:48:47 by vvasiuko         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// static int	handle_pipe(int i, t_data *data)
// {
// 	printf("found TOKEN_PIPE at index %i\n", i);
// 	add_token(&data->tokens, create_token(TOKEN_PIPE, "|", NULL, NULL));
// 	return (i + 1);
// }

// static int	handle_q_string(int i, char *str, t_data *data, char c)
// {
// 	int		str_start_i;
// 	int		str_end_i;
// 	char	*string;

// 	str_start_i = i;
// 	i++;
// 	while (str[i] && str[i] != c)
// 	{
// 		printf("char: %c\n", str[i]);
// 		i++;
// 	}
// 	str_end_i = i;
// 	if (str_end_i > str_start_i)
// 	{
// 		printf("reached end with char %c at index %i\n", str[str_end_i],
// 			str_end_i);
// 		printf("start index %i, end index %i, end-start+1= %i\n", str_start_i,
// 			str_end_i, str_end_i - str_start_i + 1);
// 		string = ft_substr(str, str_start_i, str_end_i - str_start_i + 1);
// 		// safe_malloc needed
// 		printf("quoted string: %s\n\n", string);
// 		add_token(&data->tokens, create_token(TOKEN_STRING, "", NULL, NULL));
// 		free(string);
// 	}
// 	return (i + 1);
// }

// static int	handle_string(int i, char *str, t_data *data)
// {
// 	int		str_start_i;
// 	int		str_end_i;
// 	char	*string;

// 	str_start_i = i;
// 	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("|<>\"'", str[i]))
// 	{
// 		printf("char: %c\n", str[i]);
// 		i++;
// 	}
// 	str_end_i = i - 1;
// 	if (str_end_i >= str_start_i)
// 	{
// 		printf("reached end with char %c at index %i\n", str[str_end_i],
// 			str_end_i);
// 		printf("start index %i, end index %i, end-start+1= %i\n", str_start_i,
// 			str_end_i, str_end_i - str_start_i + 1);
// 		string = ft_substr(str, str_start_i, str_end_i - str_start_i + 1);
// 		// safe_malloc needed
// 		printf("string: %s\n\n", string);
// 		add_token(&data->tokens, create_token(TOKEN_STRING, "", NULL, NULL));
// 		free(string);
// 	}
// 	return (i);
// }

// static int	heredoc(int i, char *str, t_data *data)
// {
// 	// handle input redirection
// 	printf("found TOKEN_REDIRECT_IN at index %i\n", i);
// 	i++;
// 	if (str[i] && str[i] == '<')
// 	{
// 		i++;
// 		printf("heredoc\n");
// 	}
// 	add_token(&data->tokens, create_token(TOKEN_REDIRECT_IN, "<", NULL, NULL));
// 	return (i);
// }

// static int	append(int i, char *str, t_data *data)
// {
// 	// handle output redirection
// 	printf("found TOKEN_REDIRECT_OUT at index %i\n", i);
// 	i++;
// 	if (str[i] && str[i] == '>')
// 	{
// 		i++;
// 		printf("append\n");
// 	}
// 	add_token(&data->tokens, create_token(TOKEN_REDIRECT_OUT, ">", NULL, NULL));
// 	return (i);
// }

// static int	handle_special(int i, char *str, t_data *data)
// {
// 	if (str[i] && ft_strchr("|<>\"'", str[i]))
// 	{
// 		if (str[i] == '<')
// 			i = heredoc(i, str, data);
// 		else if (str[i] == '|')
// 			i = handle_pipe(i, data);
// 		else if (str[i] == '>')
// 			i = append(i, str, data);
// 		else if (str[i] == '\"' || str[i] == '\'')
// 			i = handle_q_string(i, str, data, str[i]);
// 	}
// 	return (i);
// }

// static char *skip_whitespace(char *str)
// {
// 	while (*str && ft_isspace(*str))
// 		str++;
// 	return (str);
// }

// int	scan(char *str, t_data *data)
// {
// 	int		i;
// 	char 	*str;

// 	i = 0;
// 	str = data->input_copy;
// 	skip_whitespace(str);
// 	while (1)
// 	{
// 		// maybe it's better to pass pointer to i but i get confused with *
// 		i = handle_string(i, str, data);
// 		i = handle_special(i, str, data);
// 		if (!str[i])
// 			break ;
// 	}
// 	return (EXIT_SUCCESS);
// }
