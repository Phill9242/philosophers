/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:39:52 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/18 19:32:00 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_odd_threads(t_philos *philos)
{
	if (*philos->pos % 2 == 0)
	{
		if (is_philo_dead (philos) == TRUE)
			return ;
		eat_function (philos);
		if (is_philo_dead (philos) == TRUE)
			return ;
		sleep_function (philos);
		if (is_philo_dead (philos) == TRUE)
			return ;
		think_function (philos);
	}
	else
		usleep (60 * 1000);
}

void	*routine(void *philo_void)
{
	t_philos	*philos;

	philos = (t_philos *) philo_void;
	init_odd_threads (philos);
	while (is_philo_dead (philos) == FALSE)
	{
		if (is_philo_dead (philos) == TRUE)
			return (0);
		eat_function (philos);
		if (is_philo_dead (philos) == TRUE)
			return (0);
		sleep_function (philos);
		if (is_philo_dead (philos) == TRUE)
			return (0);
		think_function (philos);
	}
	return (0);
}

int	ft_start_thread(t_philos **philos, t_rules *r, pthread_t	*pthread)
{
	int	i;

	i = 0;
	if (*r->nb_philo == 1)
		pthread_create(&pthread[0], NULL, &cant_eat_alone, philos[0]);
	else if (*r->time_to_die <= *r->t_eat)
	{
		while (i < *r->nb_philo)
		{
			pthread_create(&pthread[i], NULL, &cant_eat_so_fast, philos[i]);
			i++;
		}
	}
	else
	{
		while (i < *r->nb_philo)
		{
			pthread_create(&pthread[i], NULL, &routine, philos[i]);
			i++;
		}
	}
	return (0);
}
