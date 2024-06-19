/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:46:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/17 13:59:35 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	time_diff(int before, int now)
{
	return (now - before);
}
