/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 21:34:19 by elkan             #+#    #+#             */
/*   Updated: 2026/02/09 22:43:30 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

unsigned long long	eating(t_info *info, t_philo *philo);
void				return_forks(t_info *info, t_philo *philo);
void				manage_eat_limit(t_info *info, t_philo *philo);

void				grab_fork(t_info *info, t_philo *philo, int fork);

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
unsigned long long	eating(t_info *info, t_philo *philo)
{
	int					fork_1;
	int					fork_2;
	struct timeval		time;
	unsigned long long	time_mcs;

	fork_1 = philo->fork_i[0];
	fork_2 = philo->fork_i[1];
	gettimeofday(&time, NULL);
	time_mcs = time.tv_sec * 1000000 + time.tv_usec;
	while (philo->forks_held != 2 && !check_death(info, philo,
			time_mcs, philo->die_mcs))
	{
		if (philo->forks_held == 0)
			grab_fork(info, philo, fork_1);
		if (philo->forks_held == 1)
			grab_fork(info, philo, fork_2);
		if (philo->forks_held != 2)
			usleep(1000);
		gettimeofday(&time, NULL);
		time_mcs = time.tv_sec * 1000000 + time.tv_usec;
	}
	pthread_mutex_lock(&info->r_mutex);
	if (!info->run)
		return (pthread_mutex_unlock(&info->r_mutex), 0);
	return (pthread_mutex_unlock(&info->r_mutex), time_mcs);
}

void	manage_eat_limit(t_info *info, t_philo *philo)
{
	int	finished;

	if (!info->eat_limit)
		return ;
	philo->eat_limit++;
	if (info->eat_limit && philo->eat_limit == info->eat_limit)
	{
		pthread_mutex_lock(&info->eat_lim_mutex);
		info->fully_eaten++;
		finished = info->fully_eaten == info->total_philo;
		pthread_mutex_unlock(&info->eat_lim_mutex);
		if (finished)
		{
			pthread_mutex_lock(&info->r_mutex);
			info->run = 0;
			pthread_mutex_unlock(&info->r_mutex);
		}
	}
}

void	grab_fork(t_info *info, t_philo *philo, int fork)
{
	struct timeval		time;
	unsigned long long	time_ms;

	pthread_mutex_lock(&info->m_forks[fork]);
	if (info->forks[fork])
	{
		info->forks[fork] = 0;
		pthread_mutex_unlock(&info->m_forks[fork]);
		gettimeofday(&time, NULL);
		time_ms = time.tv_sec * 1000000 + time.tv_usec;
		print_log(0, info, philo->philo_num);
		philo->forks_held++;
	}
	else
	{
		pthread_mutex_unlock(&info->m_forks[fork]);
	}
}

void	return_forks(t_info *info, t_philo *philo)
{
	int	fork_1;
	int	fork_2;

	fork_1 = philo->fork_i[0];
	fork_2 = philo->fork_i[1];
	pthread_mutex_lock(&info->m_forks[fork_1]);
	info->forks[fork_1] = 1;
	pthread_mutex_unlock(&info->m_forks[fork_1]);
	pthread_mutex_lock(&info->m_forks[fork_2]);
	info->forks[fork_2] = 1;
	pthread_mutex_unlock(&info->m_forks[fork_2]);
	philo->forks_held = 0;
}
