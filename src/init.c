/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:37:38 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/18 16:03:43 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <pthread.h>

int	init_coders(t_table *args, struct timeval start_time)
{
	int	n;
	int	i;

	n = args->num_coders;
	args->coders = malloc(n * sizeof(t_coder));
	if (!args->coders)
		return (print_errors("Could not malloc coders array"));
	i = 0;
	while (i < n)
	{
		args->coders[i].id = i;
		args->coders[i].compile_count = 0;
		args->coders[i].last_comp_time = start_time;
		args->coders[i].table = args;
		i++;
	}
	return (1);
}

int	init_dongles(t_table *args)
{
	int	n;
	int	i;

	n = args->num_coders;
	args->dongles = malloc(n * sizeof(pthread_mutex_t));
	if (!args->dongles)
		return (print_errors("Unable to malloc dongles!"));
	while (i < n)
	{
		pthread_mutex_init(&args->dongles[i], NULL);
		i++;
	}
	pthread_mutex_init(&args->print_lock, NULL);
	pthread_mutex_init(&args->state_lock, NULL);
	return (1);
}
