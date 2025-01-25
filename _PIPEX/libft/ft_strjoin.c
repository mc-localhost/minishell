/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:41:00 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/15 11:58:40 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*first;
	size_t	size;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	res = malloc((size + 1) * sizeof(char));
	if (!res)
		return (NULL);
	first = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (first);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strjoin("lalala", "second lalala"));
// 	printf("%d\n", ft_strlen("lalala"));
// 	return (0);
// }
