/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:38:12 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/31 15:34:23 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


const char *expand(const char *str, t_data *data)
{
	const char	*res;
	char	*till_dollar;
	char	*dollar;
	int till_dollar_len;
	int	i;

	i = 0;
	res = str;
	dollar = ft_strchr(str, '$');
	if (dollar)
	{
		printf("\n$ FOUND\n");
		till_dollar_len = dollar - str;
		printf("till_dolar_len: %i\n", till_dollar_len);
		till_dollar = safe_malloc(till_dollar_len + 1);
		ft_strlcpy(till_dollar, str, till_dollar_len + 1);
		printf("till_dollar: %s\n", till_dollar);
		i = till_dollar_len + 1;
		if (str[i] && str[i] == '?')
		{
			printf("replacing with exit code");
			res = ft_strjoin(till_dollar, ft_itoa(g_last_exit_code)); //safe_malloc needed
			printf("after joining before dollar with expansion: %s\n", res);
			res = ft_strjoin(res, &str[i + 1]);
			printf("res after second join: %s\n", res);
			expand(res, data);
		}
		else if (str[i] && (ft_isspace(str[i]) || ft_strchr("$|<>\"'", str[i])))
		{
			printf("just leaving it be\n");
			//maybe replace it with " and replace back at the very end?
			expand(res, data);
		}
		else
		{
			printf("starting from index %i\n", i);
			while (str[i] && !ft_isspace(str[i]) && !ft_strchr("$|<>\"'", str[i]))
				i++;
			printf("dollar part stops at index %i\n", i);
			printf("and has length of %i\n", i - till_dollar_len - 1);
			dollar = safe_malloc(i - till_dollar_len);
			ft_strlcpy(dollar, &str[till_dollar_len + 1], i - till_dollar_len);
			printf("will be attempting to find \"%s\" in env vars...\n", dollar);
			dollar = find_env_var(&data->envs, dollar);
			if (dollar)
			{
				printf("found in vars: %s\n", dollar);
				printf("len of expansion is %i\n", (int)ft_strlen(dollar));
				res = ft_strjoin(till_dollar, dollar); //safe_malloc needed
				printf("after joining before dollar with expansion: %s\n", res);
				res = ft_strjoin(res, &str[i]);
				printf("res after second join: %s\n", res);
			}
			else
			{
				printf("couldn't find replacement in env vars\n");
				if (str[i])
					res = ft_strjoin(till_dollar, &str[i]);
				else
					res = till_dollar;
			}
		}
		printf("result: %s\n", res);
		expand(res, data);
	}
	return (res);
}
