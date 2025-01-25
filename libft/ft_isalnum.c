/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 18:40:05 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/11 18:49:52 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int i)
{
	if ((i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z')
		|| (i >= '0' && i <= '9'))
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	src = '6';
// 	printf ("%d", ft_isalnum (src));
// 	printf ("%s", "\n");
// 	printf ("%d", isalnum (src));
// 	return (0);
// }