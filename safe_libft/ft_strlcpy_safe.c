/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:12:49 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:32:24 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_strlcpy_safe(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (*(src + src_len) != '\0' && dstsize > 1)
	{
		*(dst + src_len) = *(src + src_len);
		dstsize--;
		src_len++;
	}
	*(dst + src_len) = '\0';
	while (*(src + src_len) != '\0')
		src_len++;
	return (src_len);
}

// int	main(void)
// {
// 	char	src[] = "Hello world!";
// 	char	dest[20];
// 	char	src2[] = "Hello world!";
// 	char	dest2[20];

// 	printf ("%zu\n", ft_strlcpy(dest, src, 0));
// 	printf ("%zu", strlcpy(dest2, src2, 0));
// 	return (0);
// }