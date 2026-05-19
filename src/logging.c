/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 18:49:02 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 17:12:52 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

void	log_dong_taken(size_t timestamp, t_coder *coder, t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d has taken a dongle\n", timestamp, coder->id);
	pthread_mutex_unlock(&table->print_lock);
}

void	log_compiling(size_t timestamp, t_coder *coder, t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d is compiling\n", timestamp, coder->id);
	pthread_mutex_unlock(&table->print_lock);
}

void	log_debugging(size_t timestamp, t_coder *coder, t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d is debugging\n", timestamp, coder->id);
	pthread_mutex_unlock(&table->print_lock);
}

void	log_refactor(size_t timestamp, t_coder *coder, t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d is refactoring\n", timestamp, coder->id);
	pthread_mutex_unlock(&table->print_lock);
}

void	log_burn(size_t timestamp, t_coder *coder, t_table *table)
{
	pthread_mutex_lock(&table->print_lock);
	printf("%ld %d burned out\n", timestamp, coder->id);
	pthread_mutex_unlock(&table->print_lock);
}
