/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:24:55 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/15 11:06:43 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_one_thread(void *void_ph)
{
	t_p		*p;
	t_m		*m;

	p = (t_p *)void_ph;
	m = p->m;
	pthread_mutex_lock(&m->forks[p->ph_right]);
	action_message(m, p->ph_id, " has taken a fork.");
	ft_justwait(m->t_dead, m);
	action_message(m, p->ph_id, " died.");
	pthread_mutex_unlock(&m->forks[p->ph_right]);
	return (NULL);
}

int	one_ph(t_m *m)
{
	t_p		*p;
	int		i;

	p = m->p;
	m->t_begin = timestamp();
	if (pthread_create(&p[0].thread, NULL, &ft_one_thread, &p[0]))
		return (0);
	pthread_join(p[0].thread, NULL);
	i = 0;
	while (i < m->n_ph)
	{
		pthread_mutex_destroy(&m->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&m->message);
	pthread_mutex_destroy(&m->check);
	return (1);
}

void	ph_eat(t_p *p)
{
	t_m	*m;

	m = p->m;
	if (checker(m))
		return ;
	pick_forks(p);
	pthread_mutex_lock(&m->check);
	p->t_ph_last_ate = timestamp();
	p->ph_meals++;
	pthread_mutex_unlock(&m->check);
	action_message(m, p->ph_id, " is eating.");
	ft_justwait(m->t_eat, m);
	drop_forks(p);
}

void	action_message(t_m *m, int id, char *s)
{
	int		time;
	int		dead;

	pthread_mutex_lock(&m->message);
	pthread_mutex_lock(&m->check);
	dead = m->if_dead;
	pthread_mutex_unlock(&m->check);
	if (!dead)
	{
		time = (timestamp() - m->t_begin);
		printf("%u	%d%s\n", time, id + 1, s);
	}
	pthread_mutex_unlock(&m->message);
	return ;
}

void	ft_justwait(int time, t_m *m)
{
	int	i;
	int	dead;

	i = timestamp();
	while (1)
	{
		pthread_mutex_lock(&m->check);
		dead = m->if_dead;
		pthread_mutex_unlock(&m->check);
		if (dead)
			break ;
		if (time_diff(i, timestamp()) >= time)
			break ;
	}
}
