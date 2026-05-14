/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:01:53 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/14 23:08:13 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

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
	return (-1);
}

int	main(int argc, char *argv[])
{
	t_arguments		*args;
	int				parser;
	struct timeval	tv;

	args = malloc(sizeof(t_arguments));
	if (!args)
		return (print_errors("malloc for arguments failed!"));
	parser = parse_args(argc, argv, args);
	if (parser != 0)
		return (-1);
	gettimeofday(&tv, NULL);
	printf("Seconds since 1/1/1970: %lu\n", tv.tv_sec);
	printf("Microseconds: %ld\n", tv.tv_usec);
	return (0);
}
