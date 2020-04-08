/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 15:42:26 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void philosopher(t_nb nb, t_t t, int who)
{
    while (1)
    {
        sem_wait(nb.forks);
        ft_message(t.start, who, "has taken a fork");
        ft_message(t.start, who, "has taken a fork");
        t.last = ft_time();
        nb.meals++;
        ft_message(t.start, who, "is eating");
        usleep(t.eat * 1000);
        sem_post(nb.forks);
        ft_message(t.start, who, "is sleeping");
        usleep(t.sleep * 1000);
        ft_message(t.start, who, "is thinking");
    }
}

void philo_three(t_nb nb, t_t t)
{
    int i;

    i = 0;
    while (i < nb.phi)
    {
        if (fork() == 0)
        {
            philosopher(nb, t, i + 1);
            i = nb.phi;
        }
        i++;
    }
    while ((waitpid(-1, NULL, 0)) != -1)
        ;
}

int main(int ac, char **av)
{
    t_nb    nb;
    t_t     t;

    if (arg_check(ac, av) == 0)
        return (1);
    nb.phi = ft_atoi(av[1]);
    t.die = ft_atoi(av[2]);
    t.eat = ft_atoi(av[3]);
    t.sleep = ft_atoi(av[4]);
    nb.eat = (ac == 6) ? ft_atoi(av[5]): -1;
    nb.meals = 0;
    t.start = ft_time();
    t.last = 0;
    sem_unlink("forks");
    nb.forks = sem_open("forks", O_CREAT, S_IRWXU, (unsigned int)(nb.phi / 2));
    philo_three(nb, t);
    sem_close(nb.forks);
    sem_unlink("forks");
    return (0);
}
