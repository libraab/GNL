/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:45:50 by abouhlel          #+#    #+#             */
/*   Updated: 2021/07/05 13:45:53 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	count_newline(char *sauvgard)
{
	int	i;

	i = 0;
	while (sauvgard[i++])
	{
		if (sauvgard[i] == '\n')
			return (i);
	}
	return (-1);
}

int	find_newline(char **sauvgard, char **line, int i)
{
	char	*tmp;
	int	len;

	(*sauvgard)[i] = '\0';
	*line = ft_strdup(*sauvgard);
	len = ft_strlen(*sauvgard + i + 1);
	if (len == 0)
	{
		free(*sauvgard);
		*sauvgard = 0;
		return (1);
	}
	tmp = ft_strdup(*sauvgard + i + 1);
	free (*sauvgard);
	*sauvgard = tmp;
	return (1);
}

int	check_line(char **sauvgard, char **line, int read_bytes)
{
	int	i;

	if (read_bytes < 0)
		return (-1);
	i = count_newline(*sauvgard);
	if (*sauvgard && i >= 0)
		return (find_newline(sauvgard, line, i));
	else if (*sauvgard)
	{
		*line = *sauvgard;
		*sauvgard = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char            buff[BUFFER_SIZE + 1];
	static char	*sauvgard[256];
	int		read_bytes;
	int		i;

	if ((fd < 0) || (fd > 256) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	read_bytes = read(fd, buff, BUFFER_SIZE);
	while (read_bytes > 0)
	{
		buff[read_bytes] = '\0';
		sauvgard[fd] = ft_strjoin(sauvgard[fd], buff);
		i = count_newline(sauvgard[fd]);
		if (i >= 0)
			return (find_newline(&sauvgard[fd], line, i));
	}
	return (check_line(&sauvgard[fd], line, read_bytes));
}
