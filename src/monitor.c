/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 19:57:51 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 19:57:53 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <stdbool.h>

static bool	check_burn(t_coder *coder)
{
	if (tt_start(coder->last_comp_time) >= coder->table->burnout_time)
		return (true);
	return (false);
}

static void	run_burn(t_table *table, int i)
{
	if (check_burn(&table->coders[i]))
	{
		pthread_mutex_lock(&table->state_lock);
		log_burn(tt_start(table->start_time),
			&table->coders[i],
			table);
		table->someone_burned_out = 1;
		pthread_mutex_unlock(&table->state_lock);
		i = 0;
		while (i < table->num_coders)
		{
			pthread_mutex_lock(&table->dongles[i].lock);
			pthread_cond_broadcast(&table->dongles[i].cond);
			pthread_mutex_unlock(&table->dongles[i].lock);
			i++;
		}
	}
}

static bool	check_burned(t_table *table)
{
	pthread_mutex_lock(&table->state_lock);
	if (table->someone_burned_out)
	{
		pthread_mutex_unlock(&table->state_lock);
		return (true);
	}
	pthread_mutex_unlock(&table->state_lock);
	return (false);
}

void	*monitor_routine(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (true)
	{
		i = 0;
		if (check_burned(table))
			break ;
		while (i < table->num_coders)
		{
			run_burn(table, i);
			i++;
		}
	}
	return ((void *)0);
}
