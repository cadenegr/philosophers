/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:28:35 by cadenegr          #+#    #+#             */
/*   Updated: 2024/06/18 12:39:30 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <stdint.h>
# include <limits.h>

struct	s_main;

typedef struct s_philo
{
	pthread_t		thread;
	int				ph_id;
	int				ph_meals;
	int				ph_left;
	int				ph_right;
	int				t_ph_last_ate;
	struct s_main	*m;
}	t_p;

typedef struct s_main
{
	int				n_ph;
	int				n_total_meals;
	int				if_dead;
	int				t_dead;
	int				t_eat;
	int				t_sleep;
	int				t_begin;
	int				all_ate;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message;
	pthread_mutex_t	check;
	t_p				*p;
}	t_m;

//arguments.c
int		arg(int ac, char **av, t_m *m);
int		init_mutex(t_m *m);
int		init_ph(t_m *m);
int		ft_alloc(t_m *m);

//tools.c
int		ft_strlen(char *s);
int		ft_isuint(const char *s);
int		ft_isdigit(int c);
int		ft_error(char *s);

//actions.c
int		one_ph(t_m *m);
void	ph_eat(t_p *p);
void	ft_justwait(int time, t_m *m);
void	action_message(t_m *m, int id, char *s);

//starter.c
void	*ft_thread(void *void_ph);
void	add_meals(t_m *m, t_p *p);
void	dead_check(t_m *m, t_p *p);
void	exit_starter(t_m *m, t_p *p);
int		starter(t_m *m);

//time.c
int		timestamp(void);
int		time_diff(int before, int now);
#endif
