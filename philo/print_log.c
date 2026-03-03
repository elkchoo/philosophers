/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print_log.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: elkan <elkan@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2026/01/29 14:46:13 by Elkan Choo		#+#	#+#			 */
/*   Updated: 2026/02/11 20:18:26 by elkan			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

// act 0: timestamp_in_mcs X has taken a fork
// act 1: timestamp_in_mcs X is eating
// act 2: timestamp_in_mcs X is sleeping
// act 3: timestamp_in_mcs X is thinking
// act 4: timestamp_in_mcs X died

#include "philo.h"

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

// Note: For death, now_ms given will be death_mcs, so now_ms is equivalent
// to death_mcs
int	print_log(int act, t_info *info, int philo_num)
{
	struct timeval		now;
	unsigned long long	now_ms;

	pthread_mutex_lock(&info->r_mutex);
	if (!info->run)
		return (pthread_mutex_unlock(&info->r_mutex), 1);
	pthread_mutex_unlock(&info->r_mutex);
	pthread_mutex_lock(&info->print_mutex);
	gettimeofday(&now, NULL);
	now_ms = (now.tv_sec * 1000000 + now.tv_usec - info->start_mcs) / 1000;
	if (act == 0)
		printf("%llu %i has taken a fork\n", now_ms, philo_num);
	else if (act == 1)
		printf("%llu %i is eating\n", now_ms, philo_num);
	else if (act == 2)
		printf("%llu %i is sleeping\n", now_ms, philo_num);
	else if (act == 3)
		printf("%llu %i is thinking\n", now_ms, philo_num);
	else if (act == 4)
	{
		printf("%llu %i died\n", now_ms, philo_num);
		pthread_mutex_lock(&info->r_mutex);
		info->run = 0;
		pthread_mutex_unlock(&info->r_mutex);
	}
	return (pthread_mutex_unlock(&info->print_mutex), 0);
}
