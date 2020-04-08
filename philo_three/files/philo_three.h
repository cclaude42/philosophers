/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:24:11 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/08 16:29:45 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <semaphore.h>
# include <pthread.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# define EATING 1
# define SLEEPING 2
# define THINKING 3

typedef struct	s_all
{
	sem_t	*forks;
	int 	nb_phi;
    int		t_die;
    int 	t_eat;
    int 	t_sleep;
	long	t_start;
    int 	nb_eat;
	long	last_meal;
	int		meal_cnt;
	int		who;
}				t_all;

int		arg_check(int ac, char **av);
int		ft_atoi(char *str);
int		ft_nbrlen(long n);
size_t	ft_strlen(const char *s);

void	ft_message(long time, int who, char *what);
long	ft_time();
#endif
