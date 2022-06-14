/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 14:12:26 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/14 19:21:44 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

t_file	*cust_open(int fd)
{
	t_file	*pt_file;
	t_file	empty;

	pt_file = malloc(sizeof *pt_file);
	if (pt_file != NULL)
	{
		
		pt_file = &empty;
		pt_file->fd = fd;
	}
	return (pt_file);
}

int	cust_getc(t_file *pt_file)
{
	int	read_ok;
	char	res;
	
	if (pt_file->reading_flow >= pt_file->reading_size)
	{
		pt_file->reading_size = 0;
		pt_file->reading_flow = 0;
		read_ok = read(pt_file->fd, pt_file->reading_buff, BUFFER_SIZE);
		if (read_ok <= 0)
			return (-1);
		pt_file->reading_size = read_ok;
	}
	res = pt_file->reading_buff[pt_file->reading_flow];
	pt_file->reading_flow++;
	return (res);
}
/*
char	append_c()
{
	;
}

char	*final_line()
{
	;
}*/


