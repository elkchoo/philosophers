/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:27:08 by elkan             #+#    #+#             */
/*   Updated: 2026/02/09 22:41:02 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>

void	setup(int eat_limit, char *argv[], t_info *info);
void	philo_setup(t_info *info, t_philo *philo);

// Replace fork functions in check_end, eating, setup

void	setup(int eat_limit, char *argv[], t_info *info)
{
	long long int	num;

	pthread_mutex_init(&(info->r_mutex), NULL);
	pthread_mutex_init(&(info->p_num_mutex), NULL);
	pthread_mutex_init(&(info->print_mutex), NULL);
	if (eat_limit)
		pthread_mutex_init(&(info->eat_lim_mutex), NULL);
	info->total_philo = (int)ft_atoll(argv[1]);
	info->forks = malloc((info->total_philo) * sizeof(uint8_t));
	memset(info->forks, 1, (info->total_philo) * sizeof(uint8_t));
	info->m_forks = malloc((info->total_philo) * sizeof(pthread_mutex_t));
	info->philo_num = 0;
	num = ft_atoll(argv[2]);
	info->starve_mcs = num * 1000ULL;
	num = ft_atoll(argv[3]);
	info->eat_mcs = num * 1000ULL;
	num = ft_atoll(argv[4]);
	info->sleep_mcs = num * 1000ULL;
	info->eat_limit = (int)ft_atoll(argv[4 + eat_limit]) * eat_limit;
	info->fully_eaten = 0;
	info->run = 1;
}

void	set_start_time(t_info *info)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	info->start_mcs = time.tv_sec * 1000000 + time.tv_usec;
}

// For dom hand, 0 is right, 1 is left, assuming clockwise seating
void	philo_setup(t_info *info, t_philo *philo)
{
	philo->eat_limit = 0;
	pthread_mutex_lock(&(info->p_num_mutex));
	philo->philo_num = info->philo_num;
	info->philo_num++;
	pthread_mutex_unlock(&(info->p_num_mutex));
	philo->dom_hand = philo->philo_num % 2;
	philo->forks_held = 0;
	if (philo->philo_num != info->total_philo - 1)
	{
		philo->fork_i[philo->dom_hand] = philo->philo_num;
		philo->fork_i[!philo->dom_hand] = philo->philo_num + 1;
	}
	else
	{
		philo->fork_i[philo->dom_hand] = philo->philo_num;
		philo->fork_i[!philo->dom_hand] = 0;
	}
	pthread_mutex_lock(&info->r_mutex);
	pthread_mutex_unlock(&info->r_mutex);
	philo->eat_mcs = info->start_mcs + info->eat_mcs
		* (philo->philo_num % (2 + info->total_philo % 2));
	philo->die_mcs = info->start_mcs + info->starve_mcs;
}
