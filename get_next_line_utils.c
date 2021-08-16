/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwoo <jwoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:59:13 by jwoo              #+#    #+#             */
/*   Updated: 2021/01/21 11:32:10 by jwoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*ft_strdup(char *s1)
{
	char	*str;
	size_t	count;
	size_t	index;

	if (s1 == NULL)
		return (NULL);
	count = ft_strlen(s1);
	str = malloc(sizeof(char) * (count + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < count)
	{
		str[index] = s1[index];
		index++;
	}
	str[index] = 0;
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	index;
	size_t	i;

	if (s2 == 0)
		return (0);
	len1 = s1 ? ft_strlen(s1) : 0;
	len2 = ft_strlen(s2);
	if ((str = (char *)malloc(sizeof(char) * (len1 + len2 + 1))) == 0)
		return (0);
	index = 0;
	i = 0;
	while (i < len1)
		str[index++] = s1[i++];
	i = 0;
	while (i < len2)
		str[index++] = s2[i++];
	str[index] = '\0';
	return (str);
}
