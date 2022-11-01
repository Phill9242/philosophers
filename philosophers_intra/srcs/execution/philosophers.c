/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:42:45 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:14:27 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_rules		*rules;
	t_philos	**philos;
	pthread_t	*philos_thread;
	int			i;

	i = -1;
	if (ft_check_args (argc, argv) == FALSE)
	{
		printf ("Invalid arguments\n");
		return (-1);
	}
	rules = ft_calloc (1, sizeof(t_rules));
	philos = ft_calloc (ft_atol(argv[1]), sizeof(*philos));
	philos_thread = ft_calloc (sizeof(pthread_t), ft_atol(argv[1]));
	if (rules == NULL || philos == NULL || philos_thread == NULL)
		return (-2);
	ft_save_args (argc, argv, rules, philos);
	ft_init_mutex (rules);
	ft_start_thread (philos, rules, philos_thread);
	while (++i < *rules->nb_philo)
		pthread_join(philos_thread[i], NULL);
	free (philos_thread);
	ft_exit_and_free (philos, rules);
	return (0);
}
