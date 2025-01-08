/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:45:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/15 11:06:06 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action_message_died(t_m *m, int id, char *s)
{
	int		time;

	pthread_mutex_lock(&m->message);
	time = (timestamp() - m->t_begin);
	printf("%u	%d%s\n", time, id + 1, s);
	pthread_mutex_lock(&m->check);
	m->if_dead = 1;
	pthread_mutex_unlock(&m->check);
	pthread_mutex_unlock(&m->message);
	return ;
}

int	ft_error(char *s)
{
	write (2, "Error: ", ft_strlen("Error: "));
	write (2, s, ft_strlen(s));
	write (2, "\n", 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_m		m;

	if (!arg(ac, av, &m))
		return (1);
	if (m.n_ph == 1)
	{
		one_ph(&m);
		free (m.forks);
		free (m.p);
		return (0);
	}
	if (!starter(&m))
		return (1);
	free (m.forks);
	free (m.p);
	return (0);
}
