/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:40:35 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/13 10:40:51 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && i + j < len
			&& haystack[i + j] == needle[j])
			j++;
		if (!needle[j])
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char string1[]
// = "needle here haystack contains and not here (needle)";
// 	const char string2[] = "needle";
// 	printf("%s", ft_strnstr(string1, string2, 30));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strnstr(string1, string2, 30));
// 	printf("%s","\n");
// 	const char string3[]
// = "Haystack doesn't contain anything but contains need";
// 	const char string4[] = "needle";
// 	printf("%s", ft_strnstr(string3, string4, 100));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strnstr(string3, string4, 100));
// 	printf("%s","\n");
// 	const char string5[] = "Empty needle";
// 	const char string6[] = "";
// 	printf("%s", ft_strnstr(string5, string6, 10));
// 	printf("%s","\n And the computer says: \n");
// 	printf("%s", strnstr(string5, string6, 10));
// 	return (0);
// }