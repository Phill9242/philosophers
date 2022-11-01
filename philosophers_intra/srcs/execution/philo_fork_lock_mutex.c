/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_lock_mutex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:24:27 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:19:33 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	lock_commom_fork(int fork, t_philos *philos)
{
	pthread_mutex_lock(&philos->rules->f_lock);
	*philos->rules->h_fork[fork] = 1;
	pthread_mutex_unlock(&philos->rules->f_lock);
}

static int	find_dispute_philo(int fork, t_philos *philos)
{
	int	disp_philo_pos;

	if (fork == *philos->pos)
	{
		disp_philo_pos = *philos->pos - 1;
		if (*philos->pos == 0)
			disp_philo_pos = *philos->rules->nb_philo - 1;
	}
	else
	{
		disp_philo_pos = *philos->pos + 1;
		if (*philos->pos + 1 == *philos->rules->nb_philo)
			disp_philo_pos = 0;
	}
	return (disp_philo_pos);
}

void	lock_mutex_fork(int fork, t_philos *philos)
{
	long long int	eat;
	long long int	disp_philo_eat;
	long long int	finish_meal;
	int				disp_philo_pos;
	int				sleep_time;

	disp_philo_pos = find_dispute_philo (fork, philos);
	pthread_mutex_lock (&philos->rules->eat_lock);
	disp_philo_eat = *philos->rules->all_philos[disp_philo_pos]->eat;
	eat = *philos->eat;
	pthread_mutex_unlock (&philos->rules->eat_lock);
	finish_meal = get_time_now() - eat + *philos->rules->t_eat;
	sleep_time = (get_time_now() - eat - *philos->rules->time_to_die) * -1;
	if (eat > disp_philo_eat)
	{
		if (finish_meal >= *philos->rules->time_to_die)
			usleep(sleep_time * 1000);
		else
			usleep(*philos->rules->t_eat * 1000);
	}
	pthread_mutex_lock(&philos->rules->forks[fork]);
}
