/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:58:53 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/21 11:24:08 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		find_n(char *str)
{
	int	len;
	int	point;

	if (str == 0)
		return (-42);
	len = ft_strlen(str);
	point = -1;
	while (++point < len)
		if (str[point] == '\n')
			return (point);
	return (-1);
}

char	*split_n(char *s, int point, int x)
{
	char	*str;
	int		s_len;
	int		len;
	int		i;

	s_len = s ? ft_strlen(s) : 0;
	len = x == 0 ? point : s_len - point - 1;
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	str[len] = '\0';
	i = -1;
	if (x == 0)
		while (++i < len)
			str[i] = s[i];
	else
		while (++i < len)
			str[i] = s[point + 1 + i];
	return (str);
}

int		free_gnl(char **gnl, char **buf, int ret)
{
	if (ret <= 0)
	{
		free(*gnl);
		*gnl = 0;
	}
	free(*buf);
	*buf = 0;
	return (ret);
}

int		ret_gnl(char **line, char **gnl, char **buf, int y)
{
	int		point;
	char	*temp;

	if (y == 1)
	{
		point = find_n(*gnl);
		temp = *gnl;
		if ((*line = split_n(temp, point, 0)) == 0)
			return (free_gnl(gnl, buf, -1));
		if ((*gnl = split_n(temp, point, 1)) == 0)
			return (free_gnl(gnl, buf, -1));
		free(temp);
		temp = 0;
		return (free_gnl(gnl, buf, 1));
	}
	else
	{
		*line = y == 0 ? ft_strdup(*gnl) : ft_strdup("");
		if (*line == 0)
			return (free_gnl(gnl, buf, -1));
		return (free_gnl(gnl, buf, 0));
	}
}

int		get_next_line(int fd, char **line)
{
	static char	*gnl[OPEN_MAX];
	char		*buf;
	char		*temp;
	int			rs;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || line == 0)
		return (-1);
	if ((buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == 0)
		return (-1);
	while ((rs = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		if (buf != 0)
			buf[rs] = '\0';
		temp = gnl[fd];
		gnl[fd] = ft_strjoin(temp, buf);
		free(temp);
		temp = 0;
		if (rs == 0 && gnl[fd] == 0)
			return (ret_gnl(line, &gnl[fd], &buf, -1));
		if (find_n(gnl[fd]) >= 0)
			return (ret_gnl(line, &gnl[fd], &buf, 1));
		if (rs < BUFFER_SIZE && find_n(gnl[fd]) == -1)
			return (ret_gnl(line, &gnl[fd], &buf, 0));
	}
	return (free_gnl(&gnl[fd], &buf, -1));
}
