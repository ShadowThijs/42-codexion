/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:25:47 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/18 15:39:37 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H

# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

# define USEC_TO_SEC 1000000
# define USEC_TO_MSEC 1000

typedef struct s_table	t_table;

typedef struct s_coder
{
	int				id;
	struct timeval	last_comp_time;
	int				compile_count;
	pthread_t		thread;
	t_table			*table;
}	t_coder;

typedef struct s_table
{
	int				num_coders;
	long			burnout_time;
	long			compile_duration;
	long			refactor_duration;
	long			debug_duration;
	long			dongle_cooldown;
	int				required_compiles;
	int				someone_burned_out;
	int				total_compiles;
	char			*scheduler;
	pthread_mutex_t	*dongles;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;
	t_coder			*coders;
}	t_table;

int		parse_args(int argc, char *argv[], t_table *args);
int		print_errors(char *message);
int		init_coders(t_table *args, struct timeval start_time);
void	log_dong_taken(size_t timestamp, size_t coder);
void	log_compiling(size_t timestamp, size_t coder);
void	log_debugging(size_t timestamp, size_t coder);
void	log_refactor(size_t timestamp, size_t coder);
void	log_burn(size_t timestamp, size_t coder);
int		init_dongles(t_table *args);
long	tt_start(struct timeval start_tv);

#endif // CODEXION_H
