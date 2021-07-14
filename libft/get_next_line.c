/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchin <dchin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 17:32:18 by dchin             #+#    #+#             */
/*   Updated: 2020/11/27 18:01:36 by dchin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		check_readed(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*set_readed(char *readed, char *buff)
{
	char	*str;

	if (readed)
	{
		str = ft_strjoin(readed, buff);
		free(readed);
	}
	else
		str = ft_strdup(buff);
	return (str);
}

char	*get_line(char *readed)
{
	char	*ptr_to_n;
	char	*temp;
	char	*str;

	if (!readed)
		return (0);
	temp = ft_strdup(readed);
	if ((ptr_to_n = ft_strchr(temp, '\n')))
		*ptr_to_n = '\0';
	str = ft_strdup(temp);
	free(temp);
	return (str);
}

char	*get_readed(char *readed, int *rd)
{
	char	*ptr_to_n;
	char	*str;

	if (*rd == 0)
	{
		free(readed);
		return (0);
	}
	if (!readed)
		return (0);
	ptr_to_n = ft_strchr(readed, '\n');
	str = ft_strdup((ptr_to_n + 1));
	free(readed);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	int				size_rd;
	char			*buffer;
	static char		*readed;

	size_rd = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL)
		return (-1);
	if (!(buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (size_rd != 0 && !check_readed(readed))
	{
		if ((size_rd = read(fd, buffer, BUFFER_SIZE)) == -1)
		{
			free(buffer);
			return (-1);
		}
		buffer[size_rd] = '\0';
		readed = set_readed(readed, buffer);
	}
	free(buffer);
	*line = get_line(readed);
	readed = get_readed(readed, &size_rd);
	return (size_rd > 0);
}
