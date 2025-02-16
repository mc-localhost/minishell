/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:07:31 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 18:08:39 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*expanded(char *start, char *end, t_data *data)
{
	if (start == end) // and if end + 1 = ' ' or '\0' - FIX!
		return (ft_strdup_safe("$"));
	else if (end - start == 1 && *start == '?')
		return (ft_itoa_safe(g_last_exit_code));
	else
		return (find_env_var(&data->envs, ft_substr_safe(start, 0, end
					- start)));
}

static char	*dollar_end(char *str)
{
	if (*str == '?')
		return (str + 1);
	while (*str && (ft_isalnum(*str) || *str == '_'))
		str++;
	return (str);
}

char	*expand(char *str, t_data *data)
{
	char	*res;
	char	*temp;
	char	*start;
	char	*end;

	res = ft_strdup_safe("");
	while (*str)
	{
		temp = str;
		while (*str && *str != '$')
			str++;
		res = ft_strjoin_safe(res, ft_substr_safe(temp, 0, str - temp));
		if (*str == '$')
		{
			str++;
			start = str;
			end = dollar_end(str);
			res = ft_strjoin_safe(res, expanded(start, end, data));
			str = end;
		}
	}
	return (res);
}
