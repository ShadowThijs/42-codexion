/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:24:02 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/18 15:27:22 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	cleanup_args(t_table *args)
{
	int	n;
	int	i;

	n = args->num_coders;
	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&args->dongles[i]);
		i++;
	}
	free(args->dongles);
	free(args->coders);

}
