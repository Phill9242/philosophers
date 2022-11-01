/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:44:58 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/16 16:07:25 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	ft_print(int msg, long long int time, int philo, t_rules *rules)
{
	pthread_mutex_lock (&rules->die_check);
	pthread_mutex_lock (rules->print);
	if ((msg == DIE) && *rules->is_dead != TRUE)
	{
		*rules->is_dead = TRUE;
		printf ("%lld %d died\n", time, philo);
	}
	if (!*rules->is_dead)
	{
		if (msg == FORK)
			printf ("%lld %d has taken a fork\n", time, philo);
		if (msg == EAT)
			printf ("%lld %d is eating\n", time, philo);
		if (msg == THNK)
			printf ("%lld %d is thinking\n", time, philo);
		if (msg == SLP)
			printf ("%lld %d is sleeping\n", time, philo);
	}
	pthread_mutex_unlock (rules->print);
	pthread_mutex_unlock (&rules->die_check);
	return ;
}
