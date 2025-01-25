/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 15:26:56 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 13:55:07 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_set(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	first;
	size_t	last;

	first = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[first] && ft_char_in_set(s1[first], set))
		first++;
	last = ft_strlen(s1);
	if (first == last)
		return (ft_strdup(""));
	last--;
	while (last >= first && ft_char_in_set(s1[last], set))
		last--;
	return (ft_substr(s1, first, last - first + 1));
}

// int main ()
// {
// 	printf("%s\n", ft_strtrim("     3jkj3kkk!!  3 "," 3"));
// 	return (0);
// }