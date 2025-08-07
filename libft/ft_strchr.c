/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:42:09 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/17 09:42:11 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	i = 0;
	while (str[i])
	{
		if (str[i] == chr)
		{
			return ((char *)str + i);
		}
		i++;
	}
	if (chr == '\0')
	{
		return ((char *)str + i);
	}
	return (NULL);
}
