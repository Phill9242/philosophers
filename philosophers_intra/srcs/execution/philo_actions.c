/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:44 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:02:32 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	sleep_function(t_philos *philo)
{
	int	sleep;
	int	die;

	sleep = *philo->rules->sleep;
	die = *philo->rules->time_to_die;
	ft_print (SLP, time_str(philo), *philo->pos + 1, philo->rules);
	if (get_time_now() + sleep - *philo->eat > die)
		usleep ((*philo->eat - get_time_now() + die) * 1000);
	else
		usleep (sleep * 1000);
}

void	think_function(t_philos *philo)
{
	ft_print (THNK, time_str(philo), *philo->pos + 1, philo->rules);
	ill_die_waiting_a_fork(philo, philo->rules->all_philos);
	is_philo_dead (philo);
}

static void	ft_unlock_forks(t_philos *philos)
{
	pthread_mutex_unlock(&philos->rules->f_lock);
	pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
	if (*philos->pos + 1 == *philos->rules->nb_philo)
	{
		pthread_mutex_lock(&philos->rules->f_lock);
		*philos->rules->h_fork[0] = 0;
		pthread_mutex_unlock(&philos->rules->f_lock);
		pthread_mutex_unlock(&philos->rules->forks[0]);
	}
	else
	{
		pthread_mutex_lock(&philos->rules->f_lock);
		*philos->rules->h_fork[*philos->pos + 1] = 0;
		pthread_mutex_unlock(&philos->rules->f_lock);
		pthread_mutex_unlock(&philos->rules->forks[*philos->pos + 1]);
	}
}

void	eat_function(t_philos *philos)
{
	int	sleep;

	if (choose_mutex_lock_order (philos) == FALSE)
		return ;
	ft_print (EAT, time_str(philos), *philos->pos + 1, philos->rules);
	pthread_mutex_lock(&philos->rules->must_lock);
	if (*philos->must_eat > 0)
		*philos->must_eat = *philos->must_eat - 1;
	pthread_mutex_unlock(&philos->rules->must_lock);
	pthread_mutex_lock(&philos->rules->eat_lock);
	*philos->eat = get_time_now();
	pthread_mutex_unlock(&philos->rules->eat_lock);
	eat_all_meals(philos->rules);
	sleep = check_eat_usleep_time (philos, philos->rules->all_philos);
	pthread_mutex_lock(&philos->rules->f_lock);
	*philos->rules->h_fork[*philos->pos] = 0;
	ft_unlock_forks (philos);
	if (sleep == TRUE)
		usleep (10000);
}
