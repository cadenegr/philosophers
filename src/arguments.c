/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:12:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/08/15 11:29:05 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		i++;
	}
	dead_check(m, m->p);
	exit_starter(m, p);
	return (1);
}

int	init_mutex(t_m *m)
{
	int	i;

	i = 0;
	while (i < m->n_ph)
	{
		if (pthread_mutex_init(&m->forks[i], NULL))
			return (ft_error("Problem initializing mutex for forks."));
		i++;
	}
	if (pthread_mutex_init (&m->message, NULL))
		return (ft_error("Problem initializing mutex for message."));
	if (pthread_mutex_init(&m->check, NULL))
		return (ft_error("Problem initializing mutex for check."));
	return (1);
}

int	ft_alloc(t_m *m)
{
	m->p = malloc(sizeof(t_p) * m->n_ph);
	if (!m->p)
		return (ft_error ("Cannot allocate memory for the philo struct."));
	m->forks = malloc(sizeof(pthread_mutex_t) * m->n_ph);
	if (!m->forks)
		return (ft_error ("Cannot allocate memory for the fork mutex"));
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
			m->p[i].ph_left = i - 1;
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
	m->only_main = 1;
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
