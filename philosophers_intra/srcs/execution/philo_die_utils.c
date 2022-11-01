/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_die_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:10:54 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:21:21 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	die_while_eating(t_philos *philo, t_philos **all_philos, int prev, int next)
{
	int				die_info;
	int				t_die;
	int				t_eat;
	long long int	prev_eat;
	long long int	next_eat;

	pthread_mutex_lock (&philo->rules->eat_lock);
	prev_eat = *all_philos[prev]->eat;
	next_eat = *all_philos[next]->eat;
	pthread_mutex_unlock (&philo->rules->eat_lock);
	t_eat = *philo->rules->t_eat;
	t_die = *philo->rules->time_to_die;
	die_info = 0;
	if (get_time_now() - prev_eat + t_eat >= t_die)
	{
		die_info = (get_time_now() - prev_eat - t_die) * -1;
		return (die_info);
	}
	else if (get_time_now() - next_eat + t_eat >= t_die)
	{
		die_info = (get_time_now() - next_eat - t_die) * -1;
		return (die_info);
	}
	return (die_info);
}

void	ill_die_waiting_a_fork(t_philos *philo, t_philos **all_philos)
{
	int	*wait_fork;
	int	t_die;

	t_die = *philo->rules->time_to_die;
	wait_fork = longest_meal(philo, all_philos, philo->rules);
	if (*wait_fork + (get_time_now() - *philo->eat) > t_die)
		usleep(((get_time_now() - *philo->eat - t_die - 1) * -1) * 1000);
	free (wait_fork);
}

int	is_philo_dead(t_philos *philo)
{
	pthread_mutex_lock (&philo->rules->die_check);
	if (*philo->rules->is_dead == TRUE)
	{
		pthread_mutex_unlock (&philo->rules->die_check);
		return (TRUE);
	}
	if (get_time_now() - *philo->eat >= *philo->rules->time_to_die)
	{
		pthread_mutex_unlock (&philo->rules->die_check);
		ft_print (DIE, time_str(philo), *philo->pos + 1, philo->rules);
		return (TRUE);
	}
	pthread_mutex_unlock (&philo->rules->die_check);
	return (FALSE);
}
