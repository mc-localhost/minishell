/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 16:26:35 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/11/15 11:58:45 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((*(unsigned char *)(s1 + i) == *(unsigned char *)(s2 + i))
			&& i < n - 1 && *(unsigned char *)(s1 + i) != '\0'
			&& *(unsigned char *)(s2 + i) != '\0')
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
// int main(void)
// {
// 	char string1[] = "I hate this";
// 	char string2[] = "I hate this task";
// 	printf("%d", ft_strncmp(string1, string2, 50));
// 	printf("%s","\n");
// 	printf("%d", strncmp(string1, string2, 50));
// 	return (0);
// }