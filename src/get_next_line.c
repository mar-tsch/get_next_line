/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:10:39 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/17 18:32:21 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char	*get_next_line(int fd)
{
	static t_marie	*stored_chars;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_store(fd, &stored_chars);
	if (stored_chars == NULL)
		return (NULL);
	put_line(stored_chars, &line);
	clean_store(&stored_chars);
	if (*line == '\0')
	{
		free_store(stored_chars);
		stored_chars = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_store(int fd, t_marie **stored_chars)
{
	int		read_ok;
	char	*buff;

        read_ok = 1;
	while (!new_line(*stored_chars) && read_ok != 0)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buff == NULL)
			return ;
		read_ok = (int)read(fd, buff, BUFFER_SIZE);
		if ((*stored_chars == NULL && read_ok == 0) || read_ok == -1)
		{
			free(buff);
			return ;
		}
		buff[read_ok] = '\0';
		store_the_char(stored_chars, buff, read_ok);
		free(buff);
	}
}

void	store_the_char(t_marie **stored_chars, char *buff, int read_ok)
{
	int			x;
	t_marie		*pos;
	t_marie		*new;

	new = malloc(sizeof(t_marie));
	if (new == NULL)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (read_ok + 1));
	if (new->content == NULL)
		return ;
	x = 0;
	while (buff[x] && x < read_ok)
        {
		new->content[x] = buff[x];
                x++;
        }
        new->content[x] = '\0';
	if (*stored_chars == NULL)
	{
		*stored_chars = new;
                return ;
	}
	pos = go_last(*stored_chars);
	pos->next = new;
}

void	put_line(t_marie *stored_chars, char **line)
{
	int	x;
	int	y;

	if (stored_chars == NULL)
		return ;
	create_line(line, stored_chars);
	if (*line == NULL)
		return ;
	y = 0;
	while (stored_chars)
	{
		x = 0;
		while (stored_chars->content[x])
		{
			if (stored_chars->content[x] == '\n')
			{
				(*line)[y++] = stored_chars->content[x];
				break ;
			}
			(*line)[y++] = stored_chars->content[x++];
		}
		stored_chars = stored_chars->next;
	}
	(*line)[y] = '\0';
}

void	clean_store(t_marie **stored_chars)
{
	int		x;
	int		y;
	t_marie	*last;
	t_marie	*clean;

	clean = malloc(sizeof(t_marie));
	if (stored_chars == NULL || clean == NULL)
		return ;
	clean->next = NULL;
	last = go_last(*stored_chars);
	x = 0;
	while (last->content[x] && last->content[x] != '\n')
		x++;
	if (last->content && last->content[x] == '\n')
		x++;
	clean->content = malloc(sizeof(char) * ((get_len(last->content) - x) + 1));
	if (clean->content == NULL)
		return ;
	y = 0;
	while (last->content[x])
		clean->content[y++] = last->content[x++];
	clean->content[y] = '\0';
	free_store(*stored_chars);
	*stored_chars = clean;
}
