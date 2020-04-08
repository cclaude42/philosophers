/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 16:46:11 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void    *death_loop(void *ptr)
{
    t_all   *s;;

    s = (t_all *)ptr;
    while (1)
    {
        if (ft_time() - s->last_meal > s->t_die)
        {
            ft_message(s->t_start, s->who, "has died");
            // kill everything !
        }
    }
    return (NULL);
}

void    philosopher(t_all s)
{
    pthread_t   tid;

    pthread_create(&tid, NULL, death_loop, &s);
    while (1)
    {
        sem_wait(s.forks);
        ft_message(s.t_start, s.who, "has taken a fork");
        ft_message(s.t_start, s.who, "has taken a fork");
        s.last_meal = ft_time();
        s.meal_cnt++;
        ft_message(s.t_start, s.who, "is eating");
        usleep(s.t_eat * 1000);
        sem_post(s.forks);
        ft_message(s.t_start, s.who, "is sleeping");
        usleep(s.t_sleep * 1000);
        ft_message(s.t_start, s.who, "is thinking");
    }
}

void    philo_three(t_all s)
{
    int i;

    i = 0;
    while (i < s.nb_phi)
    {
        if (fork() == 0)
        {
            s.who = i + 1;
            philosopher(s);
            i = s.nb_phi;
        }
        i++;
    }
    while ((waitpid(-1, NULL, 0)) != -1)
        ;
}

int     main(int ac, char **av)
{
    t_all s;

    if (arg_check(ac, av) == 0)
        return (1);
    s.nb_phi = ft_atoi(av[1]);
    s.t_die = ft_atoi(av[2]);
    s.t_eat = ft_atoi(av[3]);
    s.t_sleep = ft_atoi(av[4]);
    s.nb_eat = (ac == 6) ? ft_atoi(av[5]): -1;
    s.t_start = ft_time();
    s.last_meal = s.t_start;
    s.meal_cnt = 0;
    sem_unlink("forks");
    s.forks = sem_open("forks", O_CREAT, S_IRWXU, (unsigned int)(s.nb_phi / 2));
    philo_three(s);
    sem_close(s.forks);
    sem_unlink("forks");
    return (0);
}
