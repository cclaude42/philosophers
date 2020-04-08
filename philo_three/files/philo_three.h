/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:24:11 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 15:42:07 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
// # include <fcntl.h>
// # include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3

typedef struct	s_nb
{
	int 	phi;
    int 	eat;
	int		meals;
	sem_t	*forks;
}				t_nb;

typedef struct	s_t
{
    int		die;
    int 	eat;
    int 	sleep;
	long	start;
	long	last;
}				t_t;

int		arg_check(int ac, char **av);
int		ft_atoi(char *str);
int		ft_nbrlen(long n);
size_t	ft_strlen(const char *s);

void	ft_message(long time, int who, char *what);
long	ft_time();
#endif
