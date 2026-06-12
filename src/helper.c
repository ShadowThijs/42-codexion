/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:49:07 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/06/12 16:07:04 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

bool	compare_tv(struct timeval first, struct timeval second)
{
	if (first.tv_sec > second.tv_sec)
		return (false);
	else if (first.tv_sec < second.tv_sec)
		return (true);
	else if (first.tv_usec > second.tv_usec)
		return (false);
	return (true);
}

long	tt_start(struct timeval start_tv)
{
	struct timeval	now_tv;

	gettimeofday(&now_tv, NULL);
	if (start_tv.tv_sec == now_tv.tv_sec)
		return ((now_tv.tv_usec - start_tv.tv_usec) / USEC_TO_MSEC);
	return (((now_tv.tv_sec - start_tv.tv_sec) * USEC_TO_MSEC)
		+ ((now_tv.tv_usec - start_tv.tv_usec) / USEC_TO_MSEC));
}

int	print_errors(char *message, t_table *args)
{
	cleanup_args(args);
	fprintf(stderr, "ERROR:\t%s\n", message);
	return (0);
}

struct timeval	gtime(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}

void	print_help(char *argv[])
{
	printf("usage: %s\t<number of coders> "
		"<time to burnout>\n\t\t\t<time to compile> "
		"<time to debug>\n\t\t\t<time to refactor> "
		"<number of compiles required>\n\t\t\t"
		"<dongle cooldown> <sheduler>\n\n", argv[0]);
	printf("\tnumber of coders: integer "
		"ranging from 2 to INT_MAX\n");
	printf("\ttime to burnout (in ms): integer\n");
	printf("\ttime to compile (in ms): integer\n");
	printf("\ttime to debug (in ms): integer\n");
	printf("\ttime to refactor (in ms): integer\n");
	printf("\tnumber of compiles: integer\n");
	printf("\tdongle cooldown (in ms): integer\n");
	printf("\tscheduler: either fifo or edf\n\n");
}
