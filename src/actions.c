/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:24:55 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/18 15:25:38 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_ph(t_m *m)
{
	t_p		*p;

	p = m->p;
	m->t_begin = timestamp();
	if (pthread_create(&p[0].thread, NULL, &ft_thread, &p[0]))
		return (0);
	dead_check(m, p);
	pthread_detach(p[0].thread);
	pthread_mutex_destroy(&m->forks[0]);
	pthread_mutex_destroy(&m->message);
	pthread_mutex_destroy(&m->check);
	while (m->if_dead == 0)
		ft_justwait(m->t_dead, m);
	return (1);
}

void	ph_eat(t_p *p)
{
	t_m		*m;

	m = p->m;
	if ((m->n_total_meals != -1) && (p->ph_meals == m->n_total_meals + 1))
		return ;
	pthread_mutex_lock(&m->forks[p->ph_right]);
	action_message(m, p->ph_id, " has taken the right fork.");
	pthread_mutex_lock(&m->forks[p->ph_left]);
	action_message(m, p->ph_id, " has taken the left fork.");
	pthread_mutex_lock(&m->check);
	action_message(m, p->ph_id, " is eating.");
	p->t_ph_last_ate = timestamp();
	pthread_mutex_unlock(&m->check);
	ft_justwait(m->t_eat, m);
	p->ph_meals++;
	pthread_mutex_unlock(&m->forks[p->ph_right]);
	pthread_mutex_unlock(&m->forks[p->ph_left]);
}

void	action_message(t_m *m, int id, char *s)
{
	pthread_mutex_lock(&m->message);
	if (!m->if_dead)
	{
		printf("%d	", timestamp() - m->t_begin);
		printf("%d", id + 1);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&m->message);
	return ;
}

void	ft_justwait(int time, t_m *m)
{
	int	i;

	i = timestamp();
	while (!(m->if_dead))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
}
