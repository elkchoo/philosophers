/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_till.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 18:16:12 by Elkan Choo        #+#    #+#             */
/*   Updated: 2026/02/09 22:33:36 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <sys/time.h>
#include <unistd.h>

int	wait_till(t_info *info, t_philo *philo, unsigned long long timemcs,
				unsigned long long death_mcs)
{
	struct timeval		now;
	unsigned long long	now_mcs;
	int					run;

	pthread_mutex_lock(&info->r_mutex);
	run = info->run;
	pthread_mutex_unlock(&info->r_mutex);
	gettimeofday(&now, NULL);
	now_mcs = now.tv_sec * 1000000 + now.tv_usec;
	while (now_mcs < timemcs && !check_death(info, philo, now_mcs, death_mcs)
		&& run)
	{
		usleep(1000);
		gettimeofday(&now, NULL);
		now_mcs = now.tv_sec * 1000000 + now.tv_usec;
		pthread_mutex_lock(&info->r_mutex);
		run = info->run;
		pthread_mutex_unlock(&info->r_mutex);
	}
	return (!run);
}
