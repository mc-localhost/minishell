/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:39:22 by vvasiuko          #+#    #+#             */
/*   Updated: 2024/10/15 13:18:15 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*dest;

	dest = (void *) malloc (count * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, count * size);
	return (dest);
}

// int main() {
//    int n = 5;
//    int *array;
//    // use calloc function to allocate the memory
//    array = (int*)ft_calloc(n, sizeof(int));
//    if (array == NULL) {
//       fprintf(stderr, "Memory allocation failed!\n");
//       return 1;
//    }
//    //Display the array value
//    printf("Array elements after calloc: ");
//    for (int i = 0; i < n; i++) {
//       printf("%d ", array[i]);
//    }
//    printf("\n");
//    //free the allocated memory
//    free(array);
//    return 0;
// }