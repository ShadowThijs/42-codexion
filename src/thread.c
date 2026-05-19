/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 16:25:34 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 18:30:00 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>

static int	should_stop(t_coder *coder)
{
	int	stop;

	pthread_mutex_lock(&coder->table->state_lock);
	stop = coder->table->someone_burned_out
		|| coder->compile_count >= coder->table->required_compiles;
	pthread_mutex_unlock(&coder->table->state_lock);
	return (stop);
}

static void	lock_dongles(t_coder *coder)
{
	int	left;
	int	right;
	int	n;

	n = coder->table->num_coders;
	left = coder->id;
	right = (coder->id + 1) % n;
	if (coder->id == n - 1)
	{
		acquire_dongle(coder, right);
		acquire_dongle(coder, left);
	}
	else
	{
		acquire_dongle(coder, left);
		acquire_dongle(coder, right);
	}
}

static void	unlock_dongles(t_coder *coder)
{
	int	left;
	int	right;
	int	n;

	n = coder->table->num_coders;
	left = coder->id;
	right = (coder->id + 1) % n;
	release_dongle(coder, left);
	release_dongle(coder, right);
}

static void	runtime_loop(t_coder *coder)
{
	t_table	*table;

	table = coder->table;
	gettimeofday(&coder->last_comp_time, NULL);
	log_compiling(tt_start(table->start_time), coder, table);
	usleep(table->compile_duration * USEC_TO_MSEC);
	unlock_dongles(coder);
	coder->compile_count++;
	pthread_mutex_lock(&table->state_lock);
	if (!coder->table->someone_burned_out)
	{
		log_debugging(tt_start(table->start_time), coder, table);
		usleep(table->debug_duration * USEC_TO_MSEC);
		log_refactor(tt_start(table->start_time), coder, table);
		usleep(table->refactor_duration * USEC_TO_MSEC);
	}
	pthread_mutex_unlock(&table->state_lock);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (true)
	{
		if (should_stop(coder))
			break ;
		lock_dongles(coder);
		if (coder->table->someone_burned_out)
			break ;
		runtime_loop(coder);
	}
	return (NULL);
}
