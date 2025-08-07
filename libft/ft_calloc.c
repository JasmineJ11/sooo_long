/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:12:25 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/19 17:12:26 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	size_t			total;
	unsigned char	*mem;

	total = num * size;
	if (num > 0 && size > 0 && total / num != size)
		return (NULL);
	mem = malloc(total);
	if (mem != NULL)
	{
		ft_memset(mem, 0, total);
	}
	return (mem);
}
