/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:40:55 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/18 15:55:00 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *void_ph)
{
	t_p		*p;
	t_m		*m;

	p = (t_p *)void_ph;
	m = p->m;
	if (p->ph_id % 2)
		usleep(15000);
	while (!m->if_dead)
	{
		ph_eat(p);
		if (m->all_ate)
			break ;
		action_message(m, p->ph_id, " is sleeping.");
		ft_justwait(m->t_sleep, m);
		action_message(m, p->ph_id, " is thinking.");
	}
	return (NULL);
}

void	add_meals(t_m *m, t_p *p)
{
	int	i;

	i = 0;
	while (i < m->n_ph && p[i].ph_meals == (m->n_total_meals + 1))
		i++;
	if (i == m->n_ph)
		m->all_ate = 1;
}

void	dead_check(t_m *m, t_p *p)
{
	int	i;

	while (!m->all_ate) 
	{
		i = 0;
		while (i < m->n_ph && !m->if_dead)
		{
			pthread_mutex_lock(&m->check);
			if (time_diff(p[i].t_ph_last_ate, timestamp()) > m->t_dead)
			{
				action_message(m, i, " died.");
				m->if_dead = 1;
			}
			pthread_mutex_unlock(&m->check);
			usleep(10);
			i++;
		}
		if (m->if_dead)
			break ;
		if (m->n_total_meals != -1)
			add_meals(m, p);
	}
}

void	exit_starter(t_m *m, t_p *p)
{
	int	i;

	i = 0;
	while (i < m->n_ph)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < m->n_ph)
	{
		pthread_mutex_destroy(&m->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&m->message);
	pthread_mutex_destroy(&m->check);
}

int	starter(t_m *m)
{
	int		i;
	t_p		*p;

	i = 0;
	p = m->p;
	m->t_begin = timestamp();
	while (i < m->n_ph)
	{
		if (pthread_create(&p[i].thread, NULL, ft_thread, &p[i]))
			return (0);
		p[i].t_ph_last_ate = timestamp();
		i++;
	}
	dead_check(m, m->p);
	exit_starter(m, p);
	return (1);
}
