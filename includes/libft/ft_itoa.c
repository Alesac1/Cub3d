/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:15:11 by dde-giov          #+#    #+#             */
/*   Updated: 2024/06/08 22:44:23 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	if (n < 0)
		digits++;
	while (n != 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*s;

	digits = ft_count_digits(n);
	s = malloc(sizeof(char) * (digits + 1));
	if (s == NULL)
		return (NULL);
	s[digits] = '\0';
	digits--;
	if (n < 0)
	{
		s[0] = '-';
		if (n == -2147483648)
		{
			n = -214748364;
			s[digits--] = '8';
		}
		n = -n;
	}
	while (digits >= 0 && s[digits] != '-')
	{
		s[digits--] = '0' + (n % 10);
		n /= 10;
	}
	return (s);
}
