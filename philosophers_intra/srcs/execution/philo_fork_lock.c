/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fork_lock.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 01:10:41 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:14:17 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	lock_fork_2(t_philos *philos)
{
	if (*philos->pos + 1 == *philos->rules->nb_philo)
	{
		lock_mutex_fork (0, philos);
		if (is_philo_dead (philos) == TRUE)
		{
			pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
			pthread_mutex_unlock(&philos->rules->forks[0]);
			return (FALSE);
		}
		lock_commom_fork (0, philos);
	}
	else
	{
		lock_mutex_fork (*philos->pos + 1, philos);
		if (is_philo_dead (philos) == TRUE)
		{
			pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
			pthread_mutex_unlock(&philos->rules->forks[*philos->pos + 1]);
			return (FALSE);
		}
		lock_commom_fork (*philos->pos + 1, philos);
	}
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	return (TRUE);
}

int	lock_fork_1(t_philos *philos)
{
	lock_mutex_fork (*philos->pos, philos);
	if (is_philo_dead (philos) == TRUE)
	{
		pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
		return (FALSE);
	}
	pthread_mutex_lock(&philos->rules->f_lock);
	*philos->rules->h_fork[*philos->pos] = 1;
	pthread_mutex_unlock(&philos->rules->f_lock);
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	return (TRUE);
}

int	invert_lock_fork_1(t_philos *philos)
{
	if (*philos->pos + 1 == *philos->rules->nb_philo)
	{
		lock_mutex_fork (0, philos);
		if (is_philo_dead (philos) == TRUE)
		{
			pthread_mutex_unlock(&philos->rules->forks[0]);
			return (FALSE);
		}
		lock_commom_fork (0, philos);
	}
	else
	{
		lock_mutex_fork (*philos->pos + 1, philos);
		if (is_philo_dead (philos) == TRUE)
		{
			pthread_mutex_unlock(&philos->rules->forks[*philos->pos + 1]);
			return (FALSE);
		}
		lock_commom_fork (*philos->pos + 1, philos);
	}
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	return (TRUE);
}

int	invert_lock_fork_2(t_philos *philos)
{
	lock_mutex_fork (*philos->pos, philos);
	if (is_philo_dead (philos) == TRUE)
	{
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
		pthread_mutex_unlock(&philos->rules->forks[*philos->pos]);
		return (FALSE);
	}
	pthread_mutex_lock(&philos->rules->f_lock);
	*philos->rules->h_fork[*philos->pos] = 1;
	pthread_mutex_unlock(&philos->rules->f_lock);
	ft_print (FORK, time_str(philos), *philos->pos + 1, philos->rules);
	return (TRUE);
}
