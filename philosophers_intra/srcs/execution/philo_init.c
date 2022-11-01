/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:33:38 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/16 15:24:41 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_alloc_mem_for_rules(t_rules *rules)
{
	rules->init_time = ft_calloc (1, sizeof (long long int));
	rules->nb_philo = ft_calloc (1, sizeof (int));
	rules->time_to_die = ft_calloc (1, sizeof (int));
	rules->t_eat = ft_calloc (1, sizeof (int));
	rules->sleep = ft_calloc (1, sizeof (int));
	rules->must_eat = ft_calloc (1, sizeof (int));
	rules->is_dead = ft_calloc (1, sizeof (int));
	*rules->is_dead = FALSE;
}

void	ft_alloc_mem_for_philos(t_philos **philos, t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < *rules->nb_philo)
	{
		philos[i] = ft_calloc (1, sizeof (t_philos));
		philos[i]->rules = rules;
		philos[i]->pos = ft_calloc (1, sizeof(int));
		philos[i]->must_eat = ft_calloc (1, sizeof(int));
		*philos[i]->must_eat = *rules->must_eat;
		*philos[i]->pos = i;
		philos[i]->eat = ft_calloc (1, sizeof(long long int));
		*philos[i]->eat = *rules->init_time;
	}
}

void	ft_save_args(int argc, char **argv, t_rules *r, t_philos **philos)
{
	struct timeval	t_now;
	int				i;

	i = -1;
	gettimeofday(&t_now, NULL);
	ft_alloc_mem_for_rules (r);
	*r->init_time = (t_now.tv_sec * 1000) + (t_now.tv_usec / 1000);
	*r->nb_philo = ft_atol(argv[1]);
	*r->time_to_die = ft_atol(argv[2]);
	*r->t_eat = ft_atol(argv[3]);
	*r->sleep = ft_atol(argv[4]);
	if (argc == 6)
		*r->must_eat = ft_atol(argv[5]);
	else
		*r->must_eat = -1;
	r->all_philos = philos;
	r->print = ft_calloc(1, sizeof(pthread_mutex_t));
	r->forks = ft_calloc(*r->nb_philo, sizeof(pthread_mutex_t));
	r->h_fork = ft_calloc(*r->nb_philo, sizeof(int *));
	while (++i < *r->nb_philo)
		r->h_fork[i] = ft_calloc (1, sizeof(int));
	ft_alloc_mem_for_philos (philos, r);
	return ;
}

void	ft_init_mutex(t_rules *rules)
{
	int	i;

	i = -1;
	while (++i < *rules->nb_philo)
		pthread_mutex_init (&rules->forks[i], NULL);
	pthread_mutex_init (rules->print, NULL);
	pthread_mutex_init (&rules->die_check, NULL);
	pthread_mutex_init (&rules->f_lock, NULL);
	pthread_mutex_init (&rules->eat_lock, NULL);
	pthread_mutex_init (&rules->must_lock, NULL);
}

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	if ((argc < 5) || (argc > 6))
		return (FALSE);
	if (ft_atol(argv[1]) < 1)
		return (FALSE);
	while (argv[++i])
	{
		while (argv[i][++k])
		{
			if (!ft_isdigit(argv[i][k]))
				return (FALSE);
		}
		k = -1;
	}
	return (TRUE);
}
