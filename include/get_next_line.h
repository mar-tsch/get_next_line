/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtritsch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:38:16 by mtritsch          #+#    #+#             */
/*   Updated: 2022/06/17 15:05:06 by mtritsch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);

typedef struct s_marie
{
	char			*content;
	struct s_marie	*next;
}	t_marie;

void	read_store(int fd, t_marie **stored_chars);
void	store_the_char(t_marie **stored_chars, char *buff, int read_ok);
void	put_line(t_marie *stored_chars, char **line);
void	clean_store(t_marie **stored_chars);
int		new_line(t_marie *stored_chars);
int		get_len(char *s);
t_marie	*go_last(t_marie *stored_chars);
void	create_line(char **line, t_marie *stored_chars);
void	free_store(t_marie *stored_chars);
#endif
