/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xeherzi <xeherzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:07:22 by xeherzi           #+#    #+#             */
/*   Updated: 2023/01/19 08:44:54 by xeherzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_find_str(char	*s)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	str = malloc(sizeof(char) * (ft_find_nl(s) + 2));
	if (!str)
		return (NULL);
	i = -1;
	while (++i <= ft_find_nl(s))
		str[i] = s[i];
	str[i] = '\0';
	free(s);
	return (str);
}

char	*ft_line(int fd, char *s)
{
	char	*buf;
	int		res;

	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	res = 1;
	while (res > 0)
	{
		res = read(fd, buf, BUFFER_SIZE);
		buf[res] = '\0';
		if (!s)
			s = ft_strdup(buf);
		else
			s = ft_strjoin(s, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (s);
}

int	ft_find_nl(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*stash;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	else
	{
		line = ft_line(fd, stash);
		stash = ft_substr(line, ft_find_nl(line) + 1, \
		ft_strlen(line) - ft_find_nl(line) - 1);
		line = ft_find_str(line);
		if (stash && !stash[0] && !line[0])
		{
			free(line);
			free(stash);
			return (NULL);
		}
	}
	return (line);
}
