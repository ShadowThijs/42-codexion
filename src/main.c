/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:01:53 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 16:57:18 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <bits/pthreadtypes.h>
#include <sys/time.h>

int	start_threads(t_table *args)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < args->num_coders)
	{
		pthread_create(&args->coders[i].thread, NULL, coder_routine,
			&args->coders[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, args);
	i = 0;
	while (i < args->num_coders)
	{
		pthread_join(args->coders[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_table	*args;

	args = malloc(sizeof(t_table));
	if (!args)
		return (print_errors("malloc for arguments failed!"));
	if (!parse_args(argc, argv, args))
		return (print_errors("Arguments error!"));
	gettimeofday(&args->start_time, NULL);
	if (!init_coders(args))
		return (print_errors("Could not initialise coders!"));
	if (!init_dongles(args))
		return (print_errors("Could not initialise dongles!"));
	start_threads(args);
	return (0);
}
