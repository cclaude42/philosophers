/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:24:11 by cclaude           #+#    #+#             */
/*   Updated: 2020/09/09 18:04:05 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/time.h>

typedef struct	s_all
{
	pid_t	*pid;
	sem_t	*forks;
	sem_t	*meals;
	int		nb_phi;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	long	t_start;
	int		nb_eat;
	long	last_meal;
	int		meal_cnt;
	int		who;
}				t_all;

int				arg_check(int ac, char **av);
void			ft_message(long time, int who, char *what);
long			ft_time(void);
void			ft_usleep(int length);
int				ft_atoi(char *str);
#endif
