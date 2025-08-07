/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 08:03:36 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/16 08:03:37 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	v;
	size_t			i;

	p = (unsigned char *)ptr;
	v = (unsigned char)value;
	i = 0;
	while (i < num)
	{
		if (p[i] == v)
		{
			return (p + i);
		}
		i++;
	}
	return (NULL);
}
