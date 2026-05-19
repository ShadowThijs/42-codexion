/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:25:47 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 17:35:50 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H

# define CODEXION_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define USEC_TO_SEC 1000000
# define USEC_TO_MSEC 1000

# define DONGLE_AVAILABLE 0
# define DONGLE_HELD 1
# define DONGLE_COOLING 2

typedef struct s_table	t_table;

typedef struct s_wait_node
{
	int					coder_id;
	struct timeval		request_time;
	struct timeval		deadline;
}	t_wait_node;

typedef struct s_wait_queue
{
	t_wait_node			*nodes;
	int					size;
	int					capacity;
}	t_wait_queue;

typedef struct s_coder
{
	int					id;
	struct timeval		last_comp_time;
	int					compile_count;
	pthread_t			thread;
	t_table				*table;
}	t_coder;

typedef struct s_dongle
{
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	int					state;
	int					held_by;
	struct timeval		released_at;
	t_wait_queue		queue;
}	t_dongle;

typedef struct s_table
{
	int					num_coders;
	long				burnout_time;
	long				compile_duration;
	long				refactor_duration;
	long				debug_duration;
	long				dongle_cooldown;
	int					required_compiles;
	int					someone_burned_out;
	int					total_compiles;
	char				*scheduler;
	struct timeval		start_time;
	t_dongle			*dongles;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		state_lock;
	t_coder				*coders;
}	t_table;

int				parse_args(int argc, char *argv[], t_table *args);
int				print_errors(char *message);
int				init_coders(t_table *args);
void			log_dong_taken(size_t timestamp, t_coder *coder,
					t_table *table);
void			log_compiling(size_t timestamp, t_coder *coder,
					t_table *table);
void			log_debugging(size_t timestamp, t_coder *coder,
					t_table *table);
void			log_refactor(size_t timestamp, t_coder *coder,
					t_table *table);
void			log_burn(size_t timestamp, t_coder *coder,
					t_table *table);
int				init_dongles(t_table *args);
long			tt_start(struct timeval start_tv);
void			*coder_routine(void *arg);
bool			compare_tv(struct timeval first, struct timeval second);
struct timeval	gtime(void);
void			heap_push(t_wait_queue *q, t_wait_node node,
					t_table *table);
t_wait_node		heap_pop(t_wait_queue *q, t_table *table);
void			acquire_dongle(t_coder *coder, int dongle_idx);
void			release_dongle(t_coder *coder, int dongle_idx);
void			*monitor_routine(void *arg);

#endif // CODEXION_H
