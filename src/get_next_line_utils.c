/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:12:26 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/15 19:18:43 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int     new_line(t_marie *stored_chars)
{
        int             x;
        t_marie *pos;

        if (stored_chars == NULL)
                return (0);
        pos = go_last(stored_chars);
        x = 0;
        while (pos->content[x++])
        {
                if (pos->content[x] == '\n')
                        return (1);
        }
        return (0);
}
t_marie *go_last(t_marie *stored_chars)
{
        t_marie *pos;

        pos = stored_chars;
        while (pos && pos->next)
                pos = pos->next;
        return (pos);
}

void    create_line(char **line, t_marie *stored_chars)
{
        int     x;
        int     size;

        size = 0;
        while (stored_chars)
        {
                x = 0;
                while (stored_chars->content[x])
                {
                        if (stored_chars->content[x] == '\n')
                        {
                                size++;
                                break;
                        }
                        size++;
                        x++;
                }
                stored_chars = stored_chars->next;
        }
        *line = malloc(sizeof(char) * (size + 1));
}

int     get_len(char *s)
{
        int     x;

        while (s)
                x++;
        return (x);
}

void    free_store(t_marie *stored_chars)
{
        t_marie *pos;
        t_marie *next;

        pos = stored_chars;
        while (pos)
        {
                free(pos->content);
                next = pos->next;
                free(pos);
                pos = next;
        }
}

