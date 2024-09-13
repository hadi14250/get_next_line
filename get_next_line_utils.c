/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:07:15 by hakaddou          #+#    #+#             */
/*   Updated: 2022/03/27 01:54:16 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (0);
	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!len1 && !len2)
		return (0);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (0);
	str[0] = '\0';
	while (i < len1 + len2)
	{
		if (i < len1)
			str[i] = s1[i];
		if (i >= len1)
			str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}
