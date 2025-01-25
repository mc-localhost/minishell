/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:47:08 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 12:17:12 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;

	src_len = 0;
	dst_len = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	while (src[src_len] && (dstsize - dst_len - src_len) > 1)
	{
		dst[dst_len + src_len] = src[src_len];
		src_len++;
	}
	if (dst_len < dstsize)
		dst[dst_len + src_len] = '\0';
	while (src[src_len])
		src_len++;
	return (src_len + dst_len);
}

// int	main(void)
// {
// 	char	src[] = "Hello world!";
// 	char	dest[20] = "Hello";

// 	printf ("%zu\n", ft_strlcat(dest, src, 10));
// 	// printf ("%zu", strlcat(dest, src, 10));
// 	return (0);
// }