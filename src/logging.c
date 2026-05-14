/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:49:02 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/14 18:59:10 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	log_dong_taken(size_t timestamp, size_t coder)
{
	printf("%ld %ld has taken a dongle\n",
		timestamp, coder);
}

void	log_compiling(size_t timestamp, size_t coder)
{
	printf("%ld %ld is compiling\n",
		timestamp, coder);
}

void	log_debugging(size_t timestamp, size_t coder)
{
	printf("%ld %ld is debugging",
		timestamp, coder);
}

void	log_refactor(size_t timestamp, size_t coder)
{
	printf("%ld %ld is refactoring",
		timestamp, coder);
}

void	log_burn(size_t timestamp, size_t coder)
{
	printf("%ld %ld burned out",
		timestamp, coder);
}
