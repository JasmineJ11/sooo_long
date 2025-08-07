/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 11:37:32 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/15 11:37:33 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*p;
	unsigned char	v;
	size_t			i;

	p = (unsigned char *)ptr;
	v = (unsigned char)value;
	i = 0;
	while (i < num)
	{
		p[i] = v;
		i++;
	}
	return (ptr);
}
