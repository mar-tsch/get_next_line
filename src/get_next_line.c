/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:10:39 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/17 12:13:59 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

char    *get_next_line(int fd)
{
        static t_marie  *stored_chars;
        int                             read_ok;
        char                    *line;

        if (fd < 0 || BUFFER_SIZE < 0 || read(fd, &line, 0) < 0)
                return (NULL);
        read_ok = 1;
        line = NULL;
        stored_chars = NULL;
        read_store(&stored_chars, &read_ok);
        if (stored_chars == NULL)
                return (NULL);
        put_line(stored_chars, &line);
        clean_store(&stored_chars);
        return (line);
}

void    read_store(t_marie **stored_chars, int *p_read_ok)
{
        char    *buff;

        while (!new_line(*stored_chars) && *p_read_ok != 0)
        {
                buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
                if (!buff)
                        return (NULL);
                *p_read_ok = (int)read(fd, buff, BUFFER_SIZE);
                if (*stored_chars == NULL && *p_read_ok || *p_read_ok == -1)
                {
                        free(buff);
                        return ;
                }
                buff[*p_read_ok] = '\0';
                store_the_char(stored_chars, buff, *p_read_ok);
                free(buff);
        }
}

void    store_the_char(t_marie **stored_chars, char *buff, int *read_ok)
{
        int                     x;
        t_marie         *pos;
        t_marie         *new;

        new = malloc(sizeof(t_marie));
        if (!new)
                return (NULL);
        new->next = NULL;
        new->content = malloc(sizeof(char) * (read_ok + 1));
        if (!new->content)
                return (NULL);
        x = 0;
        while (buff[x++] && x < read_ok)
                new->content[x] = buff[x];
        new->content[x] = '\0';
        if (*stored_chars == NULL)
                *stored_chars = new;
        pos = go_last(*stored_chars);
        pos->next = new;
}

void    put_line(t_marie *stored_chars, char **line)
{
        int     x;
        int     y;

        if (!stored_chars)
                return (NULL);
        create_line(line, stored_chars);
        if (!*line)
                return (NULL);
        while (stored_chars)
        {
                x = 0;
                while (stored_chars->content[x])
                {
                        if (stored_chars[x] == '\n')
                        {
                                *line[y++] = stored_chars[x++];
                                break ;
                        }
                        *line[y++] = stored_chars[x++];
                }
                stored_chars = stored_chars->next;
        }
        *line[y] = '\0';
}

void    clean_store(t_marie *stored_chars)
{
        int             x;
        int             y;
        t_marie *last;
        t_marie *clean;

        clean = malloc(sizeof(t_marie));
        if (!stored_chars || !clean)
                return (NULL);
        clean->next = NULL;
        last = go_last(*stored_chars);
        x = 0;
        while (last->content[x] && last->content[x] != '\n')
                x++;
        if (last->content[x] && last->content[x] == '\n')
                x++;
        clean->content = malloc(sizeof(char) + ((get_len(last->content) - 1) + 1));
        if (!clean)
                return (NULL);
        y = 0;
        while (last->content[x])
                clean->content[y++] = last->content[x++];
        clean->content[y] = '\0';
        free_store(*stored_chars);
        *stored_chars = clean;
}

