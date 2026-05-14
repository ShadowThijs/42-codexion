/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:57:11 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/14 23:21:24 by tlogtenb         ###   ########.fr       */
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

int	quick_checks(t_arguments *args)
{
	if (args->tt_compile + args->dong_cool >= args->tt_burn)
		return (print_errors("Compile time and cooldown dongles too high!\n"
				"\tTry lowering compile/dongle cooldown times.\n"
				"\tOr increase time to burn out."));
	if (args->num_coders > 1
		&& (args->num_compiles_req / (args->num_coders / 2) * args->tt_compile)
		> args->tt_burn * args->num_compiles_req)
		return (print_errors("Throughput impossible!"));
	args->tp_cycle = args->tt_compile + args->tt_debug + args->tt_refactor;
	args->total_time = args->num_compiles_req * args->tp_cycle;
	return (0);
}

int	parse_args(int argc, char *argv[], t_arguments *args)
{
	if (argc != 9)
		return (print_errors("Not enough arguments!"));
	if (check_args(argv) == -1)
		return (print_errors("Incorrect arguments provided!"));
	args->num_coders = atoi(argv[1]);
	args->tt_burn = atoi(argv[2]);
	args->tt_compile = atoi(argv[3]);
	args->tt_debug = atoi(argv[4]);
	args->tt_refactor = atoi(argv[5]);
	args->num_compiles_req = atoi(argv[6]);
	args->dong_cool = atoi(argv[7]);
	if (!strcmp(argv[8], "fifo"))
		args->use_fifo = true;
	else if (!strcmp(argv[8], "edf"))
		args->use_edf = true;
	else
		return (-1);
	return (quick_checks(args));
}
