/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elkan <elkan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 12:00:00 by elkan             #+#    #+#             */
/*   Updated: 2026/02/12 18:31:31 by elkan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct information
{
	unsigned long long	start_mcs;
	unsigned long long	eat_mcs;
	unsigned long long	sleep_mcs;
	unsigned long long	starve_mcs;
	uint8_t				*forks;
	pthread_mutex_t		*m_forks;
	int					total_philo;
	int					philo_num;
	pthread_mutex_t		p_num_mutex;
	int					eat_limit;
	int					fully_eaten;
	uint8_t				run;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		r_mutex;
	pthread_mutex_t		eat_lim_mutex;
}	t_info;

typedef struct philosopher
{
	unsigned long long	die_mcs;
	unsigned long long	sleep_mcs;
	unsigned long long	wake_mcs;
	unsigned long long	eat_mcs;
	int					philo_num;
	uint8_t				dom_hand;
	uint8_t				fork_i[2];
	uint8_t				forks_held;
	int					number;
	int					eat_limit;
}	t_philo;

// from ft_atoll.c
long long int		ft_atoll(const char *str);

// from setup.c
void				setup(int eat_limit, char *argv[], t_info *data);
void				find_fork_index(t_info *info, t_philo *philo);
void				philo_setup(t_info *info, t_philo *philo);
void				set_start_time(t_info *info);

// from phillosophers.c
void				*philosopher_act(void *i);
int					update_times(t_info *info, t_philo *philo,
						long long unsigned int time_ate_mcs);

// from print_log.c
int					print_log(int act, t_info *info, int philo_num);

// from wait_till.c
int					wait_till(t_info *info, t_philo *philo,
						unsigned long long timemcs,
						unsigned long long death_mcs);

// from eating.c
unsigned long long	eating(t_info *info, t_philo *philo);
void				return_forks(t_info *info, t_philo *philo);
void				manage_eat_limit(t_info *info, t_philo *philo);

// from check_end.c
int					check_death(t_info *info, t_philo *philo,
						unsigned long long now_mcs,
						unsigned long long death_mcs);

// from shutdown.c						
int					shutdown(t_info *info, pthread_t *philo);

#endif
