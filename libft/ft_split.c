/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiawli <jiawli@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:44:56 by jiawli            #+#    #+#             */
/*   Updated: 2025/04/21 16:44:58 by jiawli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	word_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_word(const char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			s += word_len(s, c);
		}
		else
		{
			s++;
		}
	}
	return (count);
}

static void	*free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static char	**allocate_array(char const *s, char c, char **array)
{
	int	len;
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = word_len(s, c);
			array[i] = ft_substr(s, 0, len);
			if (!array[i])
				return (free_array(array));
			s += len;
			i++;
		}
		else
			s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (s == NULL)
		return (NULL);
	array = malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (array == NULL)
		return (NULL);
	return (allocate_array(s, c, array));
}
