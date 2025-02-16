/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_stderr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 14:04:46 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/16 15:15:37 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_stderr(char *s)
{
	if (!s)
		return ;
	write(2, s, ft_strlen(s));
}

void	ft_putchar_stderr(char c)
{
	write (2, &c, 1);
}
