/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpan <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:58:50 by lpan              #+#    #+#             */
/*   Updated: 2018/11/23 13:20:36 by lpan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_new_line(char **str, char **line)
{
	int				i;
	char			*temp;

	i = 0;
	temp = *str;
	while (temp[i] != '\n')
	{
		if (temp[i] == '\0')
			return (0);
		i++;
	}
	temp[i] = '\0';
	*line = ft_strndup(*str, i);
	*str = NULL;
	free(temp);
	return (1);
}

static int		read_file(const int fd, char *buff, char **str, char **line)
{
	int				ret;
	char			*temp;

	ret = 0;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (*str)
		{
			temp = *str;
			*str = ft_strjoin(temp, buff);
			free(temp);
		}
		else
			*str = ft_strdup(buff);
		if (check_new_line(str, line))
			return (1);
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[1024];
	char			*buff;
	int				ret;

	ret = 0;
	if (fd < 0 || !(buff = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	ret = read_file(fd, buff, &str[fd], line);
	free(buff);
	if (!str[fd])
		return (ret);
	*line = str[fd];
	str[fd] = NULL;
	ret = 1;
	return (ret);
}
