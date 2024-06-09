/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:48:48 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/08 22:44:23 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	res;

	j = 0;
	i = ft_strlen(dst);
	res = i + ft_strlen(src);
	if (i >= dstsize)
		return (res - i + dstsize);
	while (i < dstsize && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
		if (i < dstsize && src[j] == 0)
			dst[i] = '\0';
	}
	if (i >= dstsize)
		i = dstsize - 1;
	if (dst[i] != '\0')
		dst[i] = '\0';
	return (res);
}
