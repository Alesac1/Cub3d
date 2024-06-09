/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:15:11 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/08 22:47:40 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_gnl_strdup(const char *s1);
char	*ft_gnl_strjoin(char *s1, char *s2);
int		ft_search(const char *s, char c);
char	*ft_gnl_substr(char *s, unsigned int start, size_t len, int need_free);
int		ft_line(char *src);

#endif
