/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:49:07 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/07 11:35:57 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int ft_atoi(char *str)
{
    int	i;
    int	sign;
    int	num;

    i = 0;
    sign = 1;
    num = 0;
    while ((str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	|| (str[i] == '\r' || str[i] == '\v' || str[i] == '\f'))
		i++;
    if (str[i] == '-')
        sign = -1;
    if (str[i] == '-' || str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
        num = num * 10 + (str[i++] - '0');
    return (num * sign);
}

int arg_check(int ac, char **av)
{
    int i;
    int j;

    if (ac != 5 && ac != 6)
    {
        write(2, "Invalid number of arguments.\n", 29);
        return (0);
    }
    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')
            {
                write(2, "Invalid character in arguments.\n", 32);
                return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}