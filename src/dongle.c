/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:30:00 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 18:30:00 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static struct timeval	compute_deadline(t_coder *coder)
{
	struct timeval	deadline;

	deadline.tv_sec = coder->last_comp_time.tv_sec
		+ coder->table->burnout_time / USEC_TO_MSEC;
	deadline.tv_usec = coder->last_comp_time.tv_usec
		+ (coder->table->burnout_time % USEC_TO_MSEC) * USEC_TO_MSEC;
	if (deadline.tv_usec >= USEC_TO_SEC)
	{
		deadline.tv_sec++;
		deadline.tv_usec -= USEC_TO_SEC;
	}
	return (deadline);
}

void	acquire_dongle(t_coder *coder, int dongle_idx)
{
	t_dongle	*d;
	t_wait_node	node;

	d = &coder->table->dongles[dongle_idx];
	pthread_mutex_lock(&d->lock);
	if (d->state == DONGLE_AVAILABLE)
	{
		d->state = DONGLE_HELD;
		d->held_by = coder->id;
	}
	else
	{
		node.coder_id = coder->id;
		gettimeofday(&node.request_time, NULL);
		node.deadline = compute_deadline(coder);
		heap_push(&d->queue, node, coder->table);
		while (d->held_by != coder->id
			&& !coder->table->someone_burned_out)
			pthread_cond_wait(&d->cond, &d->lock);
	}
	pthread_mutex_unlock(&d->lock);
	if (!coder->table->someone_burned_out)
		log_dong_taken(tt_start(coder->table->start_time), coder,
			coder->table);
}

void	release_dongle(t_coder *coder, int dongle_idx)
{
	t_dongle	*d;
	t_wait_node	next;

	d = &coder->table->dongles[dongle_idx];
	pthread_mutex_lock(&d->lock);
	gettimeofday(&d->released_at, NULL);
	d->held_by = -1;
	d->state = DONGLE_COOLING;
	usleep(coder->table->dongle_cooldown * USEC_TO_MSEC);
	if (d->queue.size > 0)
	{
		next = heap_pop(&d->queue, coder->table);
		d->held_by = next.coder_id;
		d->state = DONGLE_HELD;
		pthread_cond_signal(&d->cond);
	}
	else
		d->state = DONGLE_AVAILABLE;
	pthread_mutex_unlock(&d->lock);
}
