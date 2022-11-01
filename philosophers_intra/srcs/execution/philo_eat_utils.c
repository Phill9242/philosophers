/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:28:54 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:04:39 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	*get_prev_and_next_pos(t_philos *philo)
{
	int	*pos;

	pos = ft_calloc (3, sizeof(int));
	pos[I] = *philo->pos;
	if (*philo->pos + 1 == *philo->rules->nb_philo)
		pos[NEXT] = 0;
	else
		pos[NEXT] = *philo->pos + 1;
	if (*philo->pos == 0)
		pos[PREV] = *philo->rules->nb_philo - 1;
	else
		pos[PREV] = *philo->pos - 1;
	return (pos);
}

int	eat_all_meals(t_rules *rules)
{
	int	i;

	pthread_mutex_lock(&rules->must_lock);
	i = -1;
	if (*rules->must_eat < 0)
	{
		pthread_mutex_unlock(&rules->must_lock);
		return (FALSE);
	}
	while (++i < *rules->nb_philo)
	{
		if (*rules->all_philos[i]->must_eat > 0)
		{
			pthread_mutex_unlock(&rules->must_lock);
			return (FALSE);
		}
	}
	pthread_mutex_unlock(&rules->must_lock);
	pthread_mutex_lock (&rules->die_check);
	*rules->is_dead = TRUE;
	pthread_mutex_unlock (&rules->die_check);
	return (TRUE);
}

int	check_eat_usleep_time(t_philos *philo, t_philos **all_philos)
{
	int	pos;
	int	prev_pos;
	int	next_pos;
	int	die_info;

	pos = *philo->pos;
	if (pos == 0)
		prev_pos = *philo->rules->nb_philo - 1;
	else
		prev_pos = pos - 1;
	if (pos == *philo->rules->nb_philo - 1)
		next_pos = 0;
	else
		next_pos = pos + 1;
	die_info = die_while_eating(philo, all_philos, prev_pos, next_pos);
	if (die_info == 0 || die_info > *philo->rules->t_eat)
		usleep (*philo->rules->t_eat * 1000);
	else
	{
		usleep (die_info * 1000);
		return (TRUE);
	}
	return (FALSE);
}

int	*longest_meal(t_philos *philo, t_philos **all_p, t_rules *rules)
{
	long long int	eat_prev;
	long long int	eat_next;
	int				*hold_fork;
	int				*pos;

	eat_prev = 0;
	eat_next = 0;
	hold_fork = ft_calloc (1, sizeof(int));
	pos = get_prev_and_next_pos(philo);
	pthread_mutex_lock(&rules->eat_lock);
	pthread_mutex_lock(&rules->f_lock);
	if (rules->h_fork[pos[I]])
		eat_prev = *all_p[pos[PREV]]->eat - get_time_now() + *rules->t_eat;
	if (rules->h_fork[pos[NEXT]])
		eat_next = *all_p[pos[NEXT]]->eat - get_time_now() + *rules->t_eat;
	pthread_mutex_unlock(&rules->f_lock);
	pthread_mutex_unlock(&rules->eat_lock);
	if (eat_next >= eat_prev)
		*hold_fork = eat_next;
	else
		*hold_fork = eat_prev;
	if (hold_fork < 0)
		*hold_fork = 0;
	free (pos);
	return (hold_fork);
}

int	choose_mutex_lock_order(t_philos *philos)
{
	if (*philos->pos % 2 == 0)
	{
		if (!invert_lock_fork_1(philos) || !invert_lock_fork_2(philos))
			return (FALSE);
	}
	else
	{
		if (lock_fork_1(philos) == FALSE || lock_fork_2(philos) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}
