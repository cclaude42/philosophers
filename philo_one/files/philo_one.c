/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/09/02 15:24:56 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*meal_loop(void *ptr)
{
	t_all	*s;
	int		i;

	s = (t_all *)ptr;
	i = 0;
	pthread_mutex_lock(s->meals);
	while (i < s->nb_phi)
	{
		pthread_mutex_lock(s->meals);
		i++;
	}
	ft_message(s->t_start, 0, "Everyone has eaten enough !");
	pthread_mutex_unlock(s->state);
	return (NULL);
}

void	*death_loop(void *ptr)
{
	t_all	*s;
	int		alive;
	int		hungry;

	s = (t_all *)ptr;
	alive = 1;
	hungry = 1;
	while (1)
	{
		if (ft_time() - s->last_meal > s->t_die && alive)
		{
			ft_message(s->t_start, s->who, "has died");
			pthread_mutex_unlock(s->state);
			alive = 0;
		}
		else if (s->meal_cnt >= s->nb_eat && hungry)
		{
			pthread_mutex_unlock(s->meals);
			hungry = 0;
		}
	}
	return (NULL);
}

void	*philosopher(void *ptr)
{
	pthread_t	tid;
	t_all		*s;

	s = (t_all *)ptr;
	pthread_create(&tid, NULL, death_loop, s);
	s->who % 2 ? 0 : ft_usleep(ft_time(), s->t_eat);
	while (1)
	{
		pthread_mutex_lock(&s->fork);
		ft_message(s->t_start, s->who, "has taken a fork");
		pthread_mutex_lock(s->prev);
		ft_message(s->t_start, s->who, "has taken a fork");
		s->last_meal = ft_time();
		ft_message(s->t_start, s->who, "is eating");
		ft_usleep(ft_time(), s->t_eat);
		pthread_mutex_unlock(&s->fork);
		pthread_mutex_unlock(s->prev);
		s->meal_cnt++;
		ft_message(s->t_start, s->who, "is sleeping");
		ft_usleep(ft_time(), s->t_sleep);
		ft_message(s->t_start, s->who, "is thinking");
	}
	return (NULL);
}

void	philo_one(t_all *s)
{
	pthread_mutex_t	state;
	pthread_mutex_t	meals;
	pthread_t		tid;
	int				i;

	s[0].prev = &s[s[0].nb_phi - 1].fork;
	pthread_mutex_init(&state, NULL);
	pthread_mutex_init(&meals, NULL);
	pthread_mutex_lock(&state);
	i = 0;
	while (i < s[0].nb_phi)
	{
		s[i].state = &state;
		s[i].meals = &meals;
		pthread_create(&tid, NULL, philosopher, &s[i++]);
	}
	if (s[0].nb_eat > -1)
		pthread_create(&tid, NULL, meal_loop, &s[0]);
	pthread_mutex_lock(&state);
	i = 0;
	while (i < s[0].nb_phi)
		pthread_mutex_destroy(&s[i++].fork);
	pthread_mutex_destroy(&state);
	pthread_mutex_destroy(&meals);
	free(s);
}

int		main(int ac, char **av)
{
	t_all	*s;
	int		i;

	if (arg_check(ac, av) == 0 || ft_atoi(av[1]) == 0)
		return (1);
	if (!(s = malloc(sizeof(t_all) * ft_atoi(av[1]))))
		return (1);
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		pthread_mutex_init(&s[i].fork, NULL);
		s[i].prev = (i != 0) ? &s[i - 1].fork : NULL;
		s[i].nb_phi = ft_atoi(av[1]);
		s[i].t_die = ft_atoi(av[2]);
		s[i].t_eat = ft_atoi(av[3]);
		s[i].t_sleep = ft_atoi(av[4]);
		s[i].t_start = ft_time();
		s[i].nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
		s[i].last_meal = s[i].t_start;
		s[i].meal_cnt = 0;
		s[i].who = i + 1;
		i++;
	}
	philo_one(s);
	return (0);
}
