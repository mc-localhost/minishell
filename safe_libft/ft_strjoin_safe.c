/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:41:00 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 18:32:08 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_safe(char const *s1, char const *s2)
{
	char	*res;
	char	*first;
	size_t	size;

	if (!s1 && !s2)
		return (ft_strdup_safe(""));
	if (!s1)
		return (ft_strdup_safe(s2));
	if (!s2)
		return (ft_strdup_safe(s1));
	size = ft_strlen(s1) + ft_strlen(s2);
	res = safe_malloc((size + 1) * sizeof(char));
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
