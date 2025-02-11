/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:38:12 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/11 15:45:47 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expanded(char *start, char *end, t_data *data)
{
	if (start == end)
		return (ft_strdup("$")); // safe malloc needed
	else if (end - start == 1 && *start == '?')
		return (ft_itoa(g_last_exit_code)); // safe malloc needed
	else
		return (find_env_var(&data->envs, ft_substr(start, 0, end - start)));
	// safe malloc needed
}

static char	*dollar_end(char *str)
{
	if (*str == '?')
		return (str + 1);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (str); // returns next char after the end of the dollar token
}

/*
Expander expands
	- $USER to username found in environment variables,
	if variable with such name is not found, it's replaced
	with nothing.
	- $? to global variable used for storing last exit code.
	- $ with nothing afterwards to $ (basically remains unchanged).

Regular bash also handles cases like $$, $0
but they are out of scope of this project.
*/

char	*expand(char *str, t_data *data)
{
	char	*res;
	char	*temp;
	char	*start;
	char	*end;

	res = ft_strdup("");
	while (*str)
	{
		temp = str;
		while (*str && *str != '$')
			str++;
		res = ft_strjoin(res, ft_substr(temp, 0, str - temp));
		// safe malloc needed
		if (*str == '$')
		{
			str++; // skipped dollar itself
			start = str;
			end = dollar_end(str);
			res = ft_strjoin(res, expanded(start, end, data));
			// safe malloc needed
			str = end;
		}
	}
	return (res);
}
