/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:59:55 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/03/07 12:55:53 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_n_flag(t_token *token)
{
	char	*str;
	int		start;

	start = 0;
	while (start < token->args_count)
	{
		if (!ft_strncmp(token->args[start], "-n", 2))
		{
			str = token->args[start] + 2;
			while (*str)
			{
				if (*str != 'n')
					return (start);
				str++;
			}
		}
		else
			break ;
		start++;
	}
	return (start);
}

// in case if we want to use esc chart
char	*esc_chart(char	*str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	s = malloc(ft_strlen(str) * sizeof(char));
	if (!s)
		return (str);
	while (str[i])
	{
		if (str[i + 1] && str[i] == '\\' && str[i + 1] == '\\')
		{
			s[j++] = '\\';
			i += 2;
		}
		if (str[i] == '\\')
			i++;
		s[j++] = str[i];
		i++;
	}
	s[j] = '\0';
	return (s);
}

void	echo_out(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '\\')
				printf("\\");
			else if (str[i + 1] == 'n')
				printf("\\n");
			else if (str[i + 1] == 't')
				printf("\\t");
			i++;
		}
		else
			printf("%c", str[i]);
		i++;
	}
	if (c != '0')
		printf("%c", c);
}

static int	echo_n(t_token *token, int start)
{
	int	i;

	i = start;
	while (i < token->args_count - 1)
	{
		echo_out(token->args[i], ' ');
		i++;
	}
	if (token->args[i])
		echo_out(token->args[i], '0');
	return (0);
}

int	echo(t_token *token)
{
	int	i;
	int	start;

	if (token->args_count > 0)
	{
		start = check_n_flag(token);
		if (start > 0)
			return (echo_n(token, start));
		else
		{
			i = 0;
			while (i < token->args_count - 1)
			{
				echo_out(token->args[i], ' ');
				i++;
			}
			echo_out(token->args[i], '\n');
		}
	}
	else
		printf("\n");
	return (0);
}
