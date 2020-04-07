/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/07 10:24:11 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/07 17:41:20 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

// # include <stdlib.h>
// # include <fcntl.h>
// # include <string.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct	s_nb
{
	int 	phi;
    int 	eat;
	sem_t	*forks;
}				t_nb;

typedef struct	s_t
{
    int die;
    int eat;
    int sleep;
}				t_t;

int arg_check(int ac, char **av);
int ft_atoi(char *str);
#endif
