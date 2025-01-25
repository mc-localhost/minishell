/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:31:23 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 13:36:51 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*udst;
	char		*usrc;

	if (!dst && !src)
		return (dst);
	if (dst < src)
		return (ft_memcpy (dst, src, len));
	udst = (char *)dst;
	usrc = (char *)src;
	while (len > 0)
	{
		len--;
		udst[len] = usrc[len];
	}
	return (dst);
}

// int main() 
// { 
// 	char csrc[100] = "Geeksfor"; 
// 	ft_memmove(csrc+5, csrc, strlen(csrc)+1); 
// 	printf("%s", csrc); 
// 	return 0; 
// } 