/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:40:55 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/15 15:18:49 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_thread(void *void_ph)
{
	t_p	*p;
	t_m	*m;

	p = (t_p *)void_ph;
	m = p->m;
	if (p->ph_id % 2)
		usleep(50000);
	pthread_mutex_lock(&m->check);
	p->t_ph_last_ate = timestamp();
	pthread_mutex_unlock(&m->check);
	while (!checker(m))
	{
		action_message(m, p->ph_id, " is thinking.");
		if (checker(m))
			break ;
		ph_eat(p);
		if (checker(m))
			break ;
		action_message(m, p->ph_id, " is sleeping.");
		ft_justwait(m->t_sleep, m);
		if (checker(m))
			break ;
	}
	return (NULL);
}

void	add_meals(t_m *m, t_p *p)
{
	int	i;
	int	total_meals;

	i = 0;
	while (i < m->n_ph)
	{
		pthread_mutex_lock(&m->check);
		total_meals = p[i].ph_meals;
		pthread_mutex_unlock(&m->check);
		if (total_meals < (m->n_total_meals + 1))
			return ;
		i++;
	}
	pthread_mutex_lock(&m->check);
	m->all_ate = 1;
	pthread_mutex_unlock(&m->check);
}

void	dead_check_loop(t_m *m, t_p *p, int i)
{
	int	last_meal;

	pthread_mutex_lock(&m->check);
	last_meal = p[i].t_ph_last_ate;
	pthread_mutex_unlock(&m->check);
	if (time_diff(last_meal, timestamp()) > m->t_dead)
		action_message_died(m, i, " died.");
}

void	dead_check(t_m *m, t_p *p)
{
	int	i;

	if (!m->only_main)
		return ;
	m->only_main = 0;
	while (!checker(m))
	{
		i = 0;
		while (i < m->n_ph && !checker(m))
		{
			dead_check_loop(m, p, i);
			i++;
		}
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
