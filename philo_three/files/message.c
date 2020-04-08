/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 11:34:50 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 15:23:48 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void        ft_charfill(char *buffer, char *str, int *i)
{
    int j;

    j = 0;
    while (str[j])
        buffer[(*i)++] = str[j++];
}

void        ft_numfill(char *buffer, long nbr, int *i)
{
    long	div;

    if (nbr == 0)
    {
        buffer[(*i)++] = '0';
        return ;
    }
    div = 1000000000;
    while (nbr / div == 0)
        div = div / 10;
    while (div > 0)
    {
        buffer[(*i)++] = nbr / div + '0';
        nbr = nbr % div;
        div = div / 10;
    }
}

long   ft_time()
{
    struct timeval  te;

    gettimeofday(&te, NULL);
    return (te.tv_sec * 1000 + te.tv_usec / 1000);
}

void        ft_message(long time, int who, char *what)
{
    long    stamp;
    char    *buffer;
    int     size;
    int     i;

    i = 0;
    stamp = ft_time() - time;
    size = ft_nbrlen(stamp) + ft_nbrlen(who) + ft_strlen(what) + 5;
    buffer = malloc(sizeof(char) * size);
    ft_numfill(buffer, stamp, &i);
    buffer[i++] = ' ';
    buffer[i++] = '#';
    ft_numfill(buffer, who, &i);
    buffer[i++] = ' ';
    ft_charfill(buffer, what, &i);
    buffer[i++] = '\n';
    write(1, buffer, size - 1);
    free(buffer);
}
