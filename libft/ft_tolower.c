/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:18:45 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/12 13:50:14 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int i)
{
	if (i >= 'A' && i <= 'Z')
		return (i += 32);
	return (i);
}

// int main(void)
// {
// 	char	src = 'E';

// 	printf ("%d", ft_tolower (src));
// 	printf ("%s", "\n");
// 	printf ("%d", tolower (src));
// 	return (0);
// }