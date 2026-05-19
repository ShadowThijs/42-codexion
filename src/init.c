/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 14:37:38 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 17:36:28 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	init_coders(t_table *args)
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
		args->coders[i].last_comp_time = args->start_time;
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
	i = 0;
	args->dongles = malloc(n * sizeof(t_dongle));
	if (!args->dongles)
		return (print_errors("Unable to malloc dongles!"));
	while (i < n)
	{
		pthread_mutex_init(&args->dongles[i].lock, NULL);
		pthread_cond_init(&args->dongles[i].cond, NULL);
		args->dongles[i].state = DONGLE_AVAILABLE;
		args->dongles[i].held_by = -1;
		args->dongles[i].queue.nodes = malloc(sizeof(t_wait_node)
				* args->num_coders);
		if (!args->dongles[i].queue.nodes)
			return (print_errors("Unable to malloc queue nodes!"));
		args->dongles[i].queue.size = 0;
		args->dongles[i].queue.capacity = args->num_coders;
		i++;
	}
	return (1);
}
