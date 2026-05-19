/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:57:11 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/18 17:06:08 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static int	check_args(char *argv[])
{
	size_t	i;
	size_t	j;

	i = 1;
	while (i < 7)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (-1);
			j++;
		}
		i++;
	}
	return (1);
}

int	quick_checks(t_table *args)
{
	if (args->compile_duration + args->dongle_cooldown >= args->burnout_time)
		return (print_errors("Compile time and cooldown dongles too high!"));
	if (args->num_coders > 1 && (args->required_compiles / (args->num_coders
				/ 2) * args->compile_duration) > args->burnout_time
		* args->required_compiles)
		return (print_errors("Throughput impossible!"));
	return (1);
}

int	parse_args(int argc, char *argv[], t_table *args)
{
	if (argc != 9)
		return (print_errors("Not enough arguments!"));
	if (check_args(argv) == -1)
		return (print_errors("Incorrect arguments provided!"));
	args->num_coders = atoi(argv[1]);
	if (args->num_coders == 1)
		return (print_errors("Cannot start with 1 dongle!"));
	args->burnout_time = (long)atoi(argv[2]);
	args->compile_duration = (long)atoi(argv[3]);
	args->debug_duration = (long)atoi(argv[4]);
	args->refactor_duration = atoi(argv[5]);
	args->required_compiles = atoi(argv[6]);
	args->dongle_cooldown = atoi(argv[7]);
	args->scheduler = argv[8];
	args->someone_burned_out = 0;
	pthread_mutex_init(&args->print_lock, NULL);
	pthread_mutex_init(&args->state_lock, NULL);
	return (quick_checks(args));
}
