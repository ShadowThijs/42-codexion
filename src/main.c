/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:01:53 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/18 15:49:38 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"
#include <sys/time.h>

/*
	* One or more coders sit in a circle, they share a compiler
	* They alternatively compile, debug or refactor
	*     (can only perform one at a time)
	* There are as many dongles as there are coders
	* 2 dongles required to compile (left and right)
	* After compiling a coder starts debugging
	* After debugging a coder starts refactoring
	* Coders burn out if they cannot compile for a specific timeframe
	*
	* Every coder needs to compile regularly and should not burn out
	* Coders do not communicate with eachother
	* Coders do not know if another coder is about to burn out
*/

int	print_errors(char *message)
{
	fprintf(stderr, "ERROR:\t%s\n", message);
	return (0);
}

long	tt_start(struct timeval start_tv)
{
	struct timeval	now_tv;

	gettimeofday(&now_tv, NULL);
	if (start_tv.tv_sec == now_tv.tv_sec)
		return ((now_tv.tv_usec - start_tv.tv_usec) / USEC_TO_MSEC);
	return (
		((now_tv.tv_sec - start_tv.tv_sec) * USEC_TO_MSEC)
		+ ((now_tv.tv_usec - start_tv.tv_usec) / USEC_TO_MSEC)
	);
}

int	main(int argc, char *argv[])
{
	t_table			*args;
	struct timeval	start_tv;

	args = malloc(sizeof(t_table));
	if (!args)
		return (print_errors("malloc for arguments failed!"));
	if (!parse_args(argc, argv, args))
		return (print_errors("Could not parse arguments"));
	gettimeofday(&start_tv, NULL);
	printf("Seconds since 1/1/1970: %lu\n", start_tv.tv_sec);
	printf("Microseconds: %ld\n", start_tv.tv_usec);
	usleep(50 * USEC_TO_MSEC);
	printf("Time from start in MS: %ld", tt_start(start_tv));
	if (!init_coders(args, start_tv))
		return (print_errors("Could not initialise coders"));
	if (!init_dongles(args))
		return (print_errors("Could not initialise dongles"));
	return (0);
}
