/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:26:35 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/01/25 13:21:46 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
			&& *(unsigned char *)(s1 + i) != '\0'
			&& *(unsigned char *)(s2 + i) != '\0')
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
