/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:45:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/18 13:26:40 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_m		m;

	if (!arg(ac, av, &m))
		return (1);
	if (m.n_ph == 1)
	{
		one_ph(&m);
		return (1);
	}
	if (!starter(&m))
		return (1);
	free (m.forks);
	free (m.p);
	return (0);
}
