/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/10/22 12:17:49 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*meal_loop(void *ptr)
{
	t_all	*s;
	int		i;

	s = (t_all *)ptr;
	i = 0;
	while (s->nb_eat != 0 && i < s->nb_phi)
	{
		sem_wait(s->meals);
		i++;
	}
	*s->run = 0;
	ft_message(1, s->t_start, 0, "Everyone has eaten enough !");
	sem_post(s->death);
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
	while (*s->run)
	{
		if (ft_time() - s->last_meal > s->t_die && alive)
		{
			*s->run = 0;
			ft_message(1, s->t_start, s->who, "has died");
			sem_post(s->death);
			alive = 0;
			return (NULL);
		}
		else if (s->nb_eat != -1 && s->meal_cnt >= s->nb_eat && hungry)
		{
			ft_usleep(s->who);
			sem_post(s->meals);
			hungry = 0;
			return (NULL);
		}
	}
	return (NULL);
}

void	*philosopher(void *ptr)
{
	pthread_t	tid;
	t_all		*s;

	s = (t_all *)ptr;
	s->last_meal = s->t_start;
	s->meal_cnt = 0;
	pthread_create(&tid, NULL, death_loop, s);
	while (*s->run && (s->nb_eat == -1 || s->nb_eat > s->meal_cnt))
	{
		sem_wait(s->forks);
		ft_message(*s->run, s->t_start, s->who, "has taken a fork");
		ft_message(*s->run, s->t_start, s->who, "has taken a fork");
		s->last_meal = ft_time();
		ft_message(*s->run, s->t_start, s->who, "is eating");
		ft_usleep(s->t_eat);
		s->meal_cnt++;
		sem_post(s->forks);
		ft_message(*s->run, s->t_start, s->who, "is sleeping");
		ft_usleep(s->t_sleep);
		ft_message(*s->run, s->t_start, s->who, "is thinking");
	}
	return (NULL);
}

void	philo_two(t_all *s, char **av)
{
	int			i;
	int			run;
	pthread_t	tid;

	i = 0;
	run = 1;
	while (i < ft_atoi(av[1]))
	{
		s[i].forks = s[0].forks;
		s[i].meals = s[0].meals;
		s[i].death = s[0].death;
		s[i].nb_phi = ft_atoi(av[1]);
		s[i].t_die = ft_atoi(av[2]);
		s[i].t_eat = ft_atoi(av[3]);
		s[i].t_sleep = ft_atoi(av[4]);
		s[i].t_start = ft_time();
		s[i].nb_eat = av[5] ? ft_atoi(av[5]) : -1;
		s[i].who = i + 1;
		s[i].run = &run;
		pthread_create(&tid, NULL, philosopher, &s[i++]);
	}
	if (s[0].nb_eat > -1)
		pthread_create(&tid, NULL, meal_loop, &s[0]);
	sem_wait(s[0].death);
	ft_usleep(s[0].t_eat + s[0].t_sleep);
}

int		main(int ac, char **av)
{
	t_all	*s;
	int		i;

	if (arg_check(ac, av) == 0)
		return (1);
	if (ft_atoi(av[1]) == 0 || !(s = malloc(sizeof(t_all) * ft_atoi(av[1]))))
		return (1);
	i = 0;
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("death");
	s[0].forks = sem_open("forks", O_CREAT, S_IRWXU, (ft_atoi(av[1]) / 2));
	s[0].meals = sem_open("meals", O_CREAT, S_IRWXU, 0);
	s[0].death = sem_open("death", O_CREAT, S_IRWXU, 0);
	philo_two(s, av);
	sem_close(s[0].death);
	sem_close(s[0].forks);
	sem_close(s[0].meals);
	sem_unlink("forks");
	sem_unlink("meals");
	sem_unlink("death");
	free(s);
	return (0);
}
