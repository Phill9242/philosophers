/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:44:15 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/16 13:42:10 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_philosophers(t_philos **philo, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < *rules->nb_philo)
	{
		free(philo[i]->eat);
		free(philo[i]->pos);
		free(philo[i]->must_eat);
		free(philo[i]);
	}
	free (philo);
	return ;
}

void	ft_destroy_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < *rules->nb_philo)
		pthread_mutex_destroy (&rules->forks[i]);
	pthread_mutex_destroy (rules->print);
	pthread_mutex_destroy (&rules->die_check);
	pthread_mutex_destroy (&rules->f_lock);
	pthread_mutex_destroy (&rules->eat_lock);
	pthread_mutex_destroy (&rules->must_lock);
}

void	ft_exit_and_free(t_philos **philo, t_rules *rules)
{
	int	i;

	i = -1;
	free_philosophers (philo, rules);
	ft_destroy_mutex (rules);
	while (++i < *rules->nb_philo)
		free(rules->h_fork[i]);
	free (rules->h_fork);
	free(rules->init_time);
	free(rules->time_to_die);
	free(rules->t_eat);
	free(rules->sleep);
	free(rules->must_eat);
	free(rules->is_dead);
	free(rules->print);
	free(rules->forks);
	free(rules->nb_philo);
	free (rules);
}
