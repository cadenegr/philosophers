/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:51:26 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/17 15:15:07 by cadenegr         ###   ########.fr       */
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

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_error(char *s)
{
	write (2, "Error: ", ft_strlen("Error: "));
	write (2, s, ft_strlen(s));
	write (2, "\n", 1);
	return (1);
}
