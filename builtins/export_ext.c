/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:15:49 by aelaaser          #+#    #+#             */
/*   Updated: 2025/02/27 09:44:51 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_export_error(char *identifier, char *name)
{
	int	i;

	i = 0;
	while (identifier[i])
	{
		if (identifier[i] == '(' || identifier[i] == ')')
		{
			ft_putstr_stderr("syntax error near unexpected token `");
			write(2, &identifier[i], 1);
			ft_putstr_stderr("'\n");
			return (258);
		}
		i++;
	}
	ft_putstr_stderr(name);
	ft_putstr_stderr(": `");
	ft_putstr_stderr(identifier);
	ft_putstr_stderr("': not a valid identifier\n");
	if (ft_strchr(identifier, ';'))
		return (127);
	if (identifier[0] == '-')
		return (2);
	return (1);
}

int	is_valid_identifier(const char *str)
{
	int	i;

	if (str == NULL || str[0] == '\0')
		return (0);
	if (!(ft_isalpha(str[0]) || str[0] == '_'))
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
