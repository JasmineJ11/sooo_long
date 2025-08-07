/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 10:53:44 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/20 10:53:47 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*dest;

	s_len = 0;
	if (s == NULL)
		return (NULL);
	while (s[s_len])
	{
		s_len++;
	}
	if (start > s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, s + (size_t)start, len);
	dest[len] = '\0';
	return (dest);
}
