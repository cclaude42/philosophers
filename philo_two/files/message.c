/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 11:34:50 by cclaude           #+#    #+#             */
/*   Updated: 2020/09/03 15:25:14 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int		ft_nbrlen(long n)
{
	int		size;

	size = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		size++;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

void	ft_charfill(char *buffer, char *str, int *i)
{
	int	j;

	j = 0;
	while (str[j])
		buffer[(*i)++] = str[j++];
}

void	ft_numfill(char *buffer, long nbr, int *i)
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

void	ft_message(int run, long time, int who, char *what)
{
	char	buffer[50];
	long	stamp;
	int		size;
	int		i;

	if (run == 0)
		return ;
	stamp = ft_time() - time;
	size = ft_nbrlen(stamp) + ft_nbrlen(who) + ft_strlen(what) + 4;
	i = 0;
	ft_numfill(buffer, stamp, &i);
	buffer[i++] = ' ';
	buffer[i++] = '#';
	ft_numfill(buffer, who, &i);
	buffer[i++] = ' ';
	if (who == 0)
		i -= 3;
	ft_charfill(buffer, what, &i);
	buffer[i++] = '\n';
	buffer[i++] = '\0';
	write(1, buffer, size);
}
