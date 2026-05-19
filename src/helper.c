/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 17:49:07 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 17:49:08 by tlogtenb         ###   ########.fr       */
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

int	print_errors(char *message)
{
	fprintf(stderr, "ERROR:\t%s\n", message);
	return (0);
}

struct timeval	gtime(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now);
}
