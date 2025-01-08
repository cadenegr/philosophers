/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:46:43 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/15 11:05:56 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pick_forks(t_p *p)
{
	t_m	*m;

	m = p->m;
	if (p->ph_id % 2 == 0)
	{
		pthread_mutex_lock(&m->forks[p->ph_right]);
		action_message(m, p->ph_id, " has taken a fork.");
		pthread_mutex_lock(&m->forks[p->ph_left]);
		action_message(m, p->ph_id, " has taken a fork.");
	}
	else
	{
		pthread_mutex_lock(&m->forks[p->ph_left]);
		action_message(m, p->ph_id, " has taken a fork.");
		pthread_mutex_lock(&m->forks[p->ph_right]);
		action_message(m, p->ph_id, " has taken a fork.");
	}
}

void	drop_forks(t_p *p)
{
	t_m	*m;

	m = p->m;
	if (p->ph_id % 2 == 0)
	{
		pthread_mutex_unlock(&m->forks[p->ph_right]);
		pthread_mutex_unlock(&m->forks[p->ph_left]);
	}
	else
	{
		pthread_mutex_unlock(&m->forks[p->ph_left]);
		pthread_mutex_unlock(&m->forks[p->ph_right]);
	}
}

int	checker(t_m *m)
{
	int	dead;
	int	eaten;

	pthread_mutex_lock(&m->check);
	dead = m->if_dead;
	eaten = m->all_ate;
	pthread_mutex_unlock(&m->check);
	if (dead || eaten)
		return (1);
	return (0);
}

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
