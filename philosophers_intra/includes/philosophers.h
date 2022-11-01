/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phiolive <phiolive@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 15:48:07 by phiolive          #+#    #+#             */
/*   Updated: 2022/10/20 01:21:32 by phiolive         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define FALSE 0
# define TRUE 1
# define WAKE 0
# define PREV 0
# define I 1
# define NEXT 2
# define DIE 0
# define FORK 1
# define EAT 2
# define SLP 3
# define THNK 4

// INCLUDES ---------------------------------------------

# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

// STRUCTS------------------------------------------------

typedef struct s_rules		t_rules;
typedef struct s_philos		t_philos;

struct s_rules
{
	long long int	*init_time;
	int				*nb_philo;
	int				*time_to_die;
	int				*t_eat;
	int				*sleep;
	int				*must_eat;
	int				*is_dead;
	int				**h_fork;
	t_philos		**all_philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	pthread_mutex_t	die_check;
	pthread_mutex_t	f_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	must_lock;
};

struct s_philos
{
	long long int	*eat;
	int				*pos;
	int				*must_eat;
	t_rules			*rules;
};

//######################################################
// ---------FUNCTIONS -----------------#################
//######################################################

// PHILO_ACTIONS -----------------------------------------------------
void			sleep_function(t_philos *philo);
void			think_function(t_philos *philo);
void			eat_function(t_philos *philos);

// PHILO_DIE_UTILS -----------------------------------------------------
int				die_while_eating(t_philos *ph, t_philos **all_p, int p, int n);
void			ill_die_waiting_a_fork(t_philos *philo, t_philos **all_philos);
int				is_philo_dead(t_philos *philo);

// PHILO_EAT_UTILS -----------------------------------------------------
int				eat_all_meals(t_rules *rules);
int				check_eat_usleep_time(t_philos *philo, t_philos **all_philos);
int				*longest_meal(t_philos *p, t_philos **all_p, t_rules *rules);
int				choose_mutex_lock_order(t_philos *philos);

// PHILO_FORK_LOCK -----------------------------------------------------
int				lock_fork_1(t_philos *philos);
int				lock_fork_2(t_philos *philos);
int				invert_lock_fork_1(t_philos *philos);
int				invert_lock_fork_2(t_philos *philos);

// PHILO_FORK_LOCK_MUTEX-------------------------------------------------
void			lock_mutex_fork(int fork, t_philos *philos);
void			lock_commom_fork(int fork, t_philos *philos);

// PHILO_INIT -----------------------------------------------------
void			ft_alloc_mem_for_rules(t_rules *rules);
void			ft_alloc_mem_for_philos(t_philos **philos, t_rules *rules);
void			ft_save_args(int argc, char **argv, t_rules *ru, t_philos **p);
void			ft_init_mutex(t_rules *rules);
int				ft_check_args(int argc, char **argv);

// PHILO_THRRADS -----------------------------------------------------
void			*routine(void *philo_void);
int				ft_start_thread(t_philos **p, t_rules *r, pthread_t *phthr);

// SPECIAL_CASES ------------------------------------------------------
void			*cant_eat_alone(void *philo_void);
void			*cant_eat_so_fast(void *philo_void);

// FREE_FUNCTIONS -----------------------------------------------------
void			free_philosophers(t_philos **philo, t_rules *rules);
void			ft_destroy_mutex(t_rules *rules);
void			ft_exit_and_free(t_philos **philo, t_rules *rules);

//MESSAGES ------------------------------------------------------------
void			ft_print(int msg, long long int t, int p, t_rules *rules);

//STRING ------------------------------------------------------------
int				ft_isdigit(int c);
int				ft_isspace(int c);
long long int	ft_atol(const char *nptr);
void			*ft_calloc(size_t nmemb, size_t size);
void			*ft_memcpy(void *dst, const void *src, size_t len);

//TIME ------------------------------------------------------------
long long int	time_str(t_philos *philos);
long long int	get_time_now(void);

#endif
