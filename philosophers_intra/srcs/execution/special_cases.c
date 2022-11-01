/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:43:20 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/15 15:43:20 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*cant_eat_alone(void *philo_void)
{
	t_philos	*philos;

	philos = (t_philos *) philo_void;
	pthread_mutex_lock(&philos->rules->forks[*philos->pos]);
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	usleep(*philos->rules->time_to_die * 1000);
	pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
	ft_print (DIE, time_str(philos), *philos->pos + 1, philos->rules);
	return (0);
}

void	*cant_eat_so_fast(void *philo_void)
{
	t_philos	*philos;

	philos = (t_philos *) philo_void;
	if (*philos->pos % 2 == 0)
		usleep(60 * 1000);
	pthread_mutex_lock(&philos->rules->forks[*philos->pos]);
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	if (*philos->pos + 1 == *philos->rules->nb_philo)
		pthread_mutex_lock(&philos->rules->forks[0]);
	else
		pthread_mutex_lock(&philos->rules->forks[*philos->pos + 1]);
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	ft_print (EAT, time_str(philos), *philos->pos + 1, philos->rules);
	usleep(*philos->rules->time_to_die * 1000);
	ft_print (DIE, time_str(philos), *philos->pos + 1, philos->rules);
	pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
	if (*philos->pos + 1 == *philos->rules->nb_philo)
		pthread_mutex_unlock(&philos->rules->forks[0]);
	else
		pthread_mutex_unlock(&philos->rules->forks[*philos->pos + 1]);
	return (0);
}
