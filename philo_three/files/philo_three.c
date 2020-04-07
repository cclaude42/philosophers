/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:23:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/07 12:16:22 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void philosopher(t_nb nb, t_t t)
{
    ;
}

void philo_three(t_nb nb, t_t t)
{
    int i;

    i = 0;
    while (i < nb.phi)
    {
        if (fork() == 0)
        {
            philosopher(nb, t);
            i = nb.phi;
        }
        i++;
    }
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
    philo_three(nb, t);
    return (0);
}
