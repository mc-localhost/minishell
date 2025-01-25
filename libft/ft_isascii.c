/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/10 18:40:52 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int i)
{
	if (i >= 0 && i <= 127)
		return (1);
	else
		return (0);
}

// int main(void)
// {
// 	char	src = ' ';

// 	printf ("%d", ft_isascii (src));
// 	printf ("%s", "\n");
// 	printf ("%d", isascii (src));
// 	return (0);
// }