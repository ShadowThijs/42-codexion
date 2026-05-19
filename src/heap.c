/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlogtenb <tlogtenb@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 18:30:00 by tlogtenb          #+#    #+#             */
/*   Updated: 2026/05/19 18:30:00 by tlogtenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

static bool	heap_compare(t_wait_node *a, t_wait_node *b, char *scheduler)
{
	if (strcmp(scheduler, "edf") == 0)
		return (compare_tv(a->deadline, b->deadline));
	return (compare_tv(a->request_time, b->request_time));
}

void	heap_push(t_wait_queue *q, t_wait_node node, t_table *table)
{
	t_wait_node	tmp;
	int			idx;
	int			parent;

	idx = q->size;
	q->nodes[idx] = node;
	q->size++;
	while (idx > 0)
	{
		parent = (idx - 1) / 2;
		if (heap_compare(&q->nodes[idx], &q->nodes[parent],
				table->scheduler))
		{
			tmp = q->nodes[idx];
			q->nodes[idx] = q->nodes[parent];
			q->nodes[parent] = tmp;
			idx = parent;
		}
		else
			break ;
	}
}

t_wait_node	heap_pop(t_wait_queue *q, t_table *table)
{
	t_wait_node	result;
	t_wait_node	tmp;
	int			idx;
	int			child;

	result = q->nodes[0];
	q->size--;
	q->nodes[0] = q->nodes[q->size];
	idx = 0;
	while (2 * idx + 1 < q->size)
	{
		child = 2 * idx + 1;
		if (child + 1 < q->size && heap_compare(&q->nodes[child + 1],
				&q->nodes[child], table->scheduler))
			child++;
		if (!heap_compare(&q->nodes[child], &q->nodes[idx],
				table->scheduler))
			break ;
		tmp = q->nodes[idx];
		q->nodes[idx] = q->nodes[child];
		q->nodes[child] = tmp;
		idx = child;
	}
	return (result);
}
