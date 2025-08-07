/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:49:16 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/23 14:49:18 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long nbr)
{
	int	count;

	count = 0;
	if (nbr <= 0)
		count++;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;
	long	nbr;

	len = int_len(n);
	nbr = n;
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	if (nbr == 0)
		result[0] = '0';
	if (nbr < 0)
	{
		nbr = -nbr;
		result[0] = '-';
	}
	while (nbr > 0)
	{
		len--;
		result[len] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (result);
}
