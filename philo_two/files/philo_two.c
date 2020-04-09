/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/09 15:21:37 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*meal_loop(void *ptr)
{
	t_all	*s;

	s = (t_all *)ptr;
	while (s->meals < s->nb_phi)
		;
	ft_message(s->t_start, 0, "Everyone has eaten enough !");
	return (NULL);
}

void	*death_loop(void *ptr)
{
	t_all	*s;
	int		check;

	s = (t_all *)ptr;
	check = 1;
	while (1)
	{
		if (ft_time() - s->last_meal > s->t_die)
		{
			ft_message(s->t_start, s->who, "has died");
			exit(0);
		}
		else if (s->meal_cnt >= s->nb_eat && check)
		{
			sem_post(s->meals);
			check = 0;
		}
	}
	return (NULL);
}

void	*philosopher(void *ptr)
{
	pthread_t	tid;
	t_all		*s;

	s = (t_all *)ptr;
	pthread_create(&tid, NULL, death_loop, &s);
	while (1)
	{
		sem_wait(s->forks);
		ft_message(s->t_start, s->who, "has taken a fork");
		ft_message(s->t_start, s->who, "has taken a fork");
		s->last_meal = ft_time();
		ft_message(s->t_start, s->who, "is eating");
		usleep(s->t_eat * 1000);
		s->meal_cnt++;
		sem_post(s->forks);
		ft_message(s->t_start, s->who, "is sleeping");
		usleep(s->t_sleep * 1000);
		ft_message(s->t_start, s->who, "is thinking");
	}
	return (NULL);
}

void	philo_two(t_all *s)
{
	int			i;
	pthread_t	tid;

	i = 0;
	if (s[0].nb_eat > -1)
		pthread_create(&tid, NULL, meal_loop, &s[0]);
	while (i < s[0].nb_phi)
	{
		s[i].last_meal = s[i].t_start;
		s[i].meal_cnt = 0;
		s[i].who = i + 1;
		pthread_create(&tid, NULL, philosopher, &s[i]);
		i++;
	}
	while (s[0].meals > -1)
		;
	sem_close(s.forks);
	sem_close(s.meals);
	sem_unlink("forks");
	sem_unlink("meals");
	free(s);
}

int		main(int ac, char **av)
{
	t_all	*s;
	int		i;

	if (arg_check(ac, av) == 0)
		return (1);
	if (!(s = malloc(sizeof(t_all) * ft_atoi(av[1]))))
		return (1);
	sem_unlink("forks");
	sem_unlink("meals");
	s[0].forks = sem_open("forks", O_CREAT, S_IRWXU, (s.nb_phi / 2));
	s[0].meals = sem_open("meals", O_CREAT, S_IRWXU, 0;
	while (i < ft_atoi(av[1]))
	{
		s[i].forks = s[0].forks;
		s[i].meals = s[0].meals;
		s[i].nb_phi = ft_atoi(av[1]);
		s[i].t_die = ft_atoi(av[2]);
		s[i].t_eat = ft_atoi(av[3]);
		s[i].t_sleep = ft_atoi(av[4]);
		s[i].t_start = ft_time();
		s[i].nb_eat = (ac == 6) ? ft_atoi(av[5]) : -1;
	}
	philo_two(s);
	return (0);
}
