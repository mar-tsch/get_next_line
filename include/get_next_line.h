/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:38:16 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/14 16:22:27 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);

typedef struct t_file
{
	int		fd;
	char	reading_buff[BUFFER_SIZE];
	size_t	reading_size;
	size_t	reading_flow;
	char	writing_buff[BUFFER_SIZE];
	size_t	writing_size;
	size_t	writng_flow;
}	t_file;

int		cust_getc(t_file *pt_file);
t_file	*cust_open(int fd);

#endif
