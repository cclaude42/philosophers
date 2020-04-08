/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 23:48:19 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void    *meal_loop(void *ptr)
{
    t_all   *s;
    int     i;

    s = (t_all *)ptr;
    i = 0;
    while (i < s->nb_phi)
    {
        sem_wait(s->meals);
        i++;
    }
    i = 0;
    while (i < s->nb_phi)
        kill(s->pid[i++], SIGTERM);
    free(s->pid);
    ft_message(s->t_start, 0, "Everyone has eaten enough !");
    sem_unlink("forks");
    sem_unlink("meals");
    exit(0);
    return (NULL);
}

void    *death_loop(void *ptr)
{
    t_all   *s;
    int     check;

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
        ft_message(s.t_start, s.who, "is eating");
        usleep(s.t_eat * 1000);
        s.meal_cnt++;
        sem_post(s.forks);
        ft_message(s.t_start, s.who, "is sleeping");
        usleep(s.t_sleep * 1000);
        ft_message(s.t_start, s.who, "is thinking");
    }
}

void    philo_three(t_all s)
{
    int         i;
    pthread_t   tid;

    i = 0;
    if (!(s.pid = malloc(sizeof(pid_t) * s.nb_phi)))
        return ;
    while (i < s.nb_phi)
    {
        s.pid[i] = fork();
        if (s.pid[i] == 0)
        {
            s.who = i + 1;
            philosopher(s);
            i = s.nb_phi;
        }
        i++;
    }
    pthread_create(&tid, NULL, meal_loop, &s);
    waitpid(-1, NULL, 0);
    i = 0;
    while (i < s.nb_phi)
        kill(s.pid[i++], SIGTERM);
    free(s.pid);
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
    sem_unlink("meals");
    s.forks = sem_open("forks", O_CREAT, S_IRWXU, (s.nb_phi / 2));
    s.meals = sem_open("meals", O_CREAT, S_IRWXU, 0);
    philo_three(s);
    sem_close(s.forks);
    sem_close(s.meals);
    sem_unlink("forks");
    sem_unlink("meals");
    return (0);
}
