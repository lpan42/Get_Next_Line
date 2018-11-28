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
	if (!(*line = ft_strndup(*str, i)))
		return (-1);
	if (!(*str = ft_strdup(&temp[i + 1])))
		return (-1);
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
			if (!(*str = ft_strjoin(temp, buff)))
				return (-1);
			free(temp);
		}
		else if (!(*str = ft_strdup(buff)))
			return (-1);
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
	if (str[fd])
	{
		if(check_new_line(&str[fd], line))
			return (1);
	}
	ret = read_file(fd, buff, &str[fd], line);
	free(buff);
	if (ret == 1 || !str[fd])
		return (ret);
	if (!ret && *line)
	{
		*line = str[fd];
		str[fd] = NULL;
	}
	return (ret);
}
