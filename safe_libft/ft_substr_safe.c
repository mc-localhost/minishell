/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:54:48 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:32:12 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_nuldest(void)
{
	char	*dest;

	dest = safe_malloc(sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

char	*ft_substr_safe(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	count;
	char	*dest;

	count = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen (s);
	if (s_len > start)
	{
		if (len + start > s_len)
			len = s_len - start;
		dest = safe_malloc((len + 1) * sizeof(char));
		if (!dest)
			return (NULL);
		dest[len] = '\0';
		while (count < len)
		{
			dest[count] = s[start + count];
			count++;
		}
	}
	else
		dest = ft_nuldest();
	return (dest);
}

// int	main(void)
// {
// 	char	src[] = "Hello world!";
// 	printf ("%s\n", ft_substr(src, 1, 5));
// 	return (0);
// }