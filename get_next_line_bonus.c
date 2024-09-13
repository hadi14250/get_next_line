/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakaddou <hakaddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 02:05:49 by hakaddou          #+#    #+#             */
/*   Updated: 2022/03/27 02:12:40 by hakaddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_trim_stat(char *str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	tmp = malloc((ft_strlen(str) - i + 1));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	i++;
	j = 0;
	while (str[i])
		tmp[j++] = str[i++];
	tmp[j] = '\0';
	free(str);
	return (tmp);
}

char	*ft_trim_line(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	tmp = malloc (i + 2);
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_get_line(char *str, int fd)
{
	char	*buf;
	char	*temp;
	int		count;

	count = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	while (!ft_strchr (str, '\n') && count != 0)
	{
		count = read (fd, buf, BUFFER_SIZE);
		if (count == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[count] = '\0';
		temp = ft_strjoin (str, buf);
		free(str);
		str = temp;
	}
	free (buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stat[1024];
	char		*next_line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (0);
	stat[fd] = ft_get_line (stat[fd], fd);
	if (!stat[fd])
		return (0);
	else if (!stat[fd][0])
	{
		free(stat[fd]);
		return (0);
	}
	next_line = ft_trim_line (stat[fd]);
	stat[fd] = ft_trim_stat(stat[fd]);
	return (next_line);
}
