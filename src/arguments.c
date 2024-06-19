/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:12:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/18 13:39:42 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_m *m)
{
	int	i;

	i = 0;
	while (i < m->n_ph)
	{
		if (pthread_mutex_init(&m->forks[i], NULL))
		{
			ft_error("Problem initializing mutex for forks.");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init (&m->message, NULL))
	{
		ft_error("Problem initializing mutex for message.");
		return (0);
	}
	if (pthread_mutex_init(&m->check, NULL))
	{
		ft_error("Problem initializing mutex for check.");
		return (0);
	}
	return (1);
}

int	ft_alloc(t_m *m)
{
	m->p = malloc(sizeof(t_p) * m->n_ph);
	if (!m->p)
	{
		ft_error ("Cannot allocate memory for the philo struct.");
		return (0);
	}
	m->forks = malloc(sizeof(pthread_mutex_t) * m->n_ph);
	if (!m->forks)
	{
		ft_error ("Cannot allocate memory for the fork mutex");
		return (0);
	}
	return (1);
}

int	init_ph(t_m *m)
{
	int	i;

	i = 0;
	while (i < m->n_ph)
	{
		m->p[i].ph_id = i;
		m->p[i].ph_meals = 0;
		m->p[i].ph_right = i;
		if (i == 0)
			m->p[i].ph_left = m->n_ph - 1;
		else
			m->p[i].ph_left = m->p[i].ph_right - 1;
		m->p[i].t_ph_last_ate = timestamp();
		m->p[i].m = m;
		i++;
	}
	return (1);
}

int	arg(int ac, char **av, t_m *m)
{
	if (ac < 5 || ac > 6)
		return (0);
	m->n_ph = ft_isuint(av[1]);
	m->t_dead = ft_isuint(av[2]);
	m->t_eat = ft_isuint(av[3]);
	m->t_sleep = ft_isuint(av[4]);
	m->if_dead = 0;
	m->all_ate = 0;
	m->n_total_meals = -1;
	if (ac == 6)
		m->n_total_meals = ft_isuint(av[5]) - 1;
	if (m->n_ph <= 0 || m->t_dead <= 0 || m->t_eat <= 0 || m->t_sleep <= 0)
		return (0);
	if (ac == 6 && m->n_total_meals < 0)
		return (0);
	if (!ft_alloc(m))
		return (0);
	if (!init_mutex(m))
		return (0);
	if (!init_ph(m))
		return (0);
	return (1);
}
