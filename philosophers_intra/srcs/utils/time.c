/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 15:46:44 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/15 15:46:44 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long long int	time_str(t_philos *philos)
{
	struct timeval	current_time;
	long long int	time_now;

	gettimeofday(&current_time, NULL);
	time_now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_now - *philos->rules->init_time);
}

long long int	get_time_now(void)
{
	struct timeval	current_time;
	long long int	time_now;

	gettimeofday(&current_time, NULL);
	time_now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (time_now);
}
