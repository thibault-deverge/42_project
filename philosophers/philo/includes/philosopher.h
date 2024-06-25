/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:07:40 by tdeverge          #+#    #+#             */
/*   Updated: 2023/03/12 18:24:12 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/********************************************************/
/*						HEADERS							*/
/********************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <sys/time.h>

/********************************************************/
/*						MACROS							*/
/********************************************************/
/*						error							*/
# define ERROR_ARG_NB		"number of arguments is not valid.\n"
# define ERROR_ARG_VALUE	"argument is not valid.\n"
# define ERROR_ALLOC		"allocation with malloc was a fail.\n"
/*						parsing							*/
# define ALLOC_FAILURE		0
# define PARSE_SUCCESS 		1
# define PARSE_FAILURE 		0
# define SUCCESS			1
/*						printing						*/
# define FORK				0
# define EAT				1
# define SLEEP				2
# define THINK				3
# define BLACK				"\033[0m"
# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define BLUE				"\033[1;34m"
# define PURPLE				"\033[1;35m"
# define CYAN				"\033[1;36m"

/********************************************************/
/*						STRUCTURES						*/
/********************************************************/
typedef struct s_rules
{
	int				nb_philos;
	int				lifetime;
	int				eat_time;
	int				sleep_time;
	int				total_meals;
	long int		start_time;
}	t_rules;

typedef struct s_mutexes
{
	pthread_mutex_t	*forks;	
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	int				end_counter;
	int				print_flag;
	int				death_flag;
}	t_mutexes;

typedef struct s_philosopher
{
	pthread_t			th_id;
	int					id;
	int					meals_eaten;
	long int			last_meal_time;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_rules		*rules;
	struct s_mutexes	*mutexes;
}	t_philosopher;

typedef struct s_data
{
	t_philosopher	*philos;
	t_mutexes		*mutexes;
	t_rules			*rules;
}	t_data;

typedef struct s_supervisor
{
	pthread_t				th_id;
	long int				start_time;
	int						lifetime;
	int						nb_philos;
	int						total_meals;
	struct s_philosopher	*philos;
	struct s_mutexes		*mutexes;
}	t_supervisor;

/********************************************************/
/*						PROTOTYPES						*/
/********************************************************/
/*						parsing							*/
t_data			*init_data(int argc, char **argv);
t_rules			*parser(int argc, char **argv);
t_mutexes		*init_mutexes(int nb_philos);
t_philosopher	*init_philos(t_rules *rules, t_mutexes *mutexes);
/*						execution						*/
t_supervisor	*launch_supervisor(t_data *data);
void			launch_philos(t_philosopher *philos, int nb_philos);
void			*routine_philo(void *arg);
void			*routine_supervisor(void *arg);
void			check_meals(t_philosopher *philo);
int				check_death(t_mutexes *mut);
int				break_end_dinner(t_mutexes *mutexes, int nb_philos);
/*						utils							*/
long int		get_time(long int start_time);
void			free_all(t_data *data, t_supervisor *supervisor);
void			usleep_safe(t_philosopher *philo, int time);
int				ft_atoi_rule(const char *nptr);

#endif
