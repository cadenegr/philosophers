/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:51:26 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/13 18:12:08 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isuint(const char *s)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
		{
			num = num * 10 + (s[i] - '0');
			i++;
		}
		else
		{
			ft_error("Wrong argument(s).");
			return (-1);
		}
	}
	if (num > 2147483647)
	{
		ft_error("Number can't be greater than an INT_MAX.");
		return (-1);
	}
	return (num);
}

int	ft_numlen(int n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0 && base == 10)
		len++;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*ptr;
	const char	*base = "0123456789";

	len = ft_numlen(n, 10);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[len] = 0;
	if (n == 0)
		ptr[0] = '0';
	if (n < 0)
		ptr[0] = '-';
	while (n != 0)
	{
		if (n > 0)
			ptr[--len] = base[n % 10];
		else
			ptr[--len] = base[-(n % 10)];
		n /= 10;
	}
	return (ptr);
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
