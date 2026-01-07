/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatikedd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 08:30:27 by iatikedd          #+#    #+#             */
/*   Updated: 2025/11/14 08:30:39 by iatikedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*new_temp(char *temp, int index)
{
	char	*new_temp;
	size_t	t_len;
	int		i;
	int		j;

	t_len = ft_strlen(temp);
	new_temp = malloc(t_len - index);
	if (!new_temp)
	{
		free(temp);
		return (NULL);
	}
	i = 0;
	j = index + 1;
	while (temp[j])
	{
		new_temp[i] = temp[j];
		j++;
		i++;
	}
	new_temp[i] = 0;
	free(temp);
	return (new_temp);
}

static char	*new_line(char *temp, int index)
{
	char	*new;
	int		i;

	i = 0;
	if (!temp)
		return (NULL);
	new = malloc(index + 2);
	if (!new)
		return (NULL);
	while (i <= index)
	{
		new[i] = temp[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

static int	check_new_line(char *temp)
{
	int	i;

	i = 0;
	if (!temp)
		return (-1);
	while (temp[i])
	{
		if (temp[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*read_and_append(int fd, char **temp, char *buffer)
{
	int		total_bytes;
	int		save_index;
	char	*free_temp;
	char	*result;

	total_bytes = 1;
	while (total_bytes > 0)
	{
		total_bytes = read(fd, buffer, (size_t)BUFFER_SIZE);
		if (total_bytes == -1)
			return (free(*temp), *temp = NULL, NULL);
		buffer[total_bytes] = 0;
		free_temp = *temp;
		*temp = ft_strjoin(*temp, buffer);
		free(free_temp);
		if (!*temp)
			return (free(*temp), *temp = NULL, NULL);
		save_index = check_new_line(*temp);
		if (save_index != -1)
		{
			result = new_line(*temp, save_index);
			return (*temp = new_temp(*temp, save_index), result);
		}
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*temp[1024];
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(temp[fd]), temp[fd] = NULL, NULL);
	result = read_and_append(fd, &temp[fd], buffer);
	free(buffer);
	if (result)
		return (result);
	if (temp[fd])
	{
		if (temp[fd][0] == '\0')
			return (free(temp[fd]), temp[fd] = NULL, NULL);
		result = ft_strdup(temp[fd]);
		return (free(temp[fd]), temp[fd] = NULL, result);
	}
	return (NULL);
}
