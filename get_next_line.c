/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhlel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 13:45:11 by abouhlel          #+#    #+#             */
/*   Updated: 2021/07/05 13:45:17 by abouhlel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	find_line(char **sauvgard, char **line, int a)
{
	char	*tmp;
	int	len;

	(*sauvgard)[a] = '\0';
	*line = ft_strdup(*sauvgard);
	len = ft_strlen(*sauvgard + a + 1);
	if (len == 0)
	{
		free(*sauvgard);
		*sauvgard = 0;
		return (1);
	}
	tmp = ft_strdup(*sauvgard + a + 1);
	free(*sauvgard);
	*sauvgard = tmp;
	return (1);
}

int	check_line(char **sauvgard, char **line, int read_bytes)
{
	int	i;

	if (read_bytes < 0)
		return (-1);
	i = count_newline(*sauvgard);
	if ((*sauvgard) && i >= 0)
	{
		return (find_line(sauvgard, line, i));
	}
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
	static char	*sauvgard;
	int		read_bytes;
	int		i;
	
	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	read_bytes = BUFFER_SIZE;
	while (read_bytes == BUFFER_SIZE)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes < 0)
			return (-1);
		buff[read_bytes] = '\0';
		sauvgard = ft_strjoin(sauvgard, buff);
		i = count_newline(sauvgard);
		if (i >= 0)
		{
			return (find_line(&sauvgard, line, i));
		}	
	}
	return (check_line(&sauvgard, line, read_bytes));
}
